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
    
/**
 * @brief The FrameIndexGenerator class
 * generate tuples of indexes
 */
class FrameIndexGenerator
{
public:
    /**
     * @brief FrameIndexGenerator: Create an instance of FrameIndexGenerator
     * @param indexmax: Vector containing the maximum values
     * @param countmax: Maximum number of iteration
     */
    FrameIndexGenerator(std::vector<int> indexmax, int countmax = -1);
    
    /// Destroy the FrameIndexGenerator
    virtual ~FrameIndexGenerator();
    
    /**
     * @brief done: Indicate if the maximum index has been reached
     * @return true if maximum is reached, false otherwise
     */
    bool done() const;
    
    /**
     * @brief next: Compute the next indexes
     */
    void next();
     
    /**
     * @brief get_index: return the current indexes
     * @return current indexes vector
     */
    std::vector<int> get_index() const;
    
    /**
     * @brief get_indexMax: getter for attribut indexMax
     * @return indexMax
     */
    std::vector<int> get_indexMax() const;
    
    /**
     * @brief get_step: getter for attribut currentStep
     * @return currentStep
     */
    int get_step() const;
    
    /**
     * @brief get_countMax: getter for attribut countMax
     * @return countMax
     */
    int get_countMax() const;
    
    /**
     * @brief compute_index: compute the current step ignoring given index
     * @param withoutindex: ignored indexes
     * @return current step
     */
    int compute_index(std::vector<int> withoutindex) const;

protected:
    /**
     * @brief computeCountMax: compute countMax with list of indexMax
     */
    void computeCountMax();

private:
    /// Vector of maximum indexes
    std::vector<int> _indexMax;
    // Be carefull: Index is from 0 to N-1
    /// Vector of current indexes
    std::vector<int> _currentIndex;
    
    /// Maximum value of generated indexes
    int _countMax;

    /// Current number of generated indexes
    int _currentStep;
    
};
    
} // namespace dicomifier

#endif // _b4478a62_9c5d_49b4_b029_441076bcda6c
