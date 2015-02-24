/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e100969d_d08f_4053_9240_9d381b9023b0
#define _e100969d_d08f_4053_9240_9d381b9023b0

#include <memory>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "bruker/BrukerDataset.h"
#include "core/FrameIndexGenerator.h"
#include "dicom/ElementTraits.h"

namespace dicomifier
{
    
namespace translator
{
    
/**
 * @brief The Tag class: Abstact base class for translation tag
 */
class Tag
{
public:
    typedef Tag Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Destroy the instance of Tag
    virtual ~Tag();
    
    /**
     * @brief run: Call to execute translation. Should be override by inherit classes
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset) = 0;

protected:
    /// Create an instance of Tag
    Tag();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#endif // _e100969d_d08f_4053_9240_9d381b9023b0
