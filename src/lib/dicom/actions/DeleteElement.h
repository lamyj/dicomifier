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
    
    static Pointer New();
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags);
    
    virtual ~DeleteElement();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    std::vector<TagAndRange> const & get_tags() const { return this->_tags; }
    void set_tags(std::vector<TagAndRange> const & tags) { this->_tags = tags; }

    virtual void run() const;
    
    static std::string get_class_name() { return "DeleteElement"; }

protected:
    DeleteElement();
    DeleteElement(DcmDataset * dataset, std::vector<TagAndRange> tags);
    
    void removeItem(int indice, DcmItem* dataset) const;

private:
    DcmDataset * _dataset;
    
    std::vector<TagAndRange> _tags;

    DeleteElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct RemoveElement
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
