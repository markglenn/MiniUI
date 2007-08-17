/***************************************************************************
 *   Copyright (C) 2007 by Mark Glenn                                      *
 *   markglenn@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _FLOAT_H_
#define _FLOAT_H_

#include <string>
#include "Integer.h"

namespace MiniUI
{
	namespace Types
	{
		/** Floating point storage container and parser */
		class Float
		{
		public:
			/// Constructor
			Float(void);

			/** Constructor
				
				@param value Set value
			*/
			Float( float value );

			/** Constructor

				@param value String value to parse
			*/
			Float( std::string value );

			/// Destructor
			virtual ~Float(void);

			/** Parses a string into a float

				@param value String value to parse
				@return A float containing the result
			*/
			static float ParseFloat ( std::string value );

			/** Converts a boolean value to a string representation

				@param value Boolean to convert
				@param precision Precision of the float
				@return String representation of the value
			*/
			static std::string ToString ( float value, int precision = 0 );

			/** Convert to 64 bit integer

				@return 64 bit value
			*/
			long long	Int64Value ( )	{ return (long long)value; }

			/** Convert to integer

				@return Integer value
			*/
			int			IntValue ( )	{ return (int)value; }

			/** Convert to long integer

				@return Long value
			*/
			long		LongValue ( )	{ return (long)value; }

			/** Convert to short integer

				@return Short value
			*/
			short		ShortValue ( )	{ return (short)value; }

			/** Returns float value

				@return Float value
			*/
			float		FloatValue ( )	{ return value; }

			/** Convert to boolean value

				@return boolean value
			*/
			bool		BooleanValue ( ){ return (value != 0.0f); }
			
			/** Converts a floating point value to a string representation

				@param precision Precision of the float
				@return String representation of the value
			*/
			std::string ToString ( int precision = 0 )
				{ return Float::ToString ( value, precision ); }

			// Retrieve a string representation of the number

			/** Converts the value to a hexidecimal string

				@return Hexidecimal string
			*/
			std::string ToHexString ( )		{ return Integer::ToString ( IntValue( ), 16 ); }

			/** Converts the value to a octal string

				@return Octal string
			*/
			std::string ToOctalString ( )	{ return Integer::ToString ( IntValue( ), 8 ); }

			/** Converts the value to a binary string

				@return Binary string
			*/
			std::string ToBinaryString ( )	{ return Integer::ToString ( IntValue( ), 2 ); }

			// Operators

			/** Tests if two values match

				@param right Value to compare
				@return True if the values match
			*/
			bool operator == ( const Float &right );

			/** Tests if two values don't match

				@param right Value to compare
				@return False if the values match
			*/
			bool operator != ( const Float &right );

		private:

			float value;

		};
	}
}

#endif // _FLOAT_H_
