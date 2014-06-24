#include <iostream>

#include "core/conditions/All.h"
#include "core/conditions/True.h"
#include "core/conditions/False.h"

int main()
{
    auto true1_ = router::conditions::True::New();
    auto true2_ = router::conditions::True::New();
    auto false1_ = router::conditions::False::New();
    auto false2_ = router::conditions::False::New();
    
    auto anyTT = router::conditions::All::New(true1_, true2_);
    std::cout << "True and True = " << anyTT->eval() << std::endl;
    
    auto anyTF = router::conditions::All::New(true1_, false1_);
    std::cout << "True and False = " << anyTF->eval() << std::endl;
    
    auto anyFT = router::conditions::All::New(false2_, true2_);
    std::cout << "False and True = " << anyFT->eval() << std::endl;
    
    auto anyFF = router::conditions::All::New(false1_, false2_);
    std::cout << "False and False = " << anyFF->eval() << std::endl;
    
    return EXIT_SUCCESS;
}
