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

    std::set<Path> reconstructions;
    for(RecursiveIterator it(boost::filesystem::canonical(path));
        it != RecursiveIterator(); ++it)
    {
        if(it->path().filename() == "id" || it->path().filename() == "reco")
        {
            reconstructions.insert(it->path().parent_path());
        }
    }

    for(auto const & reco: reconstructions)
    {
        Dataset dataset;
        Path current_path = reco;
        // upper path will be used to store the path above "path" arg
        Path upper_path = boost::filesystem::canonical(path);
        // We can begin here because the files under "reco" path will anyway be
        // parsed with the line "_add_reconstruction..."
        current_path.remove_leaf();
        // We use upper_path in order to parse the "path" directory too in the
        // following while loop
        upper_path.remove_leaf();
        while(!boost::filesystem::equivalent(current_path, upper_path))
        {
            for(Iterator it(current_path); it!= Iterator(); ++it)
            {
                if(this->_known_files.find(it->path().filename()) != this->_known_files.end()
                    && it->path().filename() != "visu_pars")
                {
                    dataset.load(it->path().string());
                }
            }
            current_path.remove_leaf();
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
        throw DicomifierException("No such reconstruction: "+reconstruction);
    }
    
    return dataset_it->second;
}

std::vector<std::string> const &
Directory
::get_used_files(std::string const& reconstruction) const
{
    auto const dataset_it = this->_datasets.find(reconstruction);
    if(dataset_it == this->_datasets.end())
    {
        throw DicomifierException("No such reconstruction: "+reconstruction);
    }

    return dataset_it->second.get_used_files();
}

std::map<std::string, std::vector<std::string> >
Directory
::get_series_and_reco(const std::string &path)
{
    std::map<std::string, std::vector<std::string> > series_and_reco;

    typedef boost::filesystem::directory_iterator Iterator;
    typedef boost::filesystem::recursive_directory_iterator RecursiveIterator;
    
    for(RecursiveIterator it(path); it != RecursiveIterator(); ++it)
    {
        if(it->path().filename() == "id" || it->path().filename() == "reco")
        {
            for(Iterator reco_it(it->path().parent_path().parent_path()); 
                reco_it != Iterator(); ++reco_it)
            {
                if(boost::filesystem::is_directory(reco_it->path()))
                {
                    std::string const reconstruction = ((Path)*reco_it).filename().string();
                    std::string const series = ((Path)*reco_it).parent_path().parent_path().filename().string();

                    auto & reconstructions = series_and_reco[series];
                    if(std::find(
                        reconstructions.begin(), reconstructions.end(), 
                        reconstruction) == reconstructions.end())
                    {
                        reconstructions.push_back(reconstruction);
                    }
                }
            }
        }
    }

    return series_and_reco;
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
