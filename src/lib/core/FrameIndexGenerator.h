/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b4478a62_9c5d_49b4_b029_441076bcda6c
#define _b4478a62_9c5d_49b4_b029_441076bcda6c

#include <vector>

namespace dicomifier
{
    
class FrameIndexGenerator
{
public:
    FrameIndexGenerator(std::vector<int> indexmax);
    
    virtual ~FrameIndexGenerator();
    
    bool done() const;
    
    std::vector<int> next();

protected:

private:
    std::vector<int> _indexMax;
    // Be carefull: Index is from 0 to N-1
    std::vector<int> _currentIndex;
    
};
    
} // namespace dicomifier

#endif // _b4478a62_9c5d_49b4_b029_441076bcda6c
