#include "include/File.h"

File::File()
{
	size = 0;
}


File::File(long fileId, string fileName, long fileSize)
{
    id = fileId;
    name = fileName;
    size = fileSize;
    //status = fileStatus;
    //host = fileHost;
}
File::File(long fileId){
	id = fileId;
}
bool File::notFound(){
	
	if(id == -1){
		return true;
	}
	return false;
	
}
/**
 * Vrátí url ve formátu pro http browser.
 */
string File::getUrl(){

    string url = "https://rapidshare.com/files/";

    url += boost::lexical_cast<string>(id);
    url += "/";
    url += name;

    return url;

}

File::~File()
{
    //dtor
}
