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

#include "bruker/BrukerDirectory.h"
#include "core/actions/Action.h"
#include "dicom/SOPClass.h"

namespace dicomifier
{
    
namespace actions
{

struct VISU_FRAMEGROUP_TYPE
{
    int length;                 // Number of frame group elements
    //std::string groupId;        // Frame group unique identifier (Not used)
    //std::string groupComment;   // Frame group description (Not used)
    //int valsStart;              // First dependant parameters for this frame group
    //int valsCnt;                // Number of dependant parameters for this frame group
    std::vector<std::string> groupDepVals;
} ;
    
class EnhanceBrukerDicom : public Action
{
public:
    typedef EnhanceBrukerDicom Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(DcmDataset * dataset, 
                       std::string const & brukerDir,
                       std::string const & sopclassuid) 
                { return Pointer(new Self(dataset, brukerDir, 
                                          sopclassuid)); }
    
    virtual ~EnhanceBrukerDicom();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);
    
    std::string const & get_brukerDir() const;
    void set_brukerDir(std::string const & brukerDir);
    
    std::string const & get_SOPClassUID() const;
    void set_SOPClassUID(std::string const & sopclassuid);

    virtual void run() const;
    
    static std::string get_class_name() { return "EnhanceBrukerDicom"; }

protected:
    EnhanceBrukerDicom();
    EnhanceBrukerDicom(DcmDataset * dataset, 
                       std::string const & brukerDir,
                       std::string const & sopclassuid);

private:
    void create_MRImageStorage(dicomifier::bruker::BrukerDataset* brukerdataset,
                               std::vector<int> indexlists,
                               std::string const & seriesnumber,
                               int framesNumber) const;

    DcmDataset * _dataset;
    std::string _brukerDir;
    std::string _SOPClassUID;
    
    EnhanceBrukerDicom(Self const & other);     // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace actions
    
} // namespace dicomifier

#endif // _a1d24eb4_37bb_46b4_a769_d76392230052
