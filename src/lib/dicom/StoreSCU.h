/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1b2f876e_1ad2_464d_9423_28181320aed0
#define _1b2f876e_1ad2_464d_9423_28181320aed0

#include "SCU.h"

#include <functional>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>

namespace dicomifier
{

/// SCU for C-Store services.
class StoreSCU: public SCU
{
public:
    /// Callback, following the semantics of DCMTK.
    typedef std::function<void(void *, T_DIMSE_StoreProgress *, 
        T_DIMSE_C_StoreRQ *)> Callback;
    
    /// Destructor.
    virtual ~StoreSCU();
    
    /// Set the affected SOP class based on the dataset.
    void set_affected_sop_class(DcmDataset const * dataset);
    
    /// Perform the C-STORE using a callback.
    void store(DcmDataset const * dataset, Callback callback, void * data=NULL,
        long bytes_count=0) const;
    
    /// Perform the C-store without a callback.
    void store(DcmDataset const * dataset, long bytes_count=0) const;
    
private:
    struct CallbackData
    {
        Callback callback;
        void * data;
    };
    
    /// Wrapper to map C++ std::function to DCMTK void *
    static void _callback_wrapper(void * data, 
        T_DIMSE_StoreProgress * progress, T_DIMSE_C_StoreRQ * request);
    
    /// Low-level store function
    void _store(DcmDataset const * dataset, 
        DIMSE_StoreUserCallback callback, void * data, 
        long bytes_count) const;
};

} // namespace dicomifier

#endif // _1b2f876e_1ad2_464d_9423_28181320aed0
