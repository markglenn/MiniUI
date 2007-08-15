#ifndef _FLOAT_H_
#define _FLOAT_H_

#include <string>
#include "Integer.h"

namespace MiniUI
{
	namespace Types
	{
		class Float
		{
		public:
			Float(void);
			Float( float value );
			Float( std::string value );

			virtual ~Float(void);

			static float ParseFloat ( std::string value );
			static std::string ToString ( float value, int precision = 0 );

			// Retrieve the value
			long long	Int64Value ( )	{ return (long long)value; }
			int			IntValue ( )	{ return (int)value; }
			long		LongValue ( )	{ return (long)value; }
			short		ShortValue ( )	{ return (short)value; }
			float		FloatValue ( )	{ return value; }
			bool		BooleanValue ( ){ return (value != 0.0f); }

			std::string ToString ( int precision = 0 )
				{ return Float::ToString ( value, precision ); }

			// Retrieve a string representation of the number
			std::string ToHexString ( )		{ return Integer::ToString ( IntValue( ), 16 ); }
			std::string ToOctalString ( )	{ return Integer::ToString ( IntValue( ), 8 ); }
			std::string ToBinaryString ( )	{ return Integer::ToString ( IntValue( ), 2 ); }

			// Operators
			bool operator == ( const Float &right );
			bool operator != ( const Float &right );

		private:

			float value;

		};
	}
}

#endif // _FLOAT_H_
