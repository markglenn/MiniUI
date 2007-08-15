#include <cctype>
#include <algorithm>
#include <locale>

#include "Integer.h"

namespace MiniUI
{
	namespace Types
	{
		static const char conversion[] = "0123456789ABCDEF";

		// No matter what number of bits the O/S is, this will calculate max/min
		int Integer::MAX_VALUE = ((unsigned int)(-1) >> 1);
		int Integer::MIN_VALUE = -Integer::MAX_VALUE - 1;

		static int upper(int c)
		{
			return std::toupper((unsigned char)c);
		}

		///////////////////////////////////////////////////////////////////////
		Integer::Integer(void) : value ( 0 )
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		Integer::Integer( int value )
		///////////////////////////////////////////////////////////////////////
		{
			this->value = value;
		}

		///////////////////////////////////////////////////////////////////////
		Integer::Integer( std::string value, int radix )
		///////////////////////////////////////////////////////////////////////
		{
			this->value = Integer::ParseInt ( value, radix );
		}

		///////////////////////////////////////////////////////////////////////
		Integer::~Integer(void)
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		int Integer::ParseInt ( std::string value, int radix )
		///////////////////////////////////////////////////////////////////////
		{
			int intvalue = 0;
			bool negative = false;

			// Empty string == 0
			if ( value.length() == 0 )
				return 0;

			// Negative value
			if ( value[0] == '-' )
			{
				value = value.substr ( 1 );
				negative = true;
			}

			// Make the data upper case
			std::transform (value.begin(), value.end(),
							value.begin(),
							upper);

			for (unsigned int i = 0; i < value.length(); i++)
			{
				// Move the digits one place to the left
				intvalue = intvalue * radix;
				char* digit = strchr (conversion, value[i]);

				if ( digit == NULL || ( digit - conversion ) >= radix )
					throw NumberFormatException ( );

				intvalue += (int)(digit - conversion);
			}

			return ( negative ? -intvalue : intvalue );
		}

		///////////////////////////////////////////////////////////////////////
		std::string	Integer::ToString ( int value, int radix )
		///////////////////////////////////////////////////////////////////////
		{
			std::string strValue = "";
			int digit;
			bool negative = false;

			unsigned int uiValue;

			// Only base 10 numbers allow negative sign
			if ( value < 0 && radix == 10 )
			{
				negative = true;
				value *= -1;
			}

			// Convert to unsigned int (to allow for hex/oct/bin negative #'s)
			uiValue = (unsigned int)value;

			while (uiValue != 0)
			{
				// Pull out the digit
				digit = uiValue % radix;
				uiValue /= radix;

				strValue = "0" + strValue;
				strValue[0] = conversion[digit];
			}

			// If we are blank, make sure we return "0"
			if (strValue.length() == 0)
				strValue = "0";

			if ( negative )
				strValue = "-" + strValue;

			return strValue;
		}


		///////////////////////////////////////////////////////////////////////
		// Parses a number in an unknown format.  Slower but thorough.
		//  Examples:
		//		Hex:		0x2A,		2Ah,	0x2Ah
		//		Octal:		032,		32o,	032o
		//		Binary:		1110101b
		//		Decimal:	12,			12d
		///////////////////////////////////////////////////////////////////////
		int	Integer::FullParseInt ( std::string value )
		///////////////////////////////////////////////////////////////////////
		{
			if ( value.length() == 0 )
				return 0;

			int radix = 10;

			// Make the data upper case
			std::transform (value.begin(), value.end(),
							value.begin(),
							upper);


			// If it starts with 0x, it's probably a hex number
			if ( value.find ("0X") != std::string::npos )
			{
				radix = 16;
				value = value.substr ( 2 );
			}
			// If it starts with just a 0, it's probably octal
			else if ( value[0] == '0' )
			{
				radix = 8;
				value = value.substr ( 1 );
			}

			switch ( value[ value.length() - 1 ] )
			{
				case 'B':
					// Hex values could also end in 'B'
					if ( radix != 16 )
					{
						radix = 2;
						value = value.substr(0, value.length() - 1);
					}
					break;

				case 'H':
					radix = 16;
					value = value.substr(0, value.length() - 1);
					break;

				case 'O':
					radix = 8;
					value = value.substr(0, value.length() - 1);
					break;

				case 'D':
					if ( radix != 16 )
					{
						radix = 10;
						value = value.substr(0, value.length() - 1);
					}
					break;
			}

			// Radix determined, now parse it
			return Integer::ParseInt ( value, radix );
		}

		///////////////////////////////////////////////////////////////////////
		bool Integer::operator == ( const Integer &right )
		///////////////////////////////////////////////////////////////////////
		{
			return ( this->value == right.value );
		}

		///////////////////////////////////////////////////////////////////////
		bool Integer::operator != ( const Integer &right )
		///////////////////////////////////////////////////////////////////////
		{
			return ( this->value != right.value );
		}

	}
}
