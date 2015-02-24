/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f45db991_65f2_4afe_9bf6_fc39dc07035d
#define _f45db991_65f2_4afe_9bf6_fc39dc07035d

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The UIDGenerator class
 */
template<DcmEVR VR>
class UIDGenerator : public SubTag<VR>
{
public:
    typedef UIDGenerator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of UIDGenerator
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of UIDGenerator
     * @param uid_type: UID Type to generate
     * @return new instance of UIDGenerator
     */
    static Pointer New(std::string const & uid_type);

    /// Destroy the instance of UIDGenerator
    virtual ~UIDGenerator();
    
    /**
     * @brief run: Generate new UID
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of UIDGenerator
    UIDGenerator();
    
    /**
     * @brief Create an instance of UIDGenerator
     * @param uid_type: UID Type to generate
     */
    UIDGenerator(std::string const & uid_type);

private:
    /// UID Type to generate
    std::string _uid_type;

};

} // namespace translator
    
} // namespace dicomifier

#include "UIDGenerator.txx"

#endif // _f45db991_65f2_4afe_9bf6_fc39dc07035d


