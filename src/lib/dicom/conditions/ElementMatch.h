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
    
    /// Create pointer to new instance of ElementMatch
    static Pointer New();

    /**
     * @brief Create pointer to new instance of ElementMatch
     * @param dataset: tested DICOM Dataset
     * @param tags: tested Tag
     * @param value: tested Value
     * @return new instance of ElementMatch
     */
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                       ValueType const & value);

    /**
     * @brief Create pointer to new instance of ElementMatch
     * @param dataset: tested DICOM Dataset
     * @param tags: tested Tag
     * @param array: tested Values
     * @return new instance of ElementMatch
     */
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                       ArrayType const & array);
    
    /// Destroy the instance of ElementMatch
    virtual ~ElementMatch();

    /**
     * @brief get_dataset: getter for attribut dataset
     * @return dataset
     */
    DcmDataset * get_dataset() const;

    /**
     * @brief set_dataset: setter for attribut dataset
     * @param dataset: new value
     */
    void set_dataset(DcmDataset * dataset);

    /**
     * @brief get_tags: getter for attribut tags
     * @return tags
     */
    std::vector<TagAndRange> const & get_tags() const { return this->_tags; }

    /**
     * @brief set_tags: setter for attribut tags
     * @param tags: new value
     */
    void set_tags(std::vector<TagAndRange> const & tags) { this->_tags = tags; }

    /**
     * @brief get_value: getter for attribut array
     * @return array
     */
    ArrayType const & get_value() const;

    /**
     * @brief set_value: setter for attribut array
     * @param value: new value
     */
    void set_value(ValueType const & value);

    /**
     * @brief set_value: setter for attribut array
     * @param array: new values
     */
    void set_value(ArrayType const & array);

    /**
     * @brief Evaluate the condition.
     * @return true if tested values match, false otherwise
     */
    virtual bool eval() const;
    
    /**
     * @brief get_class_name: Get this class name
     * @return ElementMatch
     */
    static std::string get_class_name() { return "ElementMatch"; }

protected:
    /// Create an instance of ElementMatch
    ElementMatch();

    /**
     * @brief Create an instance of ElementMatch
     * @param dataset: tested DICOM Dataset
     * @param tags: tested Tag
     * @param value: tested Value
     */
    ElementMatch(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                 ValueType const & value);

    /**
     * @brief Create an instance of ElementMatch
     * @param dataset: tested DICOM Dataset
     * @param tags: tested Tag
     * @param array: tested Values
     */
    ElementMatch(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                 ArrayType const & array);
               
    /**
     * @brief matchItem: Search values in the dataset
     * @param indice: current index in the tags vector
     * @param dataset: current level in the dataset (dataset or sequence)
     * @return
     */
    bool matchItem(int indice, DcmItem* dataset) const;

private:
    /// tested DICOM Dataset
    DcmDataset * _dataset;
    
    /// tested Tag
    std::vector<TagAndRange> _tags;

    /// tested Values
    ArrayType _array;

    ElementMatch(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace conditions

} // namespace dicomifier

#include "ElementMatch.txx"

#endif // _99df1b4a_c205_45f9_b1d7_2bb54df6a624
