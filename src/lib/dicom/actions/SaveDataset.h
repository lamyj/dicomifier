/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b2acff4b_4252_4850_9a62_a9ecdc5f9520
#define _b2acff4b_4252_4850_9a62_a9ecdc5f9520

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"

namespace dicomifier
{
	
namespace actions
{

class SaveDataset : public Action
{
public:
    typedef SaveDataset Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(DcmDataset * dataset, std::string filename) 
			{ return Pointer(new Self(dataset, filename)); }
    
	virtual ~SaveDataset();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);
    
    std::string const & get_filename() const;
    void set_filename(std::string const & filename);

    virtual void run() const;
    
    static std::string get_class_name() { return "SaveDataset"; }

protected:
	SaveDataset();
	SaveDataset(DcmDataset * dataset, std::string filename);

private:
    DcmDataset * _dataset;
    std::string _filename;

    SaveDataset(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
	
} // namespace actions
	
} // namespace dicomifier

#endif // _b2acff4b_4252_4850_9a62_a9ecdc5f9520
