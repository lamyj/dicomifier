#ifndef _221f51f1_559b_41f0_ad3a_b97ece3ecf91
#define _221f51f1_559b_41f0_ad3a_b97ece3ecf91

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"

namespace router
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
    static Pointer New(DcmDataset * dataset, DcmTagKey tag);
    
    virtual ~EmptyElement();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    DcmTag const & get_tag() const;
    void set_tag(DcmTag const & tag);

    virtual void run() const;
    
    static std::string get_class_name() { return "EmptyElement"; }

protected:
    EmptyElement();
    EmptyElement(DcmDataset * dataset, DcmTagKey tag);

private:
    DcmDataset * _dataset;
    DcmTag _tag;

    EmptyElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace actions

} // namespace router

#endif // _221f51f1_559b_41f0_ad3a_b97ece3ecf91
