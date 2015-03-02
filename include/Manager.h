#ifndef MANAGER_H
#define MANAGER_H

#include "Rapidshare.h"
#include "Buffer.h"

//#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>

using namespace std;
using namespace boost;

class Manager
{
    public:
        Manager();
        
		void createAgentStructure();
		void cloneStructure(string folderPath, string localPath);
		
		File getFile(long fileID);
		File getFile(string url);
		File getFileByPath(string path);
		
		void playFile(string url);
		void playFile(File file);	
		void playFile(string path, int pointer);
		
		void downloadFiles(string path);
		void downloadFiles(string path, string location);

		void downloadFile(string url);
		void downloadFile(string url, string location);
		void downloadFileByPath(string path, string location);
		
		void uploadFile(string path);
		void uploadFile(string path, string destination);
		
		void listFolder(string path);
		void listFolder(Folder folder);
		
		void renameFile(string path, string name);
		void renameFolder(string path, string name);
		
		void deleteFile(string path);
		void deleteFolder(string path);
		
		void createFolder(string path, string name);
		void moveFolder(string path, string newPath);
		void moveFile(string path, string newPath); 
		
		Folder getFolder(string path);
		Folder getFolder(int idFolder);
		
		bool fileExists(string url);
		bool localFileExists(string path);
		
		bool isFile(string path);
		bool isFolder(string path);
		
		void setBuffer(Buffer* gBuffer);
		
		//void setDestination(string location);
		//string getDestination();
		
        virtual ~Manager();
	protected:

	private:
	
        void createDesktopFile(string path, string url, string name);
        Rapidshare rapidshare;
		Buffer* output;
};

#endif // MANAGER_H
