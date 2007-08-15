#include <sys/stat.h>

#include "FolderArchive.h"

using namespace std;

#ifdef WIN32
#define statstruct __stat64
#define statfunc _stat64
#else
#define statstruct stat
#define statfunc stat
#endif

namespace Integration
{
	namespace FileSystem
	{
		///////////////////////////////////////////////////////////////////////
		FolderArchive::FolderArchive(string szFolderName)
		///////////////////////////////////////////////////////////////////////
		{
			m_szFolderName = szFolderName;

			// Add in the last slash
			if (m_szFolderName.c_str()[m_szFolderName.length() - 1] != '/')
				m_szFolderName.push_back ('/');
		}

		///////////////////////////////////////////////////////////////////////
		FolderArchive::~FolderArchive(void)
		///////////////////////////////////////////////////////////////////////
		{
		}

		///////////////////////////////////////////////////////////////////////
		bool FolderArchive::FileExists (string filename)
		///////////////////////////////////////////////////////////////////////
		{
			struct statstruct buf;

			if (!statfunc ( (m_szFolderName + filename).c_str(), &buf ) )
			return true;

			return false;
		}

		///////////////////////////////////////////////////////////////////////
		istream* FolderArchive::LoadFile (string filename)
		///////////////////////////////////////////////////////////////////////
		{
			ifstream *pStream = new ifstream ((m_szFolderName + filename).c_str());

			// If the file isn't open, return null
			if (!pStream->is_open())
			{
				delete pStream;
				return NULL;
			}

			// Return the stream pointer
			return pStream;
		}

	}

}
