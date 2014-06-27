#ifndef _48df5c83_5dd1_4a3c_9f5b_494bdcc45d60
#define _48df5c83_5dd1_4a3c_9f5b_494bdcc45d60

#include <functional>
#include <map>
#include <memory>

#include "Object.h"

namespace router
{
    
class Factory
{
public:
    static Factory & get_instance();
    
    virtual ~Factory();

    template<typename T>
    unsigned int register_();
    
    bool can_create(std::string const & class_) const;
    
    std::shared_ptr<Object> create(std::string const & class_) const;
    
protected:

private:
    typedef std::function<std::shared_ptr<Object>()> Creator;
    typedef std::map<std::string, Creator> CreatorMap;

    Factory();
    
    static Factory * _instance;
    CreatorMap _creators;

    // Purposely not implemented
    Factory(Factory const & other);
    void operator=(Factory const & other);
    
};
    
} // namespace router

#include "Factory.txx"

#endif // _48df5c83_5dd1_4a3c_9f5b_494bdcc45d60
