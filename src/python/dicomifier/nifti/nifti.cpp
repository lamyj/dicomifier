/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <algorithm>
#include <sstream>
#include <string>
#include <string.h>

#include <boost/python.hpp>
#include <nifti/nifti1_io.h>
#include <numpy/arrayobject.h>

#include "core/DicomifierException.h"

/// @brief Convert numpy type to C++ type
template<typename CppType, NPY_TYPES NumpyType>
struct NumpyConverter
{
        NumpyConverter()
        {
            import_array();
            boost::python::converter::registry::push_back(
                &convertible, &construct, boost::python::type_id<CppType>());
        }
        
        static void* convertible(PyObject* object)
        {
            bool const is_convertible = (
                (object != nullptr) &&
                PyArray_CheckScalar(object) &&
                (PyArray_DescrFromScalar(object)->type_num == NumpyType)
            );
            
            return is_convertible?object:nullptr;
        }
        
        static void construct(
            PyObject* object,
            boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            typedef boost::python::converter::rvalue_from_python_storage<CppType> storage_type;
            void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

            PyArray_ScalarAsCtype(object, storage);

            data->convertible = storage;
        }
};

/// @brief Read a NIfTI image.
boost::python::object read(std::string const & filename)
{
    auto * image_c = nifti_image_read(filename.c_str(), true);
    
    using namespace boost::python;
    
    object numpy = import("numpy");
    object dicomifier = import("dicomifier");
    
    dict kwargs;
    
    kwargs["scl_slope"] = image_c->scl_slope;
    kwargs["scl_inter"] = image_c->scl_inter;
    kwargs["cal_min"] = image_c->cal_min;
    kwargs["cal_max"] = image_c->cal_max;
    kwargs["qform_code"] = image_c->qform_code;
    kwargs["sform_code"] = image_c->sform_code;
    kwargs["xyz_units"] = image_c->xyz_units;
    kwargs["time_units"] = image_c->time_units;
    kwargs["descrip"] = image_c->descrip;
    
    kwargs["pixdim"] = numpy.attr("ndarray")(make_tuple(8));
    for(int i=0; i<8; ++i)
    {
        kwargs["pixdim"][i] = image_c->pixdim[i];
    }
    
    kwargs["sform"] = numpy.attr("ndarray")(make_tuple(4,4));
    kwargs["qform"] = numpy.attr("ndarray")(make_tuple(4,4));
    for(int i=0; i<4; ++i)
    {
        for(int j=0; j<4; ++j)
        {
            kwargs["sform"][i][j] = image_c->sto_xyz.m[i][j];
            kwargs["qform"][i][j] = image_c->qto_xyz.m[i][j];
        }
    }
    
    list shape;
    for(int i=1; i<=image_c->dim[0]; ++i)
    {
        shape.insert(0, image_c->dim[i]);
    }
    
    std::stringstream dtype;
    if(image_c->byteorder == 1)
    {
        dtype << "<";
    }
    else
    {
        dtype << ">";
    }
    
    std::string const datatype = nifti_datatype_string(image_c->datatype);
    int width;
    if(datatype.size() > 3 && datatype.substr(0, 3) == "INT")
    {
        dtype << "i";
        width = std::stoi(datatype.substr(3));
    }
    else if(datatype.size() > 4 && datatype.substr(0, 4) == "UINT")
    {
        dtype << "u";
        width = std::stoi(datatype.substr(4));
    }
    else if(datatype.size() > 5 && datatype.substr(0, 5) == "FLOAT")
    {
        dtype << "f";
        width = std::stoi(datatype.substr(5));
    }
    else
    {
        throw dicomifier::DicomifierException("Unknown datatype: "+datatype);
    }
    dtype << width/8;
    
    kwargs["data"] = numpy.attr("ndarray")(shape, dtype.str());
    object dummy_array = kwargs["data"];
    std::copy(
        reinterpret_cast<char*>(image_c->data), 
        reinterpret_cast<char*>(image_c->data)+image_c->nbyper*image_c->nvox, 
        reinterpret_cast<PyArrayObject*>(dummy_array.ptr())->data);
    
    return dicomifier.attr(
        "dicom_to_nifti").attr("NIfTIImage")(*tuple(), **kwargs);
}

/// @brief Write a NIfTI image.
void write(boost::python::object const & image, std::string const & filename)
{
    auto * image_c = nifti_simple_init_nim();
    
    using namespace boost::python;
    
    image_c->ndim = extract<int>(image.attr("ndim"));
    image_c->nvox = extract<size_t>(image.attr("nvox"));
    image_c->nbyper = extract<int>(image.attr("nbyper"));
    image_c->datatype = extract<int>(image.attr("datatype"));
    image_c->scl_slope = extract<float>(image.attr("scl_slope"));
    image_c->scl_inter = extract<float>(image.attr("scl_inter"));
    image_c->cal_min = extract<float>(image.attr("cal_min"));
    image_c->cal_max = extract<float>(image.attr("cal_max"));
    image_c->qform_code = extract<int>(image.attr("qform_code"));
    image_c->sform_code = extract<int>(image.attr("sform_code"));
    image_c->xyz_units = extract<int>(image.attr("xyz_units"));
    image_c->time_units = extract<int>(image.attr("time_units"));
    
    std::string const descrip = extract<std::string>(image.attr("descrip"));
    auto const * descrip_pointer = descrip.c_str();
    std::copy(
        descrip_pointer, descrip_pointer+std::min<int>(descrip.size(), 80),
        image_c->descrip);
        
    // dim and nx, ..., nw
    std::fill(image_c->dim, image_c->dim+8, 1);
    image_c->dim[0] = extract<int>(image.attr("ndim"));
    for(int i=0; i<image_c->dim[0]; ++i)
    {
        image_c->dim[i+1] = extract<int>(
                image.attr("shape")[image_c->dim[0]-1-i]);
    }
    image_c->nx = image_c->dim[1]; image_c->ny = image_c->dim[2]; 
    image_c->nz = image_c->dim[3]; image_c->nt = image_c->dim[4];
    image_c->nu = image_c->dim[5]; image_c->nv = image_c->dim[6];
    image_c->nw = image_c->dim[7];
    
    // pixdim and dx, ..., dw
    std::fill(image_c->pixdim, image_c->pixdim+8, 0);
    image_c->pixdim[1] = image_c->dx = extract<float>(image.attr("pixdim")[1]);
    image_c->pixdim[2] = image_c->dy = extract<float>(image.attr("pixdim")[2]);
    image_c->pixdim[3] = image_c->dz = extract<float>(image.attr("pixdim")[3]);
    image_c->pixdim[4] = image_c->dt = extract<float>(image.attr("pixdim")[4]);
    image_c->pixdim[5] = image_c->du = extract<float>(image.attr("pixdim")[5]);
    image_c->pixdim[6] = image_c->dv = extract<float>(image.attr("pixdim")[6]);
    image_c->pixdim[7] = image_c->dw = extract<float>(image.attr("pixdim")[7]);
    
    // qform and sform
    object numpy = import("numpy");
    object qform = image.attr("qform");
    object const q_inverse = numpy.attr("linalg").attr("inv")(qform);
    
    object sform = image.attr("sform");
    object const s_inverse = numpy.attr("linalg").attr("inv")(sform);
    
    for(int i=0; i<4; ++i)
    {
        for(int j=0; j<4; ++j)
        {
            // CAUTION: the operator[] of boost::python::object only takes one
            // argument. Writing qform[i,j] calls the C++ operator, 
            // i.e. qform[j]
            image_c->qto_xyz.m[i][j] = extract<float>(qform[i][j]);
            image_c->qto_ijk.m[i][j] = extract<float>(q_inverse[i][j]);
            
            image_c->sto_xyz.m[i][j] = extract<float>(sform[i][j]);
            image_c->sto_ijk.m[i][j] = extract<float>(s_inverse[i][j]);
        }
    }
    
    nifti_mat44_to_quatern(
        image_c->qto_xyz, 
        &image_c->quatern_b, &image_c->quatern_c, &image_c->quatern_d,
        &image_c->qoffset_x, &image_c->qoffset_y, &image_c->qoffset_z, 
        &image_c->dx, &image_c->dy, &image_c->dz,
        &image_c->qfac);
    
    image_c->fname = strdup(filename.c_str());
    
    // CAUTION: nifti_image_free will free this. Do no forget to put it
    // back to NULL
    object data = image.attr("data");
    image_c->data = reinterpret_cast<PyArrayObject*>(data.ptr())->data;
    
    nifti_image_write(image_c);
    
    image_c->data = NULL;
    nifti_image_free(image_c);
}

BOOST_PYTHON_MODULE(nifti)
{
    using namespace boost::python;

    def(
        "read", static_cast<object(*)(std::string const &)>(&read), 
        arg("filename"), "Read a NIfTI image.");
    def(
        "write", 
        static_cast<void(*)(object const &,std::string const &)>(&write),
        (arg("image"), arg("filename")), "Write a NIfTI image.");
    
#define declare_constant(name) scope().attr(#name) = name;
    
    declare_constant(DT_NONE);
    declare_constant(DT_UNKNOWN);
    declare_constant(DT_BINARY);
    declare_constant(DT_UNSIGNED_CHAR);
    declare_constant(DT_SIGNED_SHORT);
    declare_constant(DT_SIGNED_INT);
    declare_constant(DT_FLOAT);
    declare_constant(DT_COMPLEX);
    declare_constant(DT_DOUBLE);
    declare_constant(DT_RGB);
    declare_constant(DT_ALL);
    declare_constant(DT_UINT8);
    declare_constant(DT_INT16);
    declare_constant(DT_INT32);
    declare_constant(DT_FLOAT32);
    declare_constant(DT_COMPLEX64);
    declare_constant(DT_FLOAT64);
    declare_constant(DT_RGB24);
    declare_constant(DT_INT8);
    declare_constant(DT_UINT16);
    declare_constant(DT_UINT32);
    declare_constant(DT_INT64);
    declare_constant(DT_UINT64);
    declare_constant(DT_FLOAT128);
    declare_constant(DT_COMPLEX128);
    declare_constant(DT_COMPLEX256);
    declare_constant(DT_RGBA32);
    
    declare_constant(NIFTI_XFORM_UNKNOWN);
    declare_constant(NIFTI_XFORM_SCANNER_ANAT);
    declare_constant(NIFTI_XFORM_ALIGNED_ANAT);
    declare_constant(NIFTI_XFORM_TALAIRACH);
    declare_constant(NIFTI_XFORM_MNI_152);

    declare_constant(NIFTI_UNITS_UNKNOWN);
    declare_constant(NIFTI_UNITS_METER);
    declare_constant(NIFTI_UNITS_MM);
    declare_constant(NIFTI_UNITS_MICRON);
    declare_constant(NIFTI_UNITS_SEC);
    declare_constant(NIFTI_UNITS_MSEC);
    declare_constant(NIFTI_UNITS_USEC);
    declare_constant(NIFTI_UNITS_HZ);
    declare_constant(NIFTI_UNITS_PPM);
    declare_constant(NIFTI_UNITS_RADS);
    
#undef declare_constant

    NumpyConverter<float, NPY_FLOAT32>();
    NumpyConverter<double, NPY_FLOAT64>();
    NumpyConverter<std::size_t, NPY_INT64>();
    
}
