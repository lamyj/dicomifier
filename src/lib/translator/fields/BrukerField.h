/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2
#define _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2

#include "dicom/TagAndRange.h"
#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class BrukerField : public SubTag<VR>
{
public:
    typedef BrukerField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;
    
    /// Create pointer to new instance of DicomField
    static Pointer New();
    
    static Pointer New(std::string const & brukerFieldName);
    
    static Pointer New(std::string const & brukerFieldName, Range range);

    virtual ~BrukerField();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     std::vector<int> const & indexes,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const { return ECT_BrukerField; }
    
protected:
    BrukerField();
    
    BrukerField(std::string const & brukerfiledname, Range range);

private:
    std::string _brukerFieldName;
    Range _range;
    
};
    
} // namespace translator
    
} // namespace dicomifier

#include "BrukerField.txx"

#endif // _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2
