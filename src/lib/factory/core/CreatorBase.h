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

#include <boost/any.hpp>
#include <boost/property_tree/ptree.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"

namespace dicomifier
{
    
namespace factory
{
    
/**
 * @brief The CreatorBase class: Abstract base class for factory
 */
class CreatorBase
{
public:
    typedef CreatorBase Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    typedef std::map<std::string, boost::any> InOutPutType;
    
    /// Destroy the instance of CreatorBase
    virtual ~CreatorBase();
    
    /**
     * @brief set_inputs: setter for attribut inputs
     * @param inputs: new value
     */
    void set_inputs(std::shared_ptr<InOutPutType> const & inputs);

    /**
     * @brief set_outputs: setter for attribut outputs
     * @param outputs: new value
     */
    void set_outputs(std::shared_ptr<InOutPutType> const & outputs);
    
    /**
     * @brief Create: Override by inherit classes
     * @param value: XML node
     * @return Object pointer
     */
    virtual Object::Pointer Create(
            boost::property_tree::ptree::value_type & value) = 0;

protected:
    /// Create an instance of CreatorBase
    CreatorBase();
    
    /// List of the inputs
    std::shared_ptr<InOutPutType> _inputs;

    /// List of the outputs
    std::shared_ptr<InOutPutType> _outputs;
    
    template<typename T>
    T _get(boost::property_tree::ptree const & tree,
           std::string const & path) const;

private:
    CreatorBase(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory

} // namespace dicomifier

#include "factory/core/CreatorBase.txx"

#endif // _af7ae5f1_969d_404d_be7a_4cfe95455eac
