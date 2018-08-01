Name: dicomifier
Summary: Convert data to and from DICOM (libraries)
Version: 1.2.1
Release: 1%{?dist}
License: CeCILL-B
Source0: https://github.com/lamyj/%{name}/archive/v%{version}.tar.gz
URL: https://github.com/lamyj/%{name}

BuildRequires: cmake
BuildRequires: gcc-c++
BuildRequires: make
BuildRequires: pkgconfig

BuildRequires: boost-devel
BuildRequires: pkgconfig(jsoncpp)
BuildRequires: pkgconfig(log4cpp)
BuildRequires: python2-dateutil
BuildRequires: python2-nibabel
BuildRequires: python2-numpy
BuildRequires: python2-odil

BuildRequires: python2-devel
#BuildRequires: python-nose
# boost-python is only compiled for Python 2: skip Python 3-related packages

BuildRequires: help2man

%description
Dicomifier is a set of tools to convert Bruker to DICOM and DICOM to NIfTI. A
set of mapping rules is provided, allowing the conservation of meta-data upon
conversion.

This package contains the shared libraries.

#----------------------------------------------------------------------------

%package devel

Summary: Convert data to and from DICOM (development files)
Requires: %{name} = %{version}-%{release}

%description devel
Dicomifier is a set of tools to convert Bruker to DICOM and DICOM to NIfTI. A
set of mapping rules is provided, allowing the conservation of meta-data upon
conversion.

This package contains the development files.

#----------------------------------------------------------------------------

%package -n python2-%{name}

Summary: Convert data to and from DICOM (Python 2 modules)
Requires: %{name} = %{version}-%{release}
Requires: python
Requires: python2-dateutil
Requires: python2-nibabel
Requires: python2-numpy
Requires: python2-odil

%description -n python2-%{name}
Dicomifier is a set of tools to convert Bruker to DICOM and DICOM to NIfTI. A
set of mapping rules is provided, allowing the conservation of meta-data upon
conversion.

This package contains the Python 2 modules.

#----------------------------------------------------------------------------

%package cli

Summary: Convert data to and from DICOM (command line tools)
Requires: python2-%{name} = %{version}-%{release}
BuildArch: noarch

%description cli
Dicomifier is a set of tools to convert Bruker to DICOM and DICOM to NIfTI. A
set of mapping rules is provided, allowing the conservation of meta-data upon
conversion.

This package contains the command-line application.

#----------------------------------------------------------------------------

%prep
%autosetup

%build
sed -i 's/DESTINATION lib/DESTINATION %{_lib}/g' src/lib/CMakeLists.txt
mkdir build
cd build
%cmake -DBUILD_GUI=OFF -DPYTHON_EXECUTABLE=/bin/python2.7 ..
%make_build

%install
cd build
%make_install
cd ..
mkdir -p %{buildroot}%{_mandir}/man1/
LD_LIBRARY_PATH=%{buildroot}%{_libdir} \
  PYTHONPATH=%{buildroot}%{_libdir}/python2.7/site-packages/ \
  help2man -o %{buildroot}%{_mandir}/man1/bruker2dicom.1 --version-string=%{version} %{buildroot}%{_bindir}/bruker2dicom
LD_LIBRARY_PATH=%{buildroot}%{_libdir} \
  PYTHONPATH=%{buildroot}%{_libdir}/python2.7/site-packages/ \
  help2man -o %{buildroot}%{_mandir}/man1/dicom2nifti.1 --version-string=%{version} %{buildroot}%{_bindir}/dicom2nifti

%files
%{_libdir}/lib%{name}.so.*

%files devel
%{_includedir}/%{name}/
%{_libdir}/lib%{name}.so

%files -n python2-%{name}
%{_libdir}/python%{python2_version}/site-packages/%{name}/

%files cli
%{_bindir}/*
%{_mandir}/man1/*

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%changelog
* Wed Aug 01 2018 Julien Lamy <lamy@unistra.fr> 1.2.1-1
- New upstream release
- Fix dependencies
* Thu Jul 26 2018 Julien Lamy <lamy@unistra.fr> 1.2.0-1
- Initial release
