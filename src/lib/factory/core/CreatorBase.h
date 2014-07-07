/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _af7ae5f1_969d_404d_be7a_4cfe95455eac
#define _af7ae5f1_969d_404d_be7a_4cfe95455eac

#include <map>
#include <memory>

#include <boost/property_tree/ptree.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"

namespace dicomifier
{
    
namespace factory
{
    
class CreatorBase
{
public:
    typedef CreatorBase Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef std::map<std::string, boost::any> InOutPutType;
    
    virtual ~CreatorBase();
    
    void set_inputs(std::shared_ptr<InOutPutType> const inputs);
    void set_outputs(std::shared_ptr<InOutPutType> const outputs);
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value) = 0;

protected:
    CreatorBase();
    
    std::shared_ptr<InOutPutType> _inputs;
    std::shared_ptr<InOutPutType> _outputs;

private:
    CreatorBase(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory

} // namespace dicomifier

#endif // _af7ae5f1_969d_404d_be7a_4cfe95455eac
