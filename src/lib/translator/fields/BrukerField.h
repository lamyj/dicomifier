/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2
#define _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2

#include "translator/Tag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class BrukerField : public Tag
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

    virtual ~BrukerField();
                     
    virtual void run(DcmDataset* dataset,
                     dicomifier::bruker::BrukerDataset* brukerdataset);
    
    virtual ClassType get_class_type() const { return ECT_BrukerField; }
    
    ArrayType get_array() const;
    
protected:
    BrukerField();
    
    BrukerField(std::string const & brukerfiledname);

private:
    std::string _brukerFieldName;
    
    ArrayType _array;
    
};
    
} // namespace translator
    
} // namespace dicomifier

#include "BrukerField.txx"

#endif // _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2
