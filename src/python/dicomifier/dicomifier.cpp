/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <numeric>
#include <odil/DataSet.h>
#include <odil/registry.h>
#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL DICOMIFIER_ARRAY_API
#include <numpy/arrayobject.h>
#include "core/Exception.h"

#include <pybind11/numpy.h>

void wrap_bruker(pybind11::module &);

void convert_pixel_data(
    pybind11::dict & bruker_data_set, odil::DataSet & dicom_data_set)
{
    PyObject * pixel_data_object = PyDict_GetItemString(
        bruker_data_set.ptr(), "PIXELDATA");
    if(pixel_data_object == NULL)
    {
        throw std::runtime_error("Missing PIXELDATA");
    }
    if(!PyArray_Check(pixel_data_object))
    {
        throw std::runtime_error("Not an array");
    }
    auto pixel_data = reinterpret_cast<PyArrayObject*>(pixel_data_object);
    if(!PyArray_CHKFLAGS(pixel_data, NPY_ARRAY_CARRAY))
    {
        throw std::runtime_error("Not a C array");
    }
    if(!PyArray_CHKFLAGS(pixel_data, NPY_ARRAY_OWNDATA))
    {
        throw std::runtime_error("Array does not own its memory");
    }
    
    // NOTE: if pixel_data > 4 GiB, the VL field is too small to hold the size
    // of the element. Use Encapsulated Uncompressed Explicit VR Little Endian
    // instead
    // https://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_A.4.11.html
    std::size_t const nbytes = PyArray_NBYTES(pixel_data);
    std::size_t fragments = 1;
    if(nbytes > (1UL<<32))
    {
        if(!dicom_data_set.has(odil::registry::NumberOfFrames))
        {
            throw std::runtime_error("PixelData is too large");
        }
        fragments = dicom_data_set.as_int(odil::registry::NumberOfFrames)[0];
        dicom_data_set.set_transfer_syntax(
            odil::registry::EncapsulatedUncompressedExplicitVRLittleEndian);
    }
    
    if(nbytes % fragments != 0)
    {
        throw std::runtime_error("Varying frame size");
    }
    
    auto const fragment_bytes = nbytes / fragments;
    
    odil::Value::Binary value(fragments);
    auto source = PyArray_BYTES(pixel_data);
    for(std::size_t i=0; i!=fragments; ++i)
    {
        value[i].resize(fragment_bytes);
        std::memcpy(value[i].data(), source, value[i].size());
        source += fragment_bytes;
    }
    
    PyDict_DelItemString(bruker_data_set.ptr(), "PIXELDATA");
    
    dicom_data_set.add(
        odil::registry::PixelData, std::move(value), odil::VR::OB);
}

pybind11::handle convert_pixel_data(
    odil::DataSet & data_set, pybind11::object dtype_)
{
    if(!PyArray_DescrCheck(dtype_.ptr()))
    {
        throw std::runtime_error("Not a dtype");
    }
    auto dtype = reinterpret_cast<PyArray_Descr*>(dtype_.ptr());
    
    auto const & pixel_data = data_set.as_binary(odil::registry::PixelData);
    
    // Get number of bytes
    npy_intp size = std::accumulate(
        pixel_data.cbegin(), pixel_data.cend(), 0L,
        [](npy_intp const & a, odil::Value::Binary::value_type const & b)
        {
            return a + b.size();
        });
    
    // Get number of elements
    if(size % dtype->elsize != 0)
    {
        throw std::runtime_error("Incompatible dtype");
    }
    size /= dtype->elsize;
    
    auto array = PyArray_SimpleNewFromDescr(1, &size, dtype);
    
    auto it = PyArray_BYTES((PyArrayObject*)array);
    for(auto && item: pixel_data)
    {
        std::memcpy(it, item.data(), item.size());
        it += item.size();
    }
    
    data_set.remove(odil::registry::PixelData);
    
    return array;
}

PYBIND11_MODULE(_dicomifier, _dicomifier)
{
    if (_import_array() < 0)
    {
        PyErr_Print();
        PyErr_SetString(
            PyExc_ImportError, "numpy.core.multiarray failed to import");
    }
    
    pybind11::register_exception<dicomifier::Exception>(
        _dicomifier, "Exception");
    
    wrap_bruker(_dicomifier);
    
    _dicomifier.def(
        "convert_pixel_data",
        pybind11::detail::overload_cast_impl<pybind11::dict &, odil::DataSet &>()(
            &convert_pixel_data));
    _dicomifier.def(
        "convert_pixel_data",
        pybind11::detail::overload_cast_impl<odil::DataSet &, pybind11::object>()(
            &convert_pixel_data));
}
