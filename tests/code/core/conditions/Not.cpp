#include <iostream>

#include "core/conditions/Not.h"
#include "core/conditions/True.h"
#include "core/conditions/False.h"

int main()
{
    auto true_ = router::conditions::True::New();
    auto false_ = router::conditions::False::New();
    
    // testing with True condition
    auto nottrue = router::conditions::Not::New(true_);
    std::cout << "Not true = " << nottrue->eval() << std::endl;
    
    // testing with False condition
    auto notfalse = router::conditions::Not::New(false_);
    std::cout << "Not false = " << notfalse->eval() << std::endl;
    
    return EXIT_SUCCESS;
}
