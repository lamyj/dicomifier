#ifndef _ada23069_55db_424c_97cc_9f68889e9a2f
#define _ada23069_55db_424c_97cc_9f68889e9a2f

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"
#include "core/Factory.h"
#include "dicom/ElementTraits.h"

namespace router
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
    static Pointer New(DcmDataset * dataset, DcmTagKey tag, ValueType const & value);
    static Pointer New(DcmDataset * dataset, DcmTagKey tag, ArrayType const & array);

    ~SetElement();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    DcmTag const & get_tag() const;
    void set_tag(DcmTag const & tag);

    ArrayType const & get_value() const;
    void set_value(ValueType const & value);
    void set_value(ArrayType const & array);

    virtual void run() const;
    
    static std::string get_class_name() { return "SetElement"; }

    static unsigned int const registration = Factory::get_instance().register_<SetElement>();

protected:
    SetElement();

    SetElement(DcmDataset * dataset, DcmTagKey tag, ValueType const & value);
    SetElement(DcmDataset * dataset, DcmTagKey tag, ArrayType const & array);

private:
    DcmDataset * _dataset;
    DcmTag _tag;

    ArrayType _array;

    SetElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace actions

} // namespace router

#include "SetElement.txx"

#endif // _ada23069_55db_424c_97cc_9f68889e9a2f
