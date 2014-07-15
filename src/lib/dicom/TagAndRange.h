/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6540dd05_736b_4791_9874_a350a5ba72ff
#define _6540dd05_736b_4791_9874_a350a5ba72ff

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

namespace dicomifier
{
    
struct Range
{
    int _min;
    int _max;
    
    Range(): _min(0), _max(0) {}
    Range(int min, int max): _min(min), _max(max) {}
};

struct TagAndRange
{
    DcmTag _tag;
    Range _range;
    
    TagAndRange() {}
    TagAndRange(DcmTag tag, Range range): _tag(tag), _range(range) {}
};

} // namespace dicomifier

#endif // _6540dd05_736b_4791_9874_a350a5ba72ff
