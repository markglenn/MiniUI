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

#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_

#include <string>
#include "Integer.h"

namespace MiniUI
{
	namespace Types
	{
		DEFINE_EXCEPTION ( BooleanFormatException, "Invalid boolean format" );

		/** Boolean storage container and parser */
		class Boolean
		{
		public:
			/// Constructor
			Boolean(void);

			/** Constructor
				
				@param value Set value
			*/
			Boolean( bool value );

			/** Constructor

				@param value String value to parse
			*/
			Boolean( std::string value );

			/// Destructor
			virtual ~Boolean(void);

			/** Parses a string into a boolean

				@param value String value to parse ('True', 'false', 't', 'F')
				@return A boolean containing the result
			*/
			static bool ParseBoolean ( std::string value );
			
			/** Converts a boolean value to a string representation

				@param value Boolean to convert
				@return String representation of the value ('true', 'false')
			*/
			static std::string ToString ( bool value );

			/** Gets the value

				@return Stored value
			*/
			bool BooleanValue ( ) { return value; }

			/** Returns the string value of the stored value

				@return String representation of the value ('true', 'false')
			*/
			std::string ToString ( );

			/** Tests if two values match

				@param right Value to compare
				@return True if the values match
			*/
			bool operator == ( const Boolean &right );

			/** Tests if two values don't match

				@param right Value to compare
				@return False if the values match
			*/
			bool operator != ( const Boolean &right );

		private:

			bool value;

		};
	}
}

#endif // _BOOLEAN_H_
