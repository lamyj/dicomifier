#include <iostream>

#include "core/conditions/All.h"
#include "core/conditions/True.h"
#include "core/conditions/False.h"

int main()
{
    auto true_ = router::conditions::True::New();
    auto false_ = router::conditions::False::New();
    
    auto anyTT = router::conditions::All::New(true_, true_);
    std::cout << "True and True = " << anyTT->eval() << std::endl;
    
    auto anyTF = router::conditions::All::New(true_, false_);
    std::cout << "True and False = " << anyTF->eval() << std::endl;
    
    auto anyFT = router::conditions::All::New(false_, true_);
    std::cout << "False and True = " << anyFT->eval() << std::endl;
    
    auto anyFF = router::conditions::All::New(false_, false_);
    std::cout << "False and False = " << anyFF->eval() << std::endl;
    
    return EXIT_SUCCESS;
}
