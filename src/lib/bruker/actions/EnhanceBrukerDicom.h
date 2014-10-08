/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a1d24eb4_37bb_46b4_a769_d76392230052
#define _a1d24eb4_37bb_46b4_a769_d76392230052

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"

namespace dicomifier
{
    
namespace actions
{
    
class EnhanceBrukerDicom : public Action
{
public:
    typedef EnhanceBrukerDicom Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(DcmDataset * dataset, std::string brukerDir,
                       std::string const & brukerToDicomDictionary) 
                { return Pointer(new Self(dataset, brukerDir, 
                                          brukerToDicomDictionary)); }
    
    virtual ~EnhanceBrukerDicom();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);
    
    std::string const & get_brukerDir() const;
    void set_brukerDir(std::string const & brukerDir);

    virtual void run() const;
    
    static std::string get_class_name() { return "EnhanceBrukerDicom"; }

protected:
    EnhanceBrukerDicom();
    EnhanceBrukerDicom(DcmDataset * dataset, std::string brukerDir,
                       std::string const & brukerToDicomDictionary);

private:
    DcmDataset * _dataset;
    std::string _brukerDir;
    std::string _brukerToDicomDictionary;
    
    EnhanceBrukerDicom(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};

struct VISU_FRAMEGROUP_TYPE
{
    int length;                 // Number of frame group elements
    std::string groupId;        // Frame group unique identifier
    std::string groupComment;   // Frame group description
    int valsStart;              // First dependant parameters for this frame group
    int valsCnt;                // Number of dependant parameters for this frame group
} ;
    
} // namespace actions
    
} // namespace dicomifier

#endif // _a1d24eb4_37bb_46b4_a769_d76392230052
