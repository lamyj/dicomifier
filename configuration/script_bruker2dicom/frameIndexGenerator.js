
// Create Class frameIndexGenerator (constructor)
dicomifier.frameIndexGenerator = function(frameGroups, countMax) {
    this.indexMax = [];
    this.currentIndex = [];
    this.countMax = countMax || -1;
    this.currentStep = 0;
    
    this.fillIndexMax(frameGroups);
    
    if (this.countMax === -1) {
        this.countMax = 1;
        for (var i = 0; i < this.indexMax.length; ++i)
        {
            if (this.indexMax[i] != 0)
            {
                this.countMax *= this.indexMax[i];
            }
        }
    }
}

// Create functions for frameIndexGenerator classes
/**
 * @brief Initialize frameIndexGenerator with the parsed frame groups
 * @param frameGroups: Frame groups
 */
dicomifier.frameIndexGenerator.prototype.fillIndexMax = 
    function(frameGroups) {
        for (var i = 0; i < frameGroups.length; ++i) {
            this.indexMax.push(frameGroups[i][0]);
            this.currentIndex.push(0);
        }
    }

/**
 * @brief Indicate if all indexes were generated
 * @return true if all indexes were generated, false otherwise
 */
dicomifier.frameIndexGenerator.prototype.done = function() {
    return new Boolean(this.currentStep >= this.countMax);
}

/**
 * @brief generate next index
 */
dicomifier.frameIndexGenerator.prototype.next = function() {
    ++this.currentStep;
    
    for (var index = this.currentIndex.length-1; index != -1; --index) {
        // Increase current index
        ++this.currentIndex[index];
        
        // If index reaches the max
        if (this.currentIndex[index] >= this.indexMax[index]) {
            // Restart to 0
            this.currentIndex[index] = 0;
            // continue, go to the next index
        }
        else {
            // increase done => stop
            break;
        }
    }
}


/**
 * @brief Parsing frame group from a given Bruker Dataset
 * @param brukerDataset: Bruker Dataset
 * @return [ [size, name, parameters], ... ]
 *         with parameters = [ [ name, start_index ], ... ]
*/
dicomifier.getFrameGroups = function(brukerDataset) {
    if (brukerDataset === undefined || brukerDataset === null) {
        throw new dicomifier.Exception('brukerDataset is empty');
    }
    
    var array = [];
    
    for (var i = 0; i < brukerDataset.VisuFGOrderDesc.length; ++i) {
        var subarray = [];
        subarray[0] = brukerDataset.VisuFGOrderDesc[0][0];
        subarray[1] = brukerDataset.VisuFGOrderDesc[0][1];
        var parameters = [];
        for (var j = parseInt(brukerDataset.VisuFGOrderDesc[0][3]); 
             j < brukerDataset.VisuFGOrderDesc[0][4]; ++j) {
            parameters.push(brukerDataset.VisuGroupDepVals[j]);
        }
        
        subarray[2] = parameters;
        array.push(subarray);
    }
    
    // CAUTION: the frame groups are listed in innermost-to-outermost
    // order, while FrameIndexGenerator uses outermost-to-innermost order.
    // Invert now, to match the order of FrameIndexGenerator.
    array.reverse();
        
    return array;
}

/**
 * @brief Get frame index and start index if a given bruker field 
 *        is a frameGroup
 * @param brukerDataset: Bruker Dataset
 * @param brukerElement: Bruker field to check
 * @return [ frameGroup index, start index ]
 */
dicomifier.getFrameGroupIndex = function(brukerDataset, brukerElement) {
    if (brukerDataset === undefined || brukerDataset === null) {
        throw new dicomifier.Exception('brukerDataset is empty');
    }
    
    if (brukerElement === undefined || brukerElement === null) {
        return null;
    }
    
    var frameGroups = dicomifier.getFrameGroups(brukerDataset);
    
    for (var index = 0; index < frameGroups.length; ++index) {
        for (var indexParam = 0; 
             indexParam < frameGroups[index][2].length; ++indexParam) {
            if (brukerElement === frameGroups[index][2][indexParam][0]) {
                return [index, frameGroups[index][2][indexParam][1]];
            }
        }
    }

    return null;
}
