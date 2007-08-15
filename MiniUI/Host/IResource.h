#ifndef _MINIUI_RESOURCES_IRESOURCE_H_
#define _MINIUI_RESOURCES_IRESOURCE_H_

namespace MiniUI
{
	namespace Host
	{
		class IResource
		{
		public:
			virtual size_t 	read ( void *, size_t count ) = 0;
			virtual std::string readline ( ) = 0;

			virtual size_t 	size ( )	= 0;
			virtual bool 	eof ( )		= 0;
			virtual void 	close ( )	= 0;

		};
	}
}

#endif // _MINIUI_RESOURCES_IRESOURCE_H_
