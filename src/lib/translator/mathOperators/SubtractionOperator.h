/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _38f2f367_9431_49ca_8af8_2b7a79e7198d
#define _38f2f367_9431_49ca_8af8_2b7a79e7198d

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class SubtractionOperator : public SubTag<VR>
{
public:
    typedef SubtractionOperator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SubtractionOperator
    static Pointer New();
    
    static Pointer New(std::vector<Tag::Pointer> tags);

    virtual ~SubtractionOperator();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const { return ECT_SubtractionOperator; }
    
protected:
    SubtractionOperator();
    
    SubtractionOperator(std::vector<Tag::Pointer> tags);

private:
    std::vector<Tag::Pointer> _tags;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "SubtractionOperator.txx"

#endif // _38f2f367_9431_49ca_8af8_2b7a79e7198d
