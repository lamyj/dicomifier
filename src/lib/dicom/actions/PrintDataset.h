/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _19d5e0a0_18d5_435c_a768_711171448f76
#define _19d5e0a0_18d5_435c_a768_711171448f76

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"

namespace dicomifier
{
    
namespace actions
{
    
/**
 * @brief Action PrintDataset: export Dataset as string
 */
class PrintDataset : public Action
{
public:
    typedef PrintDataset Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of PrintDataset
    static Pointer New() { return Pointer(new Self()); }
    
    static Pointer New(DcmDataset* dataset, std::string const & outputfile)
        { return Pointer(new Self(dataset, outputfile)); }
    
    /// Destroy the instance of PrintDataset
    virtual ~PrintDataset();
    
    /**
     * 
     * @return 
     */
    DcmDataset* get_dataset() const;
    
    /**
     * 
     * @param dataset: 
     */
    void set_dataset(DcmDataset * dataset);
    
    /**
     * 
     * @return 
     */
    std::string get_outputfile() const;
    
    /**
     * 
     * @param outputfile: 
     */
    void set_outputfile(std::string const & outputfile);

    /**
     * @brief Run the action.
     */
    virtual void run() const;
    
    /**
     * Get this class name
     * @return this class name
     */
    static std::string get_class_name() { return "PrintDataset"; }

protected:
    /// Create an instance of PrintDataset
    PrintDataset();
    
    PrintDataset(DcmDataset* dataset, std::string const & outputfile);

private:
    /// Dataset to print
    DcmDataset * _dataset;
    
    /// Output file path (default: 'std::cout')
    std::string _outputfile;
    
    PrintDataset(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace actions
    
} // namespace dicomifier

#endif // _19d5e0a0_18d5_435c_a768_711171448f76
