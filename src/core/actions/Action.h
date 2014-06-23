#ifndef _fb0e1e31_d194_46fb_84ea_73b7278b093d
#define _fb0e1e31_d194_46fb_84ea_73b7278b093d

#include <memory>

namespace router
{

namespace actions
{

/**
 * @brief Abstract base class for all actions.
 */
class Action
{
public:
    typedef Action Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /**
     * @brief Destructor.
     *
     * The destructor must be public, since shared_ptr must be able to call it.
     */
    virtual ~Action();

    /**
     * @brief Run the action.
     */
    virtual void run() const =0;

protected:
    /**
     * @brief Constructor.
     *
     * The default constructor (and other constructors) shall be protected.
     */
    Action();

private:
    Action(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
};

} // namespace actions

} // namespace router

#endif // _fb0e1e31_d194_46fb_84ea_73b7278b093d
