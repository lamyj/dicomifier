/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c2d2da5f_7ee0_4ada_85dd_ca5f807cc7f9
#define _c2d2da5f_7ee0_4ada_85dd_ca5f807cc7f9

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class UpperCaseGenerator : public SubTag<VR>
{
public:
    typedef UpperCaseGenerator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of UpperCaseGenerator
    static Pointer New();
    
    static Pointer New(Tag::Pointer tag);

    virtual ~UpperCaseGenerator();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const { return ECT_UpperCaseGenerator; }
    
protected:
    UpperCaseGenerator();
    
    UpperCaseGenerator(Tag::Pointer tag);

private:
    Tag::Pointer _tag;

};

} // namespace translator
    
} // namespace dicomifier

#include "UpperCaseGenerator.txx"

#endif // _c2d2da5f_7ee0_4ada_85dd_ca5f807cc7f9



