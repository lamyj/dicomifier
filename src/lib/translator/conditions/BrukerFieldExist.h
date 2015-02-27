/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _89f07c95_97f3_4d46_84fb_01b6a3305a04
#define _89f07c95_97f3_4d46_84fb_01b6a3305a04

#include "ConditionBase.h"

namespace dicomifier
{
    
namespace translator
{
    
/**
 * @brief The BrukerFieldExist class
 */
class BrukerFieldExist : public ConditionBase
{
public:
    typedef BrukerFieldExist Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of BrukerFieldExist
    static Pointer New() { return Pointer(new Self()); }
    
    /**
     * @brief Create pointer to new instance of BrukerFieldExist
     * @param brukerFieldName: Name of searched Bruker field
     * @return new instance of BrukerFieldExist
     */
    static Pointer New(std::string const & brukerFieldName)
        { return Pointer(new Self(brukerFieldName)); }
    
    /// Destroy the instance of BrukerFieldExist
    virtual ~BrukerFieldExist();
    
    /**
     * @brief eval: Search a given Bruker field in the Bruker dataset
     * @param dataset: DICOM data
     * @param brukerdataset: Bruker data
     * @return true if field exists, false otherwise
     */
    virtual bool eval(DcmItem* dataset,
                      dicomifier::bruker::Dataset* brukerdataset);

protected:
    /// Create an instance of BrukerFieldExist
    BrukerFieldExist();
    
    /**
     * @brief BrukerFieldExist
     * @param brukerfieldname
     */
    BrukerFieldExist(std::string const & brukerfieldname);

private:
    /// Name of searched Bruker field
    std::string _brukerFieldName;
    
};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _89f07c95_97f3_4d46_84fb_01b6a3305a04
