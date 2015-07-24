
// Create Class frameIndexGenerator (constructor)
dicomifier.frameIndexGenerator = function(brukerDataset, countMax) {
    this.indexMax = [];
    this.currentIndex = [];
    this.countMax = countMax || -1;
    this.currentStep = 0;
    
    this.fillIndexMax(brukerDataset);
    
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
dicomifier.frameIndexGenerator.prototype.fillIndexMax = 
    function(brukerDataset) {
        for (var i = 0; i < brukerDataset.VisuFGOrderDesc.length; ++i) {
            this.indexMax.push(brukerDataset.VisuFGOrderDesc[i][0]);
        }
    }

dicomifier.frameIndexGenerator.prototype.done = function() {
    return new Boolean(this.currentStep >= this.countMax);
}

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
