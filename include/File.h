#ifndef FILE_H
#define FILE_H

//#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

class File
{
    public:
        long id, serverId, size, folderId;
        int status;
        string name, host, md5, direct, type;
	
        File();
        File(long fileId, string fileName, long fileSize);
		File(long fileId);
		

		bool notFound();
        string getUrl();
        virtual ~File();
		
		operator int() const { return size; }
		
    protected:
    private:
};

#endif // FILE_H
