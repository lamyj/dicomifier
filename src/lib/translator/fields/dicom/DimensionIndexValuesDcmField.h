/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _2ff027d3_18a0_45d6_88db_9c57775cddda
#define _2ff027d3_18a0_45d6_88db_9c57775cddda

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class DimensionIndexValuesDcmField : public SubTag<VR>
{
public:
    typedef DimensionIndexValuesDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DimensionIndexValuesDcmField
    static Pointer New();
    
    virtual ~DimensionIndexValuesDcmField();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    virtual ClassType get_class_type() const 
            { return ECT_DimensionIndexValuesDcmField; }

protected:
    DimensionIndexValuesDcmField();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#include "DimensionIndexValuesDcmField.txx"

#endif // _2ff027d3_18a0_45d6_88db_9c57775cddda
