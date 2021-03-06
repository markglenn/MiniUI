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

#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

namespace MiniUI
{
	namespace EventSystem
	{
		class Event;

		class FunctorBase
		{
		public:
			virtual void operator () ( Event * ) = 0;
		};

		template <class T>
		class Functor : public FunctorBase
		{
		protected:
			T* m_pObject;
			typedef void (T::*funcType) ( Event * );
			funcType m_oFunction;

		public:
			Functor ( T* pObj, funcType func )
				{ m_pObject = pObj; m_oFunction = func; }

			virtual void operator () ( Event * event )
				{ ( m_pObject->*m_oFunction) ( event ); }
		};
	}

}

#endif // _FUNCTOR_H_
