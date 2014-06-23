#include <iostream>

#include <dcmtk/dcmdata/dctk.h>

#include "core/conditions/Any.h"
#include "core/conditions/True.h"
#include "core/conditions/False.h"

int main()
{
    auto true_ = router::conditions::True::New();
    auto false_ = router::conditions::False::New();

    auto any = router::conditions::Any::New(false_, true_);
    std::cout << any->eval() << std::endl;
}
