/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c84c4c8e_6474_429c_8ffb_4c93c75df0f3
#define _c84c4c8e_6474_429c_8ffb_4c93c75df0f3

#include <string>

#include <v8.h>

namespace dicomifier
{

namespace javascript
{

/**
 * @brief The JavascriptVM class
 */
class JavascriptVM
{
public:
    /// Create an instance of JavascriptVM
    JavascriptVM();

    /// Destroy the instance of JavascriptVM
    ~JavascriptVM();

    /**
     * @brief Execute a JS Script
     * @param script: script JS to execute
     * @return script result
     */
    v8::Local<v8::Value> run(std::string const & script);

    /**
     * @brief Load and execute a JavaScript file
     * @param scriptpath: path to a JS file
     * @return script result
     */
    v8::Local<v8::Value> run_file(std::string const & scriptpath);

protected:

private:
    ///
    v8::Isolate* _isolate;

    ///
    v8::Persistent<v8::Context> context;

};

} // namespace javascript

} // namespace dicomifier

#endif // _c84c4c8e_6474_429c_8ffb_4c93c75df0f3
