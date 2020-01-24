/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDirectory
#include <boost/test/unit_test.hpp>

#include <set>
#include <string>

#include <boost/filesystem.hpp>

#include "bruker/Directory.h"
#include "core/DicomifierException.h"

struct Fixture
{
    std::string path;

    Fixture()
    {
        std::string const root(getenv("DICOMIFIER_TEST_DATA")?getenv("DICOMIFIER_TEST_DATA"):"");
        if(root.empty())
        {
            throw std::runtime_error("DICOMIFIER_TEST_DATA is undefined");
        }
        
        this->path = root+"/bruker";
    }
};

BOOST_FIXTURE_TEST_CASE(ListSubjects, Fixture)
{
    auto && actual = dicomifier::bruker::Directory::list_subjects(path);
    decltype(actual) const expected{path};
    BOOST_REQUIRE(actual == expected);
}

BOOST_FIXTURE_TEST_CASE(GetSeriesAndReco, Fixture)
{
    auto && actual = dicomifier::bruker::Directory::get_series_and_reco(path);
    decltype(actual) const expected{{"1", {"1"}}};
    BOOST_REQUIRE(actual == expected);
}

BOOST_FIXTURE_TEST_CASE(Load, Fixture)
{
    dicomifier::bruker::Directory directory;
    directory.load(path);
    BOOST_CHECK_EQUAL(directory.has_dataset("10001"), true);
}

BOOST_FIXTURE_TEST_CASE(GetDataset, Fixture)
{
    dicomifier::bruker::Directory directory;
    directory.load(path);

    auto && dataset = directory.get_dataset("10001");
    BOOST_CHECK_EQUAL(dataset.has_field("VISU_param"), true);
}

BOOST_FIXTURE_TEST_CASE(GetBadDataset, Fixture)
{
    dicomifier::bruker::Directory directory;
    directory.load(path);
    BOOST_REQUIRE_THROW(
        directory.get_dataset("90009"), dicomifier::DicomifierException);
}

BOOST_FIXTURE_TEST_CASE(GetUsedFiles, Fixture)
{
    dicomifier::bruker::Directory directory;
    directory.load(path);

    auto && actual = directory.get_used_files("10001");
    decltype(actual) expected{
        boost::filesystem::canonical(path+"/subject").native(),
        boost::filesystem::canonical(path+"/1/acqp").native(),
        boost::filesystem::canonical(path+"/1/pdata/1/visu_pars").native(),
    };
    BOOST_REQUIRE(
        std::set<std::string>(actual.begin(), actual.end())
        == std::set<std::string>(expected.begin(), expected.end()));
}
