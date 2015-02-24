/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _828923a2_3026_4435_a30c_b56fdb657a52
#define _828923a2_3026_4435_a30c_b56fdb657a52

#include <string>

namespace dicomifier
{

namespace gui
{

/**
 * @brief The GenerationResultItem class
 */
class GenerationResultItem
{
public:
    enum Result
    {
        None,
        OK,
        Fail,
        Canceled
    };

    /// Create an instance of GenerationResultItem
    GenerationResultItem();

    /// Destroy the instance of GenerationResultItem
    ~GenerationResultItem();

    void set_subjectName(std::string const & name) { this->_subjectName = name; }
    void set_resultDirectory(std::string const & directory) { this->_resultDirectory = directory; }
    void set_dicomdirCreation(Result const & result) { this->_dicomdirCreation = result; }
    void set_zipCreation(Result const & result) { this->_zipCreation = result; }
    void set_DicomdirErrorMsg(std::string const & message) { this->_DicomdirErrorMsg = message; }
    void set_ZipErrorMsg(std::string const & message) { this->_ZipErrorMsg = message; }

    std::string get_subjectName() const { return this->_subjectName; }
    std::string get_resultDirectory() const { return this->_resultDirectory; }
    Result get_dicomdirCreation() const { return this->_dicomdirCreation; }
    Result get_zipCreation() const { return this->_zipCreation; }
    std::string get_DicomdirErrorMsg() const { return this->_DicomdirErrorMsg; }
    std::string get_ZipErrorMsg() const { return this->_ZipErrorMsg; }

    /// Convert Result to std::string
    std::string resultToString(Result const result) const;

    std::string get_dicomdirCreationToString() const;
    std::string get_zipCreationToString() const;

protected:

private:
    /// Subject Name
    std::string _subjectName;

    /// Output directory
    std::string _resultDirectory;

    /// DICOMDIR creation status
    Result _dicomdirCreation;

    /// ZIP creation status
    Result _zipCreation;

    /// DICOMDIR creation error message
    std::string _DicomdirErrorMsg;

    /// ZIP creation error message
    std::string _ZipErrorMsg;

};

} // namespace gui

} // namespace dicomifier

#endif // _828923a2_3026_4435_a30c_b56fdb657a52
