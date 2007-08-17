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

#ifndef _INTEGER64_H_
#define _INTEGER64_H_

#include <string>

#include "../Exception.h"
#include "Integer.h"

namespace MiniUI
{
	namespace Types
	{
		/** Integer 64 storage container and parser */
		class Integer64
		{
		public:
			/// Constructor
			Integer64(void);

			/** Constructor
				
				@param value Set value
			*/
			Integer64( long long value );

			/** Constructor

				@param value String value to parse
				@param radix Base of the integer
			*/
			Integer64( std::string value, int radix = 10 );

			/// Destructor
			virtual ~Integer64(void);

			/** Parses a string into a 64 bit integer

				@param value String value to parse
				@param radix Base of the integer
				@return A 64 bit integer containing the result
			*/
			static long long	Parse		( std::string value, int radix = 10 );

			/** Parses a string into a 64 bit integer

				@param value String value to parse
				@return A 64 bit integer containing the result
			*/
			static long long	FullParse	( std::string value );

			/** Converts a 64 bit integer value to a string representation

				@param value Boolean to convert
				@param radix Base of the integer
				@return String representation of the value
			*/
			static std::string	ToString	( long long value, int radix = 10 );

			/** Returns the 64 bit integer

				@return 64 bit value
			*/
			long long	Int64Value ( )	{ return value; }

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

			/** Convert to Float

				@return Float value
			*/
			float		FloatValue ( )	{ return (float)value; }

			/** Convert to boolean

				@return Boolean value
			*/
			bool		BooleanValue ( ){ return (value != 0); }

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

			std::string ToString ( ) { return Integer64::ToString ( value, 10 ); }

			static long long MAX_VALUE; ///< Maximum value of this type
			static long long MIN_VALUE; ///< Minimum value of this type

			// Operators
			/** Tests if two values match

				@param right Value to compare
				@return True if the values match
			*/
			bool operator == ( const Integer64 &right );

			/** Tests if two values don't match

				@param right Value to compare
				@return False if the values match
			*/
			bool operator != ( const Integer64 &right );

		private:

			long long value;
		};

	}
}

#endif // _INTEGER64_H_
