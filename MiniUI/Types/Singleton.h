/********************************************************************

FileName		: Singleton.h
Author			: Mark Glenn
Date Of Creation: 9/8/2003

Description:
This class defines the singleton methodology: "a class that
can have only one instance and defines a global accessor for
that class."

Create a singleton class by defining it as described:
class CMyClass : public Singleton <CMyClass>

And access it as described:
CMyClass::Instance()->MyMethod (...);

*********************************************************************/

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "../Exception.h"

namespace MiniUI
{
	namespace Types
	{
		DEFINE_EXCEPTION ( CreationException, "Object could not be created in this context" );

		/**
			Singleton base class

			The Singleton class defines the singleton methodology: A class
			that can have only one instance and defines a global accessor for that
			instance.

			To create a singleton class, define the class as follows:
\code
class CMyClass : Singleton <CMyClass>
\endcode

			And then to access it,
\code
CMyClass::Instance()->MyNonStaticMethod (...);
\endcode
		*/
		template <class t>
		class Singleton
		{
		public:

			/** Constructor.

				Stores the instance and will throw an exception if any other
				instances are created */
			Singleton()
			{
				if (instance != NULL)
					throw CreationException ( );

				instance = (t *)this;
			}

			/** Destructor.

				Destroys the instance for another singleton to take it's place */
			virtual ~Singleton()
			{
				instance = NULL;
			}

			/** Access to the instance

				@returns The instance to the class */
			static t *Instance()
			{
				return instance;
			}

		private:
			static t *instance;

			// Disabled operators
			Singleton &operator =	(const Singleton &);
			Singleton				(const Singleton &);
		};
		//////////////////////////////////////////////////////////////////////

		template <class t>
		t *Singleton<t>::instance = NULL;
	}
}

#endif
