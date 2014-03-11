#ifndef BROWSER_H
#define BROWSER_H

#include <iostream>
#include <boost/algorithm/string.hpp>

#include "Global.h"
#include <include/Manager.h>
#include <include/Buffer.h>

using namespace std;
using namespace boost;


class Browser {

public:

	Browser();
	Manager manager;
	Buffer buffer;
	
	void copy(string path, string location, bool local);
	void play(string path);
	void play(string folder, int position);
	void rename(string path, string name);
	void rm(string path);
	void mkdir(string path, string name);
	void mv(string path, string newPath);
	void showHelp();
	
	string getCurrentPath(string part);
	
	vector<string> processParams(string input, string param, int count);
	
	~Browser();
private:
	
	bool isLocal(string& path);
	
	Folder pwd;
	string path;

};

#endif // BROWSER_H
