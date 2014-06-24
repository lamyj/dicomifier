#ifndef ALL_H
#define ALL_H

#include "Condition.h"

#include <vector>

namespace router
{
    
namespace conditions
{
    
/**
 * @brief And-combination of several conditions.
 */
class All: public Condition
{
public:
    typedef All Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(Condition::ConstPointer left, Condition::ConstPointer right) { return Pointer(new Self(left, right)); }
    
    /**
     * Destructor
     */
    virtual ~All();

    virtual bool eval() const;
    
protected:
    /**
     * Constructor
     */
    All();
    All(Condition::ConstPointer left, Condition::ConstPointer right);

private:
    std::vector<Condition::ConstPointer> _children;

    All(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace conditions
    
} // namespace router

#endif // ALL_H
