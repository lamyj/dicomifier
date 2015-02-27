/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b2f009c1_3a10_419b_9d30_6b9986e25ac2
#define _b2f009c1_3a10_419b_9d30_6b9986e25ac2

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The RegExFilter class
 */
template<DcmEVR VR>
class RegExFilter : public SubTag<VR>
{
public:
    typedef RegExFilter Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of RegExFilter
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of RegExFilter
     * @param tag: Bruker Field to process
     * @param expression: Regular expression
     * @return new instance of RegExFilter
     */
    static Pointer New(Tag::Pointer tag, std::string const & expression);

    /// Destroy the instance of RegExFilter
    virtual ~RegExFilter();
    
    /**
     * @brief run: Get data from Bruker field using a regular expression
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of RegExFilter
    RegExFilter();
    
    /**
     * @brief Create an instance of RegExFilter
     * @param tag: Bruker Field to process
     * @param expression: Regular expression
     */
    RegExFilter(Tag::Pointer tag, std::string const & expression);

private:
    /// Bruker Field to process
    Tag::Pointer _tag;
    
    /// Regular expression
    std::string _expression;

};

} // namespace translator
    
} // namespace dicomifier

#include "RegExFilter.txx"

#endif // _b2f009c1_3a10_419b_9d30_6b9986e25ac2
