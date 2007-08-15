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

 #include "Event.h"

 namespace MiniUI
 {
 	namespace EventSystem
	{
		///////////////////////////////////////////////////////////////////////
		Event::Event ( )
		///////////////////////////////////////////////////////////////////////
		{

		}

		///////////////////////////////////////////////////////////////////////
		Event::~Event ( )
		///////////////////////////////////////////////////////////////////////
		{
			m_lFunctors.clear ( );
		}

		///////////////////////////////////////////////////////////////////////
		void Event::AddListener ( FunctorBase* functor )
		///////////////////////////////////////////////////////////////////////
		{
			m_lFunctors.push_back ( functor );
		}

		///////////////////////////////////////////////////////////////////////
		void Event::RemoveListener ( FunctorBase *functor )
		///////////////////////////////////////////////////////////////////////
		{
			m_lFunctors.remove ( functor );
		}

		///////////////////////////////////////////////////////////////////////
		void Event::operator () ( )
		///////////////////////////////////////////////////////////////////////
		{
			std::list < FunctorBase* >::iterator i;

			for ( i = m_lFunctors.begin(); i != m_lFunctors.end(); i++ )
				(**i)( this );
		}

	}

}
