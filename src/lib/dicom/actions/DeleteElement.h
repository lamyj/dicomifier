/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7d7419ea_a474_491a_8a5a_86cd918c7629
#define _7d7419ea_a474_491a_8a5a_86cd918c7629

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
 * @brief Remove an element from a dataset. 
 *        If the element is not in the dataset, nothing happens.
 */
class DeleteElement: public Action
{
public:
    typedef DeleteElement Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DeleteElement
    static Pointer New() { return Pointer(new Self()); }

    /**
     * @brief Create pointer to new instance of DeleteElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to remove
     * @return new instance of DeleteElement
     */
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags)
        { return Pointer(new Self(dataset, tags)); }
    
    /// Destroy the instance of DeleteElement
    virtual ~DeleteElement();

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
     * @brief run: Execute the DeleteElement Action
     */
    virtual void run() const;

    /**
     * @brief get_class_name: return this class name
     * @return DeleteElement
     */
    static std::string get_class_name() { return "DeleteElement"; }

protected:
    /// Create an instance of DeleteElement
    DeleteElement();

    /**
     * @brief Create an instance of DeleteElement
     * @param dataset: Dataset to modify
     * @param tags: Tag to remove
     */
    DeleteElement(DcmDataset * dataset, std::vector<TagAndRange> tags);
    
    /**
     * @brief removeItem: Remove the given tag
     * @param indice: current index in the tags vector
     * @param dataset: current level in the dataset (dataset or sequence)
     */
    void removeItem(int indice, DcmItem* dataset) const;

private:
    /// Dataset to modify
    DcmDataset * _dataset;
    
    /// Tag to remove
    std::vector<TagAndRange> _tags;

    DeleteElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct ActionDeleteElement
    {
        DcmItem* dataset;
        TagAndRange tagandrange;
        DcmElement* element;
        template<DcmEVR VR> void run() const;
    };
    
};
    
} // namespace actions

} // namespace dicomifier

#endif // _7d7419ea_a474_491a_8a5a_86cd918c7629
