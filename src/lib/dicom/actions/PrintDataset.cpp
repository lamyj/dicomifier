/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "PrintDataset.h"

namespace dicomifier
{
    
namespace actions
{
    
PrintDataset
::PrintDataset()
    :Action(), _dataset(NULL), _outputfile("std::cout")
{
    // Nothing to do
}

PrintDataset
::PrintDataset(DcmDataset* dataset, std::string const & outputfile)
    :Action(), _dataset(dataset), _outputfile(outputfile)
{
    // Nothing to do
}

PrintDataset
::~PrintDataset()
{
    // Nothing to do
}

DcmDataset* 
PrintDataset
::get_dataset() const
{
    return this->_dataset;
}

void 
PrintDataset
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
}

std::string 
PrintDataset
::get_outputfile() const
{
    return this->_outputfile;
}

void 
PrintDataset
::set_outputfile(std::string const & outputfile)
{
    this->_outputfile = outputfile;
}

void 
PrintDataset
::run() const
{
    if (this->_dataset == NULL)
    {
        throw DicomifierException("Unable to print empty dataset");
    }
    
    if (this->_outputfile == "std::cerr")
    {
        this->_dataset->print(std::cerr);
    }
    else if (this->_outputfile == "std::cout" ||
             this->_outputfile == "") // Default
    {
        this->_dataset->print(std::cout);
    }
    else
    {
        std::ofstream myfile;
        myfile.open(this->_outputfile);
        this->_dataset->print(myfile);
        myfile.close();
    }
}
    
} // namespace actions
    
} // namespace dicomifier
