/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b2f009c1_3a10_419b_9d30_6b9986e25ac2
#define _b2f009c1_3a10_419b_9d30_6b9986e25ac2

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class RegExFilter : public SubTag<VR>
{
public:
    typedef RegExFilter Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of RegExFilter
    static Pointer New();
    
    static Pointer New(Tag::Pointer tag, std::string const & expression);

    virtual ~RegExFilter();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const { return ECT_RegExFilter; }
    
protected:
    RegExFilter();
    
    RegExFilter(Tag::Pointer tag, std::string const & expression);

private:
    Tag::Pointer _tag;
    
    std::string _expression;

};

} // namespace translator
    
} // namespace dicomifier

#include "RegExFilter.txx"

#endif // _b2f009c1_3a10_419b_9d30_6b9986e25ac2
