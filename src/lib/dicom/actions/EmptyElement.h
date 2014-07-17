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
    
    static Pointer New();
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags);
    
    virtual ~EmptyElement();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    std::vector<TagAndRange> const & get_tags() const { return this->_tags; }
    void set_tags(std::vector<TagAndRange> const & tags) { this->_tags = tags; }

    virtual void run() const;
    
    static std::string get_class_name() { return "EmptyElement"; }

protected:
    EmptyElement();
    EmptyElement(DcmDataset * dataset, std::vector<TagAndRange> tags);
    
    void emptyItem(int indice, DcmItem* dataset) const;

private:
    DcmDataset * _dataset;
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
