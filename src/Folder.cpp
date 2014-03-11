#include "include/Folder.h"

Folder::Folder()
{
    check = false;
}
Folder::Folder(int a){
	id = a;
}
Folder::Folder(int a, int b, string c)
{
    id = a;
    parent = b;
    name = c;
    check = false;
	
	if(name == "root"){
		path = "/";
		
	}
	
};
bool Folder::isRoot()
{
	if(id == 0){
		return true;
	}else{
		return false;
	} 
	
}
bool Folder::notFound(){
	
	if(id < 0)
		return true;
	else
		return false;
	
}
Folder::~Folder()
{
    //dtor
}
