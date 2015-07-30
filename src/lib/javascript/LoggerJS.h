/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _96bd3665_da79_4623_b057_eddc465ed4be
#define _96bd3665_da79_4623_b057_eddc465ed4be

#include <v8.h>

namespace dicomifier
{

namespace javascript
{

/**
 * @brief Send String to the logger
 * @param args: 2 arguments:
 *              - data to log
 *              - level as String (DEBUG, INFO (default), WARNING, ERROR)
 * @return null
 */
v8::Handle<v8::Value> log(v8::Arguments const & args);

} // namespace javascript

} // namespace dicomifier

#endif // _96bd3665_da79_4623_b057_eddc465ed4be
