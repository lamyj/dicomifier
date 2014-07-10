/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _67550dfa_ac58_4f33_8e02_e15bab523e33
#define _67550dfa_ac58_4f33_8e02_e15bab523e33

#include "core/actions/Action.h"

namespace dicomifier
{
    
namespace actions
{
    
class None : public Action
{
public:
    typedef None Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~None();

    virtual void run() const;
    
    static std::string get_class_name() { return "None"; }

protected:
    None();

private:
    None(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace actions

} // namespace dicomifier

#endif // _67550dfa_ac58_4f33_8e02_e15bab523e33
