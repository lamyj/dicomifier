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
    
template<DcmEVR VR>
class DateGenerator : public SubTag<VR>
{
public:
    typedef DateGenerator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DateGenerator
    static Pointer New();
    
    static Pointer New(Tag::Pointer tag, std::string const & inputformat, 
                       std::string const & outputformat);

    virtual ~DateGenerator();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     std::vector<int> const & indexes,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const { return ECT_DateGenerator; }
    
protected:
    DateGenerator();
    
    DateGenerator(Tag::Pointer tag, std::string const & inputformat, 
                  std::string const & outputformat);

private:
    Tag::Pointer _tag;
    
    std::string _inputFormat;
    std::string _outputFormat;

};

} // namespace translator
    
} // namespace dicomifier

#include "DateGenerator.txx"

#endif // _f45db991_65f2_4afe_9bf6_fc39dc07035d

