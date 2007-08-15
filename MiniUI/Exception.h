#ifndef _MINIUI_EXCEPTION_H_
#define _MINIUI_EXCEPTION_H_

#include <string>
#include <sstream>

#include "IObject.h"

/* IMPORTANT NOTE:
	If you are seeing errors on compiling this file, run dos2unix on this file.
*/
namespace MiniUI
{

	/**
		A very basic exception class.

		Any exception thrown is thrown with this class.  This allows the application
		to not rely on the Windows API exception.  It also allows the application to throw
		a generic exception with just an error message.

\code
try
{
	throw Exception ("Error Message");
}
catch (Exception &e)
{
	cout << e.what() << endl;
}
\endcode
	*/
	class Exception : public IObject
	{
	public:

		/**	Constructor for the exception.
			Pass in the error message for the catch block to read.

			@param message The error message */
		Exception (std::string message) { m_strMessage = message; }

		/**	Returns the error message

			@return The error message */
		std::string what () { return m_strMessage; }

	protected:

		/**	The error message */
		std::string m_strMessage;
	};

// Defines an exception on the fly
#define DEFINE_EXCEPTION(NAME,MESSAGE)		\
	class NAME : public Exception			\
	{										\
	public:									\
		NAME ( ) : Exception(MESSAGE) {}	\
	};
	DEFINE_EXCEPTION(IndexOutOfRangeException, "Index is out of range");


// Generic exception throwing mechanism
#define Throw(MESSAGE)																	\
	std::stringstream _exceptionmessage;												\
	std::string file( __FILE__ );														\
	file = file.substr( file.find_last_of( "\\/" ) + 1 );								\
	_exceptionmessage << MESSAGE << " <" << file << "@" << __LINE__ << ">" << std::endl;\
	throw MiniUI::Exception( _exceptionmessage.str() );

}

#endif // _MINIUI_EXCEPTION_H_
