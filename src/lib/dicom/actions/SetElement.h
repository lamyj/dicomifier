/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ada23069_55db_424c_97cc_9f68889e9a2f
#define _ada23069_55db_424c_97cc_9f68889e9a2f

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"
#include "core/Factory.h"
#include "dicom/ElementTraits.h"
#include "dicom/TagAndRange.h"

namespace dicomifier
{

namespace actions
{

/**
 * @brief Set an element in a dataset, creating it if necessary.
 *
 * The value can be set either as an array or as a single element, which will
 * be handled as a 1-element array
 */
template<DcmEVR VR>
class SetElement: public Action
{
public:
    typedef SetElement<VR> Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;

    /// Create pointer to new instance of SetElement
    static Pointer New();

    /**
     * @brief Create pointer to new instance of SetElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to modify
     * @param value: value to set
     * @return
     */
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags,
                       ValueType const & value);

    /**
     * @brief Create pointer to new instance of SetElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to modify
     * @param array: values to set
     * @return
     */
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                       ArrayType const & array);

    /// Destroy the instance of SetElement
    virtual ~SetElement();

    /**
     * @brief get_dataset: getter for attribut dataset
     * @returndataset
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
     * @brief run: Execute the SetElement Action
     */
    virtual void run() const;
    
    /**
     * @brief get_class_name: return this class name
     * @return SetElement
     */
    static std::string get_class_name() { return "SetElement"; }

protected:
    /// Create an instance of SetElement
    SetElement();

    /**
     * @brief Create an instance of SetElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to modify
     * @param value: value to set
     */
    SetElement(DcmDataset * dataset, std::vector<TagAndRange> tags, 
               ValueType const & value);

    /**
     * @brief Create an instance of SetElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to modify
     * @param array: values to set
     */
    SetElement(DcmDataset * dataset, std::vector<TagAndRange> tags, 
               ArrayType const & array);
               
    /**
     * @brief setItem: Set the given tags
     * @param indice: current index in the tags vector
     * @param dataset: current level in the dataset (dataset or sequence)
     */
    void setItem(int indice, DcmItem* dataset) const;

private:
    /// Dataset to modify
    DcmDataset * _dataset;
    
    /// Tag to modify
    std::vector<TagAndRange> _tags;

    /// Values to set
    ArrayType _array;

    SetElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace actions

} // namespace dicomifier

#include "SetElement.txx"

#endif // _ada23069_55db_424c_97cc_9f68889e9a2f
