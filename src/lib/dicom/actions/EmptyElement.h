/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _221f51f1_559b_41f0_ad3a_b97ece3ecf91
#define _221f51f1_559b_41f0_ad3a_b97ece3ecf91

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"
#include "dicom/ElementTraits.h"
#include "dicom/TagAndRange.h"

namespace dicomifier
{
    
namespace actions
{
    
/**
 * @brief Set an element in the dataset to an empty value. 
 *        If the element is not present in the dataset, it is inserted.
 */
class EmptyElement: public Action
{
public:
    typedef EmptyElement Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of EmptyElement
    static Pointer New() { return Pointer(new Self()); }

    /**
     * @brief Create pointer to new instance of EmptyElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to modify
     * @return new instance of EmptyElement
     */
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags)
        { return Pointer(new Self(dataset, tags)); }
    
    /// Destroy the instance of EmptyElement
    virtual ~EmptyElement();

    /**
     * @brief get_dataset: getter for attribut dataset
     * @return dataset
     */
    DcmDataset * get_dataset() const { return this->_dataset; }

    /**
     * @brief set_dataset: setter for attribut dataset
     * @param dataset: new value
     */
    void set_dataset(DcmDataset * dataset) { this->_dataset = dataset; }

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
     * @brief run: Execute the EmptyElement Action
     */
    virtual void run() const;

    /**
     * @brief get_class_name: return this class name
     * @return EmptyElement
     */
    static std::string get_class_name() { return "EmptyElement"; }

protected:
    /// Create an instance of EmptyElement
    EmptyElement();

    /**
     * @brief Create an instance of EmptyElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to modify
     */
    EmptyElement(DcmDataset * dataset, std::vector<TagAndRange> tags);
    
    /**
     * @brief emptyItem: Remove value for a given tag
     * @param indice: current index in the tags vector
     * @param dataset: current level in the dataset (dataset or sequence)
     */
    void emptyItem(int indice, DcmItem* dataset) const;

private:
    /// Dataset to modify
    DcmDataset * _dataset;

    /// Tag to modify
    std::vector<TagAndRange> _tags;

    EmptyElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct ActionEmptyElement
    {
        DcmItem* dataset;
        TagAndRange tagandrange;
        DcmElement* element;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace actions

} // namespace dicomifier

#endif // _221f51f1_559b_41f0_ad3a_b97ece3ecf91
