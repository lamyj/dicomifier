/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f45db991_65f2_4afe_9bf6_fc39dc07035d
#define _f45db991_65f2_4afe_9bf6_fc39dc07035d

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{

/**
 * @brief The DateGenerator class
 */
template<DcmEVR VR>
class DateGenerator : public SubTag<VR>
{
public:
    typedef DateGenerator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DateGenerator
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of DateGenerator
     * @param tag: Bruker Date/Time field
     * @param inputformat: DateTime input format
     * @param outputformat: DateTime output format
     * @return new instance of DateGenerator
     */
    static Pointer New(Tag::Pointer tag, std::string const & inputformat, 
                       std::string const & outputformat);

    /// Destroy the instance of DateGenerator
    virtual ~DateGenerator();
    
    /**
     * @brief run: Generate datetime or convert Bruker datetime field format into
     *             DICOM datetime format
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::Dataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
protected:
    /// Create an instance of DateGenerator
    DateGenerator();
    
    /**
     * @brief Create an instance of DateGenerator
     * @param tag: Bruker Date/Time field
     * @param inputformat: DateTime input format
     * @param outputformat: DateTime output format
     */
    DateGenerator(Tag::Pointer tag, std::string const & inputformat, 
                  std::string const & outputformat);

private:
    /// Bruker Date/Time field
    Tag::Pointer _tag;
    
    /// DateTime input format
    std::string _inputFormat;

    /// DateTime output format
    std::string _outputFormat;

};

} // namespace translator
    
} // namespace dicomifier

#include "DateGenerator.txx"

#endif // _f45db991_65f2_4afe_9bf6_fc39dc07035d

