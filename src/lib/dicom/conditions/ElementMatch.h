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

#include "../ElementTraits.h"
#include "lib/core/conditions/Condition.h"
#include "lib/core/Factory.h"

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
    static Pointer New(DcmDataset * dataset, DcmTagKey tag, ValueType const & value);
    static Pointer New(DcmDataset * dataset, DcmTagKey tag, ArrayType const & array);
    
    /**
     * @brief Destructor
     */
    virtual ~ElementMatch();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    DcmTag const & get_tag() const;
    void set_tag(DcmTag const & tag);

    ArrayType const & get_value() const;
    void set_value(ValueType const & value);
    void set_value(ArrayType const & array);

    virtual bool eval() const;
    
    static std::string get_class_name() { return "ElementMatch"; }

    static unsigned int const registration = Factory::get_instance().register_<ElementMatch>();

protected:
    /**
     * @brief Constructor
     */
    ElementMatch();
    ElementMatch(DcmDataset * dataset, DcmTagKey tag, ValueType const & value);
    ElementMatch(DcmDataset * dataset, DcmTagKey tag, ArrayType const & array);

private:
    DcmDataset * _dataset;
    DcmTag _tag;

    ArrayType _array;

    ElementMatch(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace conditions

} // namespace dicomifier

#include "ElementMatch.txx"

#endif // _99df1b4a_c205_45f9_b1d7_2bb54df6a624
