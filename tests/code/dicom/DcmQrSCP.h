/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f515ed49_8c2b_4fc1_b7db_fdc3ec747861
#define _f515ed49_8c2b_4fc1_b7db_fdc3ec747861

#include <fstream>
#include <signal.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>

/**
 * Test fixture starting a dcmqrscp processes.
 * 
 * The process listens on port 11112 and has AE title "REMOTE". Only AE named
 * "LOCAL" may connect to it. Its config file and storage directory are
 * temporary and deleted in the destructor.
 */
class DcmQrSCP
{
public:
    
    
    DcmQrSCP()
    {
        char template_[] = "/tmp/dicomifier.XXXXXX";
        mkdtemp(template_);
        this->_directory = template_;
        
        std::string const config = this->_directory+"/config";
            
        this->_pid = fork();
        if(this->_pid == 0)
        {
            std::ofstream stream(config);
            stream << "HostTable BEGIN\n";
            stream << "remote = (REMOTE, localhost, 11112)\n";
            stream << "local = (LOCAL, localhost, 0)\n";
            stream << "HostTable END \n";
            stream << "\n";
            stream << "AETable BEGIN\n";
            stream << "REMOTE " << this->_directory << " RW (10, 1024mb) local\n";
            stream << "AETable END\n";
            stream.close();
            
            execlp("dcmqrscp", "dcmqrscp", "-c", config.c_str(), "11112", NULL);
            // The exec will not return on success.
            throw std::runtime_error("Could not run dcmqrscp");
        }
        else
        {
            int status = system("echoscu -aec REMOTE -aet LOCAL localhost 11112");
            int count = 0;
            while(WEXITSTATUS(status)>0 && count < 10)
            {
                // Wait a bit to make sure the process is running
                usleep(100000);
                status = system("echoscu -aec REMOTE -aet LOCAL localhost 11112");
                ++count;
            }
            if(WEXITSTATUS(status) == -1 || count >= 10)
            {
                throw std::runtime_error("Could not wait for dcmqrscp");
            }
        }
    }
    
    ~DcmQrSCP()
    {
        if(this->_pid != 0)
        {
            // Make sure boost does not complain about killing the dcmqrscp
            struct sigaction old_action, new_action;
            new_action.sa_handler = SIG_IGN;
            sigaction(SIGCHLD, &new_action, &old_action);
            
            // Kill the process, remove its data on disk
            kill(this->_pid, SIGKILL);
            std::string const command = "rm -rf "+this->_directory;
            system(command.c_str());
            
            // Restore the original signal handler
            sigaction(SIGCHLD, &old_action, NULL);
        }
    }
    
private:
    std::string _directory;
    std::string _config;
    pid_t _pid;
};

#endif // _f515ed49_8c2b_4fc1_b7db_fdc3ec747861
