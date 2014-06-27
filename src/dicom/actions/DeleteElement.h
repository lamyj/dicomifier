#ifndef _7d7419ea_a474_491a_8a5a_86cd918c7629
#define _7d7419ea_a474_491a_8a5a_86cd918c7629

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"

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
    static Pointer New(DcmDataset * dataset, DcmTagKey tag);
    
    virtual ~DeleteElement();

    DcmDataset * get_dataset() const;
    void set_dataset(DcmDataset * dataset);

    DcmTag const & get_tag() const;
    void set_tag(DcmTag const & tag);

    virtual void run() const;
    
    static std::string get_class_name() { return "DeleteElement"; }

protected:
    DeleteElement();
    DeleteElement(DcmDataset * dataset, DcmTagKey tag);

private:
    DcmDataset * _dataset;
    DcmTag _tag;

    DeleteElement(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // actions

} // router

#endif // _7d7419ea_a474_491a_8a5a_86cd918c7629
