#include "Browser.h"

Browser::Browser()
{	
	string input, destination, newpath;
	path = "/";
	vector<string> params;
	
	// pass buffer
	manager.setBuffer(&buffer);
	
	string command;
	pwd = Folder(0, 0, "root");

	// WELCOME
	//printw("%s", "## Welcome in Rapidshare Manager \n");
	//printw("%s", "rs#~/ ");
	
	//refresh();
	//move(linenum,6);
	//cout << "## Welcome in Rapidshare Manager" << endl;
	//cout << "rs#~/ ";
	
	while(true) {
		
		input = buffer.getCommand();
		//getline(cin, input);
		//printw("---- %s -----", input.c_str());
		trim(input);
		split(params, input, is_any_of(" "));

		command = params[0];
	
		if(command == "ls"){
			manager.listFolder(pwd);
		}
		if(command == "help"){
			showHelp();
		}
		if(command == "mv"){
			
			params = processParams(input, command, 2);
			
			mv(getCurrentPath(params[0]), getCurrentPath(params[1]));
			
		}
		if(command == "cd"){
			
			params = processParams(input, "cd", 1);
					
			if(params[0] == ".."){
				if(!pwd.isRoot()){
					pwd = manager.getFolder(pwd.parent);
					path = pwd.path;
				}else{
					path = "/";
				}
					
			}else{		
				
				if(pwd.isRoot()){
					path = pwd.path + params[0];
				}else{
					path = pwd.path + "/" + params[0];
				}
				
				if(manager.getFolder(path).notFound()) {
					cout << "not found" << endl;
				}else{
					pwd = manager.getFolder(path);
				}			
			}
			
		}
		if(command == "cp"){	
			
			params = processParams(input, "cp", 2);		
			if(params.size() == 2){
				bool local = isLocal(params[0]);
				string destination;
				
				if(local){
					destination = getCurrentPath(params[1]);
					path = params[0];
					
				}else{				
					path = getCurrentPath(params[0]);
					destination = params[1];
				
				}
				copy(path, destination, local);				
			}
			
		}
		if(command == "pwd"){
			cout << pwd.path << endl;
		}
		if(command == "play"){
			
			
			params = processParams(input, command, 1);	
			/*if(params.size() == 1){
				
				bool isNumber = true;
				// jedna se o cislo?
				for(int i = 0; i < (int)params.size();i++){
					if(!isdigit(params[0][i])){
						isNumber = false;
					}
				}
				
				if(isNumber){
					play(pwd.path, lexical_cast<int>(params[0]));
				}else{
					play(getCurrentPath(params[0]));
				}
				
			}else{
				cout << "Wrond number of params" << endl;
			}*/

			
			
			
		}
		if(command == "clear"){
			system("clear");
		}
		if(command == "mkdir")
		{
			params = processParams(input, command, 1);
			mkdir(pwd.path, params[0]);
		}
		if(command == "rename"){
			
			params = processParams(input, "rename", 2);
			path = getCurrentPath(params[0]);
			rename(path, params[1]);
		}
		if(command == "rm")
		{
			
			params = processParams(input, command, 1);
			path = getCurrentPath(params[0]);
			rm(path);
			
		}
		if(command == "exit"){
			
			// ukoncime ncurses
			endwin();
			exit(1);
		}
		
		//cout  << "rs#~" << pwd.path << " ";
		buffer.changeStart("rs#~" + pwd.path + " ");
		buffer.writeStart();
		
	};
	
	cout << endl;
}
void Browser::showHelp()
{
	cout << "Availible commands :" << endl;
	cout << "\t help - write this help " << endl;
	cout << "\t pwd - show working directory " << endl;
	cout << "\t ls - write content of actual folder" << endl;
	cout << "\t mv - move FILE or FOLDER to new location \n \t\t mv /Test /Test/Example" << endl;
}
/**
 * Vrátí soucasnou adresu a prida k ni zbytek cesty.
 */ 
string Browser::getCurrentPath(string part)
{
	//cout << part << endl;
	string result;
	// pokud zaciname lomitkem, jedna se o abosolutni cestu
	if(part[0] == '/'){
		//cout << part << endl;
		return part;
	}
	
	if(pwd.isRoot() || part == ""){
		result = pwd.path + part;
	}else{
		result = pwd.path + "/" + part;
	}	
	//cout << result << endl;
	return result;
}

void Browser::mv(string path, string location)
{
	if(manager.isFile(path)){
		manager.moveFile(path, location);
	}
	if(manager.isFolder(path)){
		manager.moveFolder(path, location);
	}
}

void Browser::copy(string path, string location, bool local)
{
	
	// jedna se o UPLOAD
	if(local){
		//cout << path << endl;
		if(manager.localFileExists(path))
			manager.uploadFile(path, location);	
		else
			cout << "Local file doesn't exists!" << endl;
			
			
	}
	if(isLocal(location))
	{
		//cout << path << endl;
		// jedna se o soubor?
		if(manager.isFile(path)){
			manager.downloadFileByPath(path, location);
		}
		if(manager.isFolder(path)){		
			// taky zkontrolujeme posledni adresu
		
			if(location[location.size()] != '/')
			{
				location.append("/");
			}
			
			manager.cloneStructure(path, location);
		}
			
	}

}
void Browser::rename(string path, string name)
{
	if(manager.isFile(path))
		manager.renameFile(path, name);
	if(manager.isFolder(path))
		manager.renameFolder(path, name);
}
void Browser::mkdir(string path, string name)
{
	manager.createFolder(path, name);
}
void Browser::rm(string path)
{
	string confirm;
	// Je nutno se zeptat.
	cout << endl << "Are you shure? [yes/no] ";
	getline(cin, confirm);
	
	
	if(manager.isFile(path))
	{			
		if(confirm == "yes")
		{
			manager.deleteFile(path);
		}
		
	}
	/**
	 * Nutno dopracovat strom smazání složky, zatím nefunkcni. 
	 */
	if(manager.isFolder(path))
	{
		if(confirm == "yes")
		{
			//manager.deleteFolder(path);
		}		
	}
}
vector<string> Browser::processParams(string input, string param, int count)
{
	
	vector<string> params;
	trim(input);
	
	string res = input.substr(param.size() + 1);
	
	// pokud mame jenom parametr, vratime vsechno za pozici
	if(count == 1){
			
		// odstranime uvozovky
		res.erase(
			remove(res.begin(), res.end(), '\"' ),
			res.end()
		);
		params.push_back(res);
	}
	if(count == 2){
		
		vector<string> pieces;
		split(pieces, res, is_any_of("\""));
		
		// zkusime tedy mezery
		if(pieces.size() != 4){
			
			split(pieces, res, is_any_of(" "));
			if(pieces.size() == 2){
				
				params.push_back(pieces[0]);
				params.push_back(pieces[1]);
			}

		}
		if(pieces.size() == 4){
			params.push_back(pieces[1]);
			params.push_back(pieces[3]);
		}
		

		
	}
	// zkontrolujeme znaky
	for(int i = 0; i < (int)params.size(); i++){
		if(params[i] == ".")
			params[i] = "";
	}
	
	if(params.size() != count){
		cout << "Wrong number parameters" << endl;
	}
	buffer.writeLine(lexical_cast<string>(params.size()));
	//cout << params[0] << endl;
	//cout << params[1] << endl;
	return params;
	
}
void Browser::play(string path){
	
	manager.playFile(manager.getFileByPath(path));
	
}
void Browser::play(string folder, int position)
{
	manager.playFile(folder, position);
}
/**
 * Funkce overi zda se jedna o local nebo remote (mysleno local na desktop PC)
 * @param string path
 */ 
bool Browser::isLocal(string& path)
{
	if(path[0] == '@'){
		// jedna se o local adresu, potvrdime a odebereme
		path.erase(0,1);
		return true;
	}
	return false;
}

Browser::~Browser()
{
	
}

