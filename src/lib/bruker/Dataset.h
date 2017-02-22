/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a0e278c7_39cf_4b9e_9a81_b843f16ea4e2
#define _a0e278c7_39cf_4b9e_9a81_b843f16ea4e2

#include <map>
#include <string>
#include <vector>

#include "Field.h"

namespace dicomifier
{
    
namespace bruker
{

struct FrameGroup
{
    struct Parameter
    {
        std::string name;
        int start_index;
    };
    
    long size; // Number of elements in this frame group
    std::string name;
    std::string comment;
    std::vector<Parameter> parameters;
};

class Dataset
{
public:
    /// @brief Load dataset from file, update any existing field.
    void load(std::string const & path);
    
    /// @brief Test if dataset contains a given field.
    bool has_field(std::string const & name) const;
    
    /// @brief Return the field, throw an exception if field is missing.
    Field const & get_field(std::string const & name) const;
    
    /// @brief Add a field to the dataset or modify an existing field.
    void set_field(Field const & field);
    
    /// @brief Return the frame groups, in outermost-to-innermost order.
    std::vector<FrameGroup> const & get_frame_groups() const;
    
    /// @brief Function used to return a set of files used to create the dataset (expect the PixelData file)
    std::vector<std::string> const & get_used_files() const;

    typedef std::map<std::string, Field>::const_iterator const_iterator;
    const_iterator begin() const { return this->_fields.begin(); }
    const_iterator end() const { return this->_fields.end(); }

private:
    std::map<std::string, Field> _fields;
    std::vector<FrameGroup> _frame_groups;

    std::vector<std::string> _used_files;
    void _update_frame_groups();
};

} // namespace bruker

} // namespace dicomifier

#endif // _a0e278c7_39cf_4b9e_9a81_b843f16ea4e2
