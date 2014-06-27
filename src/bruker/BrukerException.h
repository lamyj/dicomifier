#ifndef _7cf59eab_abed_423e_b69d_0ae0ee4d4339
#define _7cf59eab_abed_423e_b69d_0ae0ee4d4339
/*! \file BrukerException.h
*/

#include <exception>
#include <string>

namespace router
{

/**
 * \class BrukerException
 * \brief Generic exception
 */
class BrukerException: public std::exception
{
public:
    BrukerException(const std::string& message):
        m_message(message) {}

    ~BrukerException() throw() {}
    
    virtual const char* what() const throw() {
        return m_message.c_str();
    }
    
protected:
   std::string m_message;

private:

};

/**
 * \class BrukerSizeException
 * \brief 
 */
class BrukerSizeException: public BrukerException
{
public:
    BrukerSizeException( const std::string& message,
		      int lgt,
		      int expected_lgt
		      )
      : BrukerException(message), m_lgt(lgt), m_expected_lgt(expected_lgt)
    {}

    ~BrukerSizeException() throw() {}
    
    int getFoundLgt() const throw() {
        return m_lgt;
    }

    int getExpectedLgt() const throw() {
        return m_expected_lgt;
    }
     
private:
   int m_lgt;
   int m_expected_lgt;

};

/**
 * \class BrukerInitException
 * \brief 
 */
class BrukerInitException: public BrukerException
{
public:
    BrukerInitException( const std::string& message
		      )
      : BrukerException(message)
    {}

    ~BrukerInitException() throw() {}
    
private:

};

/**
 * \class BrukerHopelessException
 * \brief 
 */
class BrukerHopelessException: public BrukerException
{
public:
    BrukerHopelessException( const std::string& message
		      )
      : BrukerException(message)
    {}

    ~BrukerHopelessException() throw() {}
    
private:

};

} // namespace router

#endif // _7cf59eab_abed_423e_b69d_0ae0ee4d4339
