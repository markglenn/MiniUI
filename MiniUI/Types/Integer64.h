#ifndef _INTEGER64_H_
#define _INTEGER64_H_

#include <string>

#include "../Exception.h"
#include "Integer.h"

namespace MiniUI
{
	namespace Types
	{

		class Integer64
		{
		public:
			Integer64(void);
			Integer64( long long value );
			Integer64( std::string value, int radix = 10 );

			virtual ~Integer64(void);

			static long long	Parse		( std::string value, int radix = 10 );
			static long long	FullParse	( std::string value );
			static std::string	ToString	( long long value, int radix = 10 );

			// Retrieve the value
			long long	Int64Value ( )	{ return value; }
			int			IntValue ( )	{ return (int)value; }
			long		LongValue ( )	{ return (long)value; }
			short		ShortValue ( )	{ return (short)value; }
			float		FloatValue ( )	{ return (float)value; }
			bool		BooleanValue ( ){ return (value != 0); }

			// Retrieve a string representation of the number
			std::string ToHexString ( )		{ return Integer64::ToString ( value, 16 ); }
			std::string ToOctalString ( )	{ return Integer64::ToString ( value, 8 ); }
			std::string ToBinaryString ( )	{ return Integer64::ToString ( value, 2 ); }

			std::string ToString ( ) { return Integer64::ToString ( value, 10 ); }

			static long long MAX_VALUE;
			static long long MIN_VALUE;

			// Operators
			bool operator == ( const Integer64 &right );
			bool operator != ( const Integer64 &right );

		private:

			long long value;
		};

	}
}

#endif // _INTEGER64_H_
