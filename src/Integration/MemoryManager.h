#ifndef _MEMORYMANAGER_H_
#define _MEMORYMANAGER_H_

#include <MiniUI/Host/IMemory.h>

namespace Integration
{
	class MemoryManager : public MiniUI::Host::IMemory
	{
		virtual void* Allocate ( unsigned int size );
		virtual void Deallocate ( void* pData );
		virtual void* Reallocate ( void *pData, unsigned int newSize );
	};
}

#endif // _MEMORYMANAGER_H_
