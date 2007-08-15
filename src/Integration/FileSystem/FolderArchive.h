#ifndef _FOLDERARCHIVE_H_
#define _FOLDERARCHIVE_H_

#include <fstream>
#include <string>
#include <MiniUI/Host/IArchive.h>

namespace Integration
{
	namespace FileSystem
	{
		class FolderArchive : public MiniUI::Host::IArchive
		{
		public:
			FolderArchive(std::string folderName);
			virtual ~FolderArchive(void);

			virtual std::string	GetArchiveName () { return m_szFolderName; }
			virtual std::istream* LoadFile (std::string filename);
			virtual bool FileExists ( std::string filename );

		private:
			std::string m_szFolderName;
		};
	}
}
#endif
