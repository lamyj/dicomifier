#ifndef NOT_H
#define NOT_H

#include "Condition.h"

namespace router
{
    
namespace conditions
{
    
/**
 * @brief Inverse of a condition.
 */
class Not: public Condition
{
public:
    typedef Not Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    static Pointer New() { return Pointer(new Self()); }
    static Pointer New(Condition::ConstPointer condition) { return Pointer(new Self(condition)); }
    
    /**
     * @brief Destructor
     */
    virtual ~Not();
    
    virtual bool eval() const;
    
protected:
    /**
     * @brief Constructor
     */
    Not();
    Not(Condition::ConstPointer condition);

private:
    Condition::ConstPointer _condition;

    Not(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace conditions
    
} // namespace router

#endif // NOT_H
