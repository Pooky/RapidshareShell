#ifndef RAPIDSHARE_H
#define RAPIDSHARE_H

#include <iostream>
#include <boost/lexical_cast.hpp>

#include "Folder.h"
#include "File.h"
#include "Buffer.h"
#include "curlClient.h"
#include "Global.h"

#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include <vector>
#include <sstream>

using namespace std;
using namespace boost;

class Rapidshare
{
    public:
        Rapidshare();
        virtual ~Rapidshare();

        string getNextUploadServer();
		string getPartFromUrl(string url, string part);
		string getFolderPath(Folder folder);
		
		void setBuffer(Buffer* gBuffer);
        void uploadFile(string filePath, Folder folder);
        void downloadFile(File file, string location);
		
		void renameFile(File file, string newName);
		void renameFolder(Folder folder, string newName);
		
		void deleteFile(File file);
		void deleteFolder(Folder folder);
		
        void writeFolderList(Folder folder);
		void writeFilesList(Folder folder);

        Folder getFolder(long id);
		Folder getFolder(string path);
		
		void createFolder(Folder parent, string folderName);
		
		void moveFolder(Folder folder, Folder parent);
		void moveFile(File file, Folder folder);
		
        File getFile(string url);
		File getFile(long id, string name);
		File getDirectUrl(File &current);
        //Folder getFolder(string folderPath);

        vector<Folder> updateFolderList();
        vector<File> getFiles(long folderId);
		vector<File> getFiles(Folder folder);

        vector<Folder> folders;
		
		bool update;
    protected:
        string result, buffer;
        curlClient client;
		Buffer* output;
    private:
        bool replace(std::string& str, const std::string& from, const std::string& to);
};

#endif // RAPIDSHARE_H
