/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _99df1b4a_c205_45f9_b1d7_2bb54df6a624
#define _99df1b4a_c205_45f9_b1d7_2bb54df6a624

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/conditions/Condition.h"
#include "core/Factory.h"
#include "dicom/ElementTraits.h"
#include "dicom/TagAndRange.h"

namespace dicomifier
{
    
namespace conditions
{
    
/**
 * @brief Test if an element in a dataset matches a value.
 */
template<DcmEVR VR>
class ElementMatch: public Condition
{
public:
    typedef ElementMatch Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;
    
    static Pointer New();
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                       ValueType const & value);
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                       ArrayType const & array);
    
    /**
     * @brief Destructor
     */
    virtual ~ElementMatch();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    std::vector<TagAndRange> const & get_tags() const { return this->_tags; }
    void set_tags(std::vector<TagAndRange> const & tags) { this->_tags = tags; }

    ArrayType const & get_value() const;
    void set_value(ValueType const & value);
    void set_value(ArrayType const & array);

    virtual bool eval() const;
    
    static std::string get_class_name() { return "ElementMatch"; }

protected:
    /**
     * @brief Constructor
     */
    ElementMatch();
    ElementMatch(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                 ValueType const & value);
    ElementMatch(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                 ArrayType const & array);
               
    bool matchItem(int indice, DcmItem* dataset) const;

private:
    DcmDataset * _dataset;
    
    std::vector<TagAndRange> _tags;

    ArrayType _array;

    ElementMatch(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace conditions

} // namespace dicomifier

#include "ElementMatch.txx"

#endif // _99df1b4a_c205_45f9_b1d7_2bb54df6a624
