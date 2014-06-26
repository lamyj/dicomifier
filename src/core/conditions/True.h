#ifndef _470a2cf4_c361_436f_9f8e_b0c22980b983
#define _470a2cf4_c361_436f_9f8e_b0c22980b983

#include "Condition.h"

namespace router
{

namespace conditions
{

/**
 * @brief Condition that is always true
 */
class True: public Condition
{
public:
    typedef True Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    static Pointer New() { return Pointer(new Self()); }
    ~True();

    virtual bool eval() const;

protected:
    True();

private:
    True(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace conditions

} // namespace router

#endif // _470a2cf4_c361_436f_9f8e_b0c22980b983
