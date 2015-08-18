var _module = namespace('dicomifier.bruker2dicom');

/// @brief Constructor of class FrameIndexGenerator
_module.FrameIndexGenerator = function(frameGroups, countMax) {
    this.indexMax = [];
    this.currentIndex = [];
    this.countMax = countMax || -1;
    this.currentStep = 0;

    this.fillIndexMax(frameGroups);

    if (this.countMax === -1) {
        this.countMax = 1;
        for (var i = 0; i < this.indexMax.length; ++i)
        {
            if (this.indexMax[i] !== 0)
            {
                this.countMax *= this.indexMax[i];
            }
        }
    }
};

/// @brief Initialize frameIndexGenerator with the parsed frame groups
_module.FrameIndexGenerator.prototype.fillIndexMax = function(frameGroups) {
    for (var i = 0; i < frameGroups.length; ++i) {
        this.indexMax.push(frameGroups[i][0]);
        this.currentIndex.push(0);
    }
};

/// @brief Indicate if all indexes were generated
_module.FrameIndexGenerator.prototype.done = function() {
    return (this.currentStep >= this.countMax);
};

/// @brief generate next index
_module.FrameIndexGenerator.prototype.next = function() {
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
};


/**
 * @brief Parsing frame group from a given Bruker Dataset
 * @return [ [size, name, parameters], ... ]
 *         with parameters = [ [ name, start_index ], ... ]
*/
_module.getFrameGroups = function(brukerDataset) {
    if (brukerDataset === undefined || brukerDataset === null) {
        throw new dicomifier.Exception('Bruker dataset is empty');
    }

    var array = [];

    for (var i = 0; i < brukerDataset.VisuFGOrderDesc.length; ++i) {
        var description = brukerDataset.VisuFGOrderDesc[i];

        var subarray = [];
        subarray[0] = description[0];
        subarray[1] = description[1];
        var parameters = [];
        for(var j = parseInt(description[3]); j < description[3]+description[4]; ++j) {
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
 * @return [ frameGroup index, start index ]
 */
_module.getFrameGroupIndex = function(brukerDataset, brukerElement) {
    if (brukerDataset === undefined || brukerDataset === null) {
        throw new dicomifier.Exception('Bruker dataset is empty');
    }

    if (brukerElement === undefined || brukerElement === null) {
        return null;
    }

    var frameGroups = _module.getFrameGroups(brukerDataset);

    for (var index = 0; index < frameGroups.length; ++index) {
        var parameters = frameGroups[index][2];

        for(var indexParam = 0; indexParam < parameters.length; ++indexParam) {
            if (brukerElement === parameters[indexParam][0]) {
                return [index, parameters[indexParam][1]];
            }
        }
    }

    return null;
};
