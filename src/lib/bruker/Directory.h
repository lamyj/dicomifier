/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _de7bece8_638f_4abc_bb07_1d9f9863f468
#define _de7bece8_638f_4abc_bb07_1d9f9863f468

#include <map>
#include <set>
#include <string>

#include <boost/filesystem.hpp>

#include "Dataset.h"

namespace dicomifier
{

namespace bruker
{

class Directory
{
public:
    void load(std::string const & path);
    
    /// @brief Test if directory contains a given series.
    bool has_dataset(std::string const & series_number) const;
    
    /**
     * @brief Return the dataset associated to the series, throw an exception 
     * if field is missing.
     */
    Dataset const & get_dataset(std::string const & series_number) const;
    
private:
    typedef boost::filesystem::path Path;
    
    /// @brief Known files in the Bruker hierarchy 
    static std::set<Path> const _known_files;
    std::map<std::string, Dataset> _datasets;
    
    void _add_reconstruction(Path const & root, Dataset const & template_);
};

} // namespace bruker

} // namespace dicomifier

#endif // _de7bece8_638f_4abc_bb07_1d9f9863f468
