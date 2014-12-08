/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2
#define _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2

#include "dicom/TagAndRange.h"
#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The BrukerField class
 */
template<DcmEVR VR>
class BrukerField : public SubTag<VR>
{
public:
    typedef BrukerField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef typename ElementTraits<VR>::ValueType ValueType;
    typedef std::vector<ValueType> ArrayType;
    
    /// Create pointer to new instance of BrukerField
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of BrukerField
     * @param brukerFieldName: Name of the Bruker field data
     * @return new instance of BrukerField
     */
    static Pointer New(std::string const & brukerFieldName);
    
    /**
     * @brief Create pointer to new instance of BrukerField
     * @param brukerFieldName: Name of the Bruker field data
     * @param range: Range of Bruker field to read
     * @return new instance of BrukerField
     */
    static Pointer New(std::string const & brukerFieldName, Range range);

    /// Destroy the instance of BrukerField
    virtual ~BrukerField();
                     
    /**
     * @brief run: Read and get value of Bruker field
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of BrukerField
    BrukerField();
    
    /**
     * @brief Create an instance of BrukerField
     * @param brukerfiledname: Name of the Bruker field data
     * @param range: Range of Bruker field to read
     */
    BrukerField(std::string const & brukerfiledname, Range range);

private:
    /// Name of the Bruker field data
    std::string _brukerFieldName;

    /// Range of Bruker field to read
    Range _range;
    
};
    
} // namespace translator
    
} // namespace dicomifier

#include "BrukerField.txx"

#endif // _dfbe0188_c0b5_41bb_93c8_92c25fdfc3b2
