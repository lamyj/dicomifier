/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE StoreSCU
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include <dicom/StoreSCU.h>
#include <core/DicomifierException.h>

#include "DcmQrSCP.h"

BOOST_AUTO_TEST_CASE(AffectedSOPClass)
{
    DcmDataset * dataset = new DcmDataset();
    dataset->putAndInsertOFStringArray(DCM_SOPClassUID, UID_MRImageStorage);
    
    dicomifier::StoreSCU scu;
    scu.set_affected_sop_class(dataset);
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), UID_MRImageStorage);
}

struct CounterCallback
{
    CounterCallback()
    {
        this->begin_count = 0;
        this->progressing_count = 0;
        this->end_count = 0;
    }
    
    void call(void * data, T_DIMSE_StoreProgress * progress, 
        T_DIMSE_C_StoreRQ * request)
    {
        if(progress->state == DIMSE_StoreBegin)
        {
            ++this->begin_count;
        }
        else if(progress->state == DIMSE_StoreProgressing)
        {
            ++this->progressing_count;
        }
        else if(progress->state == DIMSE_StoreEnd)
        {
            ++this->end_count;
        }
    }
    
    int begin_count;
    int progressing_count;
    int end_count;
};

BOOST_FIXTURE_TEST_CASE(Callback, DcmQrSCP)
{
    std::stringstream filename;
    filename << data_directory << "/" << "image.dcm";
    
    DcmDataset * dataset = NULL;
    {
        DcmFileFormat file;
        OFCondition const condition = file.loadFile(filename.str().c_str());
        if(!condition.good())
        {
            BOOST_FAIL("Could not read " + filename.str());
        }
        dataset = file.getAndRemoveDataset();
    }
    
    std::string sop_class_uid;
    {
        OFString value;
        dataset->findAndGetOFStringArray(DCM_SOPClassUID, value);
        sop_class_uid = value.c_str();
    }
    
    dicomifier::StoreSCU scu;
    
    scu.set_own_ae_title(calling_aet);
    
    scu.set_peer_host_name(peer_host);
    scu.set_peer_port(peer_port);
    scu.set_peer_ae_title(peer_aet);
    
    scu.add_presentation_context(sop_class_uid.c_str(),
        { UID_LittleEndianImplicitTransferSyntax });
    scu.set_affected_sop_class(sop_class_uid);
    
    scu.associate();
    
    CounterCallback callback;
    auto wrapper = [&callback](void * data, T_DIMSE_StoreProgress * progress, 
            T_DIMSE_C_StoreRQ * request)
        {
            callback.call(data, progress, request);
        };
    
    scu.store(dataset, wrapper);
    
    scu.release();
    
    BOOST_CHECK_EQUAL(callback.begin_count, 1);
    BOOST_CHECK_EQUAL(callback.end_count, 1);
    BOOST_CHECK(callback.progressing_count > 0);
}

BOOST_FIXTURE_TEST_CASE(Missing_SOPClassUID, DcmQrSCP)
{
    dicomifier::StoreSCU scu;
    DcmDataset dataset;
    BOOST_REQUIRE_THROW(scu.set_affected_sop_class(&dataset),
                        dicomifier::DicomifierException)
}

BOOST_FIXTURE_TEST_CASE(Bad_SOPClassUID, DcmQrSCP)
{
    dicomifier::StoreSCU scu;
    DcmDataset dataset;
    dataset.putAndInsertOFStringArray(DCM_SOPClassUID, OFString("error"));
    BOOST_REQUIRE_THROW(scu.set_affected_sop_class(&dataset),
                        dicomifier::DicomifierException)
}
