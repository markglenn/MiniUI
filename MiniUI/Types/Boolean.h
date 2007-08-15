#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_

#include <string>
#include "Integer.h"

namespace MiniUI
{
	namespace Types
	{
		DEFINE_EXCEPTION ( BooleanFormatException, "Invalid boolean format" );

		class Boolean
		{
		public:
			Boolean(void);
			Boolean( bool value );
			Boolean( std::string value );

			virtual ~Boolean(void);

			static bool ParseBoolean ( std::string value );
			static std::string ToString ( bool value );

			// Retrieve the value
			bool		BooleanValue ( ) { return value; }

			std::string ToString ( );

			// Operators
			bool operator == ( const Boolean &right );
			bool operator != ( const Boolean &right );

		private:

			bool value;

		};
	}
}

#endif // _BOOLEAN_H_
