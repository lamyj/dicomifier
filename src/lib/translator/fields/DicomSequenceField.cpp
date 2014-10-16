/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "DicomSequenceField.h"

namespace dicomifier
{

namespace translator
{
    
DicomSequenceField
::DicomSequenceField()
    : Tag(), _tags({}), _perFrame(false)
{
    // Nothing to do
}

DicomSequenceField
::DicomSequenceField(dicomifier::TagAndRange const & tagrange, 
                     std::vector<Tag::Pointer> tags,
                     bool perframe)
    : Tag(), _dicomtags(tagrange), _tags(tags), _perFrame(perframe)
{
    // Nothing to do
}

DicomSequenceField
::~DicomSequenceField()
{
    // Nothing to do
}

void 
DicomSequenceField
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (dataset == NULL)
    {
        throw DicomifierException("Empty Dataset");
    }
    
    if (this->_perFrame)
    {
        dicomifier::FrameIndexGenerator generatorlocal(generator.get_indexMax());
        while (!generatorlocal.done())
        {
            DcmItem* item = NULL;
            dataset->findOrCreateSequenceItem(this->_dicomtags._tag, item, -2); // -2 = create new
            
            for (auto currentTag : this->_tags)
            {
                currentTag->run(brukerdataset, generatorlocal, item);
            }
            
            generatorlocal.next();
        }
    }
    else
    {
        for (auto i = this->_dicomtags._range._min; 
             i < this->_dicomtags._range._max; 
             i++)
        {
            DcmItem* item = NULL;
            dataset->findOrCreateSequenceItem(this->_dicomtags._tag, item, i);
            
            for (auto currentTag : this->_tags)
            {
                currentTag->run(brukerdataset, generator, item);
            }
        }
    }
}
    
} // namespace translator
    
} // namespace dicomifier
