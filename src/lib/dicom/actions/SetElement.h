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

    static Pointer New();
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags,
                       ValueType const & value);
    static Pointer New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                       ArrayType const & array);

    ~SetElement();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    std::vector<TagAndRange> const & get_tags() const { return this->_tags; }
    void set_tags(std::vector<TagAndRange> const & tags) { this->_tags = tags; }

    ArrayType const & get_value() const;
    void set_value(ValueType const & value);
    void set_value(ArrayType const & array);

    virtual void run() const;
    
    static std::string get_class_name() { return "SetElement"; }

protected:
    SetElement();

    SetElement(DcmDataset * dataset, std::vector<TagAndRange> tags, 
               ValueType const & value);
    SetElement(DcmDataset * dataset, std::vector<TagAndRange> tags, 
               ArrayType const & array);
               
    void setItem(int indice, DcmItem* dataset) const;

private:
    DcmDataset * _dataset;
    
    std::vector<TagAndRange> _tags;

    ArrayType _array;

    SetElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace actions

} // namespace dicomifier

#include "SetElement.txx"

#endif // _ada23069_55db_424c_97cc_9f68889e9a2f
