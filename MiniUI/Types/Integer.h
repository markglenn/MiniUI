#ifndef _INTEGER_H_
#define _INTEGER_H_

#include <string>

#include "../Exception.h"

namespace MiniUI
{
	namespace Types
	{
		DEFINE_EXCEPTION ( NumberFormatException, "Invalid number format" );

		class Integer
		{
		public:
			Integer(void);
			Integer( int value );
			Integer( std::string value, int radix = 10 );

			virtual ~Integer(void);

			static int			ParseInt ( std::string value, int radix = 10 );
			static int			FullParseInt ( std::string value );
			static std::string	ToString ( int value, int radix = 10 );

			// Retrieve the value
			long long	Int64Value ( )	{ return (long long)value; }
			int			IntValue ( )	{ return value; }
			long		LongValue ( )	{ return (long)value; }
			short		ShortValue ( )	{ return (short)value; }
			float		FloatValue ( )	{ return (float)value; }
			bool		BooleanValue ( ){ return (value != 0); }

			// Retrieve a string representation of the number
			std::string ToHexString ( )		{ return Integer::ToString ( value, 16 ); }
			std::string ToOctalString ( )	{ return Integer::ToString ( value, 8 ); }
			std::string ToBinaryString ( )	{ return Integer::ToString ( value, 2 ); }

			std::string ToString ( ) { return Integer::ToString ( value, 10 ); }

			static int MAX_VALUE;
			static int MIN_VALUE;

			// Operators
			bool operator == ( const Integer &right );
			bool operator != ( const Integer &right );

		private:

			int value;
		};

	}
}

#endif // _INTEGER_H_
