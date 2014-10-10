/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
#include <iostream>
#include "FrameIndexGenerator.h"

namespace dicomifier
{
    
FrameIndexGenerator
::FrameIndexGenerator(std::vector<int> indexmax, int countmax)
    :_indexMax(indexmax), _currentIndex({}), 
     _countMax(countmax), _currentStep(0)
{
    if (indexmax.size() > 0)
    {
        this->_currentIndex = std::vector<int>(indexmax.size(), 0);
    }
    
    if (this->_countMax == -1)
    {
        this->computeCountMax();
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
    return (this->_currentStep >= this->_countMax);
}

void
FrameIndexGenerator
::next()
{
    _currentStep++;
    
    for (auto index = this->_currentIndex.size()-1; index != -1; index--)
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

std::vector<int> 
FrameIndexGenerator
::get_index() const
{
    return this->_currentIndex;
}

int 
FrameIndexGenerator
::get_step() const
{
    return this->_currentStep;
}

void 
FrameIndexGenerator
::computeCountMax()
{
    int max = 1;
    for (auto value : this->_indexMax)
    {
        if (value != 0)
        {
            max *= value;
        }
    }
    this->_countMax = max;
}
    
} // namespace dicomifier
