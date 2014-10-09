/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c7990a8f_023a_4a49_907a_eb36b7e33b4e
#define _c7990a8f_023a_4a49_907a_eb36b7e33b4e

#include "translator/Tag.h"

namespace dicomifier
{
    
namespace translator
{
    
class TestField : public Tag
{
public:
    typedef TestField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of TestField
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~TestField();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     std::vector<int> const & indexes,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const { return ECT_TestField; }
    
protected:

private:
    TestField();
    
};
    
} // namespace translator

} // namespace dicomifier

#endif // _c7990a8f_023a_4a49_907a_eb36b7e33b4e
