/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>

#include "core/Logger.h"
#include "LoggerJS.h"

namespace dicomifier
{

namespace javascript
{

v8::Handle<v8::Value> log(v8::Arguments const & args)
{
    if(args.Length() < 1)
    {
        return v8::Null();
    }

    std::stringstream streamlevel;
    if(args.Length() == 2)
    {
        auto const levelv8 = args[1];
        v8::String::Utf8Value level(levelv8);
        streamlevel << *level;
    }
    else
    {
        streamlevel << "INFO";
    }

    v8::HandleScope scope;
    auto const arg = args[0];
    v8::String::Utf8Value value(arg);
    getLogger(streamlevel.str()) << *value;

    return v8::Null();
}

} // namespace javascript

} // namespace dicomifier
