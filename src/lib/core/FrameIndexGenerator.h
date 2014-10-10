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
    FrameIndexGenerator(std::vector<int> indexmax, int countmax = -1);
    
    virtual ~FrameIndexGenerator();
    
    bool done() const;
    
    void next();
     
    std::vector<int> get_index() const;
    
    int get_step() const;

protected:
    void computeCountMax();

private:
    std::vector<int> _indexMax;
    // Be carefull: Index is from 0 to N-1
    std::vector<int> _currentIndex;
    
    int _countMax;
    int _currentStep;
    
};
    
} // namespace dicomifier

#endif // _b4478a62_9c5d_49b4_b029_441076bcda6c
