/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
CreatorBase::CreatorBase()
{
	this->_inputs = std::make_shared<InOutPutType>();
	this->_outputs = std::make_shared<InOutPutType>();
}

CreatorBase::~CreatorBase()
{
}

void CreatorBase::set_inputs(std::shared_ptr<InOutPutType> const inputs)
{
	this->_inputs = inputs;
}

void CreatorBase::set_outputs(std::shared_ptr<InOutPutType> const outputs)
{
	this->_outputs = outputs;
}
    
} // namespace factory
    
} // namespace dicomifier
