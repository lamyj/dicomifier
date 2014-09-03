/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c9fb76f8_f8b5_4fc3_97e4_53c6527c948f
#define _c9fb76f8_f8b5_4fc3_97e4_53c6527c948f

#include <boost/property_tree/ptree.hpp>

#include "Tag.h"

namespace dicomifier
{
    
namespace translator
{

class TranslationCreatorBase
{
public:
    typedef TranslationCreatorBase Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    virtual ~TranslationCreatorBase();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr) = 0;
    
protected:
    TranslationCreatorBase();

private:
    TranslationCreatorBase(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};

} // namespace translator

} // namespace dicomifier

#endif // _c9fb76f8_f8b5_4fc3_97e4_53c6527c948f
