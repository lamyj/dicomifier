/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Directory.h"

#include <set>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

#include "Dataset.h"
#include "core/DicomifierException.h"

namespace dicomifier
{

namespace bruker
{

std::set<Directory::Path> const 
Directory::_known_files = {
    "subject", "acqp", "method", "imnd", "isa", "d3proc", "reco", "visu_pars"};



std::vector<std::string>
Directory
::list_subjects(std::string const & path)
{
    std::vector<std::string> subjects;
    typedef boost::filesystem::recursive_directory_iterator RecursiveIterator;

    for (RecursiveIterator it(path); it != RecursiveIterator(); ++it)
    {
        if (it->path().filename() == "subject")
        {
            subjects.push_back(it->path().parent_path().string());
        }
    }
    return subjects;
}


void
Directory
::load(std::string const & path)
{
    typedef boost::filesystem::recursive_directory_iterator RecursiveIterator;
    typedef boost::filesystem::directory_iterator Iterator;

    std::vector<Path> reconstructions;
    for (RecursiveIterator it(path); it != RecursiveIterator(); ++it)
    {
        if (it->path().filename() == "id")
        {
            reconstructions.push_back(it->path().parent_path());
        }
    }

    for (auto const & reco : reconstructions)
    {
        Dataset dataset;
        Path current_path;
        for (current_path = reco; !boost::filesystem::equivalent(current_path, path); current_path.remove_leaf())
        {
            for (Iterator it(current_path); it!= Iterator(); ++it)
            {
                if (this->_known_files. find(it->path().filename()) != this->_known_files.end() &&
                        it->path().filename() != "visu_pars")
                {
                    dataset.load(it->path().string());
                }
            }
        }
        this->_add_reconstruction(reco, dataset);
    }
}

bool
Directory
::has_dataset(std::string const & reconstruction) const
{
    auto const dataset_it = this->_datasets.find(reconstruction);
    return (dataset_it != this->_datasets.end());
}

Dataset const &
Directory
::get_dataset(std::string const & reconstruction) const
{
    auto const dataset_it = this->_datasets.find(reconstruction);
    if(dataset_it == this->_datasets.end())
    {
        throw DicomifierException("No such series");
    }
    
    return dataset_it->second;
}

std::map<std::string, std::vector<std::string> >
Directory
::get_series_and_reco(const std::string &path)
{
    std::map<std::string, std::vector<std::string> > map;

    typedef boost::filesystem::directory_iterator Iterator;
    typedef boost::filesystem::recursive_directory_iterator RecursiveIterator;

    for(RecursiveIterator it(path); it != RecursiveIterator(); ++it)
    {
        if(it->path().filename() == "pdata")
        {
            for(Iterator reco_it(it->path()); reco_it != Iterator(); ++reco_it)
            {
                if(boost::filesystem::is_directory(reco_it->path()))
                {
                    std::string const reconstruction = ((Path)*reco_it).filename().string();
                    std::string const series = ((Path)*reco_it).parent_path().parent_path().filename().string();

                    if (map.find(series) == map.end())
                    {// create new entry
                        map[series] = {};
                    }
                    map[series].push_back(reconstruction);
                }
            }

            // Don't descend reconstructions have been processed.
            it.no_push();
        }
    }

    return map;
}

void
Directory
::_add_reconstruction(Path const & root, Dataset const & template_)
{
    // Known files below this reconstruction directory
    std::vector<Path> files;
    
    typedef boost::filesystem::recursive_directory_iterator Iterator;
    
    Path pixel_data;
    
    for(Iterator it(root); it != Iterator(); ++it)
    {
        if(this->_known_files.find(it->path().filename()) != this->_known_files.end())
        {
            files.push_back(it->path());
        }
        if(it->path().filename() == "2dseq")
        {
            pixel_data = it->path();
        }
    }
    
    // Create the dataset
    Dataset dataset(template_);
    for(auto const & file: files)
    {
        dataset.load(file.string());
    }
    if(!pixel_data.empty())
    {
        Field field;
        field.name = "PIXELDATA";
        field.value.push_back(pixel_data.string());
        dataset.set_field(field);
    }
    
    int const reconstruction = boost::lexical_cast<int>(
        root.filename().string());
    int const series = boost::lexical_cast<int>(
        root.parent_path().parent_path().filename().string());
    
    std::string const key = boost::lexical_cast<std::string>(
        10000*series+reconstruction);
    this->_datasets[key] = dataset;
}

} // namespace bruker

} // namespace dicomifier
