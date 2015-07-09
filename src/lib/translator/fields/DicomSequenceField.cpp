/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>

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
    : Tag(), _tags(tags), _dicomtags(tagrange), _perFrame(perframe)
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
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (dataset == NULL)
    {
        throw DicomifierException("Empty Dataset");
    }

    OFCondition condition = EC_Normal;
    
    if (this->_perFrame)
    {
        dicomifier::FrameIndexGenerator generatorlocal(generator.get_indexMax());
        while (!generatorlocal.done())
        {
            DcmItem* item = NULL;
            condition = dataset->findOrCreateSequenceItem(this->_dicomtags._tag, item, -2); // -2 = create new

            if (condition.bad())
            {
                std::stringstream stream;
                stream << condition.text();
                throw DicomifierException(stream.str());
            }
            
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
            // Empty sequence
            if (this->_tags.size() == 0)
            {
                condition = dataset->insertEmptyElement(this->_dicomtags._tag);

                if (condition.bad())
                {
                    std::stringstream stream;
                    stream << condition.text();
                    throw DicomifierException(stream.str());
                }
            }
            else
            {
                DcmItem* item = NULL;
                condition = dataset->findOrCreateSequenceItem(this->_dicomtags._tag, item, i);

                if (condition.bad())
                {
                    std::stringstream stream;
                    stream << condition.text();
                    throw DicomifierException(stream.str());
                }

                for (auto currentTag : this->_tags)
                {
                    currentTag->run(brukerdataset, generator, item);
                }
            }
        }
    }
}
    
} // namespace translator
    
} // namespace dicomifier
