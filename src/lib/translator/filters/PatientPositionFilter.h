/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _01f332b4_9927_4b74_84e5_dd72c753c693
#define _01f332b4_9927_4b74_84e5_dd72c753c693

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class PatientPositionFilter : public SubTag<VR>
{
public:
    typedef PatientPositionFilter Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of RegExFilter
    static Pointer New();
    
    static Pointer New(Tag::Pointer tag);

    virtual ~PatientPositionFilter();
    
    virtual void run(DcmDataset* dataset,
                     dicomifier::bruker::BrukerDataset* brukerdataset);
    
    virtual ClassType get_class_type() const { return ECT_PatientPositionFilter; }
    
protected:
    PatientPositionFilter();
    
    PatientPositionFilter(Tag::Pointer tag);

private:
    Tag::Pointer _tag;

};

} // namespace translator
    
} // namespace dicomifier

#include "PatientPositionFilter.txx"

#endif // _01f332b4_9927_4b74_84e5_dd72c753c693
