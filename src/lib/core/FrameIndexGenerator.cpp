/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "FrameIndexGenerator.h"

namespace dicomifier
{
    
FrameIndexGenerator
::FrameIndexGenerator(std::vector<int> indexmax)
    :_indexMax(indexmax), _currentIndex(indexmax)
{
    if (this->_currentIndex.size() > 1)
    {
        // Be carefull: _currentIndex should be different from _indexMax
        //              for the first call of done()
        this->_currentIndex[0]++;
    }
}

FrameIndexGenerator
::~FrameIndexGenerator()
{
    // Nothing to do
}

bool
FrameIndexGenerator
::done() const
{
    for (auto index = 0; index < this->_currentIndex.size() - 1; index++)
    {
        if (this->_currentIndex[index] != this->_indexMax[index]-1)
        {
            return false;
        }
    }
    return true;
}

std::vector<int>
FrameIndexGenerator
::next()
{
    if (this->_currentIndex.size() > 1)
    {
        for (auto index = this->_currentIndex.size()-2; index != -1; index--)
        {
            // Increase current index
            this->_currentIndex[index]++;
            
            // If index reaches the max
            if (this->_currentIndex[index] >= this->_indexMax[index])
            {
                // Restart to 0
                this->_currentIndex[index] = 0;
                // continue, go to the next index
            }
            else
            {
                // increase done => stop
                break;
            }
        }
    }
    
    return this->_currentIndex;
}
    
} // namespace dicomifier
