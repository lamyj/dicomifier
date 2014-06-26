#ifndef _99df1b4a_c205_45f9_b1d7_2bb54df6a624
#define _99df1b4a_c205_45f9_b1d7_2bb54df6a624

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/conditions/Condition.h"

#include "../ElementTraits.h"

namespace router
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

} // namespace router

#include "ElementMatch.txx"

#endif // ELEMENTMATCH_H
