#ifndef FOLDER_H
#define FOLDER_H

#include <iostream>

using namespace std;

class Folder
{
    public:
        int id, parent;
        string name, path;
        bool check; //pomucka pri vypisovani adresare

        Folder();
        Folder(int a, int b, string c);
		Folder(int a);
		bool isRoot();
		bool notFound();
        virtual ~Folder();
    protected:
    private:
};

#endif // FOLDER_H
