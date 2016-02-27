/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _82c34c7d_4926_48bd_92fd_120aaa6c3791
#define _82c34c7d_4926_48bd_92fd_120aaa6c3791

#include <clocale>
#include <string>

#include <json/json.h>

#include "javascript/JavascriptVM.h"

class TestDataJS
{
public:
    TestDataJS() {}

    virtual ~TestDataJS() {}

    Json::Value const get_json_result(std::string const & script)
    {
        auto const result = jsvm.run(script, jsvm.get_context());

        std::string json = *v8::String::Utf8Value(result);

        // Parse it into a data set.
        Json::Value jsondataset;

        Json::Reader reader;
        std::string old_locale = std::setlocale(LC_ALL, "C");
        reader.parse(json, jsondataset);
        std::setlocale(LC_ALL, old_locale.c_str());

        return jsondataset;
    }

    dicomifier::javascript::JavascriptVM jsvm;

};

#endif // _82c34c7d_4926_48bd_92fd_120aaa6c3791
