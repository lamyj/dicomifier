#ifndef _805413fc_20b1_422c_9b88_3395c07a47ca
#define _805413fc_20b1_422c_9b88_3395c07a47ca

#include <vector>

#include "Condition.h"

namespace dicomifier
{

namespace conditions
{

/**
 * @brief OR-combination of conditions.
 */
class Any: public Condition
{
public:
    typedef Any Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(Condition::ConstPointer left, Condition::ConstPointer right) { return Pointer(new Self(left, right)); }
    ~Any();

    virtual bool eval() const;
    
    static std::string get_class_name() { return "Any"; }

protected:
    Any();
    Any(Condition::ConstPointer left, Condition::ConstPointer right);

private:
    std::vector<Condition::ConstPointer> _children;

    Any(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace conditions

} // namespace dicomifier

#endif // _805413fc_20b1_422c_9b88_3395c07a47ca
