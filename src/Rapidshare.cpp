#include "include/Rapidshare.h"

Rapidshare::Rapidshare()
{
    updateFolderList();
	update = false;
}

/**
 * Vrácení následujícího volného uploadserveru
 */
string Rapidshare::getNextUploadServer()
{
    client.addParam("sub", "nextuploadserver");
    return client.getResult();
}
/**
 * Předáme buffer, do kterého budeme vypisovat.
 */  
void Rapidshare::setBuffer(Buffer* gBuffer)
{
	output = gBuffer;
}
/**
 * Vytvoření složky na serveru
 * @param Folder parent Nadrazena slozka.
 * @param string folderName nazev nove slozky
 */ 
void Rapidshare::createFolder(Folder parent, string folderName)
{
	client.addParam("sub", "addrealfolder");
	client.addParam("name", folderName);
	client.addParam("parent", lexical_cast<string>(parent.id));
	
	cout << client.getResult();
	
	//TODO: lze si vzit ID z odezvy a pridat do katalogu
	updateFolderList();
	
}
/**
 * Nahrání souboru na server
 * @param folderId int Nadřazená složka - nejvyšší je 0;
 * @param filePath string Path k souboru.
 */
void Rapidshare::uploadFile(string filePath, Folder folder)
{
	
    string uploadUrl = client.getUrl();

    replace(uploadUrl, "api", "rs" + getNextUploadServer());

    client.setUrl(uploadUrl);
    client.allowProgressBar(true);
	client.setFile(filePath, lexical_cast<string>(folder.id));
    //cout << endl << "## Upload " << endl;
    //cout << "Path: " << filePath << " Destination: " << folder.name <<endl;
	cout << endl << " >>>> "  << filePath << endl;
    client.getResult();
	//cout << endl << "## End" << endl;
	cout << endl;
}
/**
 * Extrahování kusu url.
 * @param string url Url adresa
 * @param string part id | name
 * @return string result
 */
string Rapidshare::getPartFromUrl(string url, string part){
	
    regex re("https://rapidshare.com/files/(.*)/(.*)"), dlServer("DL:(.+[a-z])");
    cmatch matches;

    string id,name;

    if(regex_match(url.c_str(), matches, re)){
        //cout << matches[1];
        id = matches[1];
        name = matches[2];
        //cout << "--" << matches[1] << "---" << matches[2];
    }	
	
	if(part == "id") return id;
	if(part == "name") return name;
	
}
string Rapidshare::getFolderPath(Folder folder){
	
	string path = "";
	Folder parent;
	
	if(folder.isRoot()) return path;
	
	while(!folder.isRoot() && !folder.notFound()){
		
		path = "/" + folder.name + path;
		
		parent = folder;
		folder = getFolder(folder.parent);
		
		if(folder.notFound()){
			cout << "notfound " << folder.name << " : " << parent.id << endl; 
		}
	}
	//cout << path << endl;
	
	return path;
}
/**
 * Dostání konkretni stahovací url, i s cookies
 */
File Rapidshare::getDirectUrl(File &current){
	
	//https://$SERVER/cgi-bin/rsapi.cgi?sub=subroutine&cookie=$COOKIE&sub=download&fileid=$FILEID&filename=$FILENAME
	// http://rs$serverid$shorthost.rapidshare.com
	
	string result = "https://rs";

	result.append(lexical_cast<string>(current.serverId));
	result.append("p" + current.host + ".rapidshare.com/cgi-bin/rsapi.cgi?sub=subroutine&sub=download&bin=0");
	result.append("&cookie=" + client.getCookie());
	result.append("&fileid=" + lexical_cast<string>(current.id));
	result.append("&filename=" + current.name);
	
	current.direct = result;
	
	return current;
	
}
void Rapidshare::downloadFile(File file,string location)
{
	// muze se stat, ze nebude vsechno, proto znova nacteme soubor
	//file = getFile(file.id, file.name);
	
	string dlServer = "rs" + lexical_cast<string>(file.serverId);
	dlServer.append("p" + file.host + ".rapidshare.com");

	string basicUrl = client.getApi();
    replace(basicUrl, "api.rapidshare.com", dlServer);
    client.setUrl(basicUrl);
	
    cout << endl << " >>> " << file.name << endl;

	if(global::DEBUG)
		cout << "DEBUG::" << " remote url: " << basicUrl << " ID: " << file.id << endl;
	
    client.addParam("sub", "download");
    client.addParam("fileid",  lexical_cast<string>(file.id));
    client.addParam("filename", file.name);
	client.allowProgressBar();
    client.setDownloadLocation(location + "/" + file.name);
    client.getResult();
	
	cout << endl;
}
/**
 * Aktualizace výpisu složek, je uložene v lokální proměnné - folders
 */
vector<Folder> Rapidshare::updateFolderList()
{
	
    string line;
    vector<string> atributes;
    client.addParam("sub", "listrealfolders");

    // vymazání starých složek
    folders.clear();
    istringstream iss(client.getResult());


    while (getline(iss,line))
    {

        Folder folder;
        sscanf(line.c_str(),"%d,%d", &folder.id, &folder.parent);

        split(atributes, line, is_any_of(","));
        folder.name = atributes[2];
        folders.push_back(folder);
    }
	
	for(int i = 0; i < (int)folders.size(); i++){
		folders[i].path = getFolderPath(folders[i]);
	}

	
    return folders;
}

/**
 * Vrácení složky podle id
 * @param id Id složky
 * @return Folder Pokud není nalezena složka, vrátí se "root"
 */
Folder Rapidshare::getFolder(long id){

	for(int i = 0; i  < (int)folders.size(); i++){
		//cout << folders[i].name << " : " << folders[i].id << endl;
		if(folders[i].id == id){		
            return folders[i];
        }
    }
	if(id == 0)	
		return Folder(0, 0, "root");
	if(id == 999)
		return Folder(999, 0, "bin");
	
	return Folder(-1);
}
Folder Rapidshare::getFolder(string path){

	if(path == "/"){
		return Folder(0,0,"root");
	}

    for(int i = 0; i  < (int)folders.size(); i++){
        if(folders[i].path == path){
           return folders[i];
        }
    }
	//cout << path;
    return Folder(-1);
	
}

File Rapidshare::getFile(string url)
{
	return getFile(lexical_cast<long>(getPartFromUrl(url, "id")), getPartFromUrl(url, "name"));
}
File Rapidshare::getFile(long id, string name)
{
    vector<string> atributes;
    File file;
	
	client.addParam("sub", "checkfiles");
	client.addParam("files", lexical_cast<string>(id));
	client.addParam("filenames", name);
	
	
    string result = client.getResult();
	
    if(string::npos == result.find("ERROR")){

        split(atributes, result, is_any_of(","));

        file.id = lexical_cast<long>(atributes[0]);
        file.name = atributes[1];
        file.size = atoi(atributes[2].c_str());
		file.serverId = lexical_cast<long>(atributes[3]);
		file.host = atributes[4];
		getDirectUrl(file);

    }	

    return file;	
}

/**
 * Dostání souborů pro určitou složku
 * @param folderId Id složky ze které chceme získat soubory.
 * @return Vector s prvky pole.
 */
vector<File> Rapidshare::getFiles(long folderId)
{
    string line;
    vector<string> atributes;
    vector<File> files;

    client.addParam("sub", "listfiles");
    client.addParam("fields", "filename,size,serverid,realfolder");
    client.addParam("realfolder", lexical_cast<string>(folderId));

    string result = client.getResult();
	
    if(result != "NONE" && string::npos == result.find("ERROR")){

        istringstream iss(result);
        while (getline(iss,line))
        {

            File file;

            split(atributes, line, is_any_of(","));
			//TODO: mozna otazka jestli se to neda nejak zrychlit, nez se znovu dotazovat na kazde
            //file = getFile(lexical_cast<long>(atributes[0]), atributes[1]);
			file.id = lexical_cast<long>(atributes[0]);
            file.name = atributes[1];
            file.size = lexical_cast<long>(atributes[2]);
			file.serverId = lexical_cast<long>(atributes[3]);
			file.folderId = lexical_cast<long>(atributes[4]);
			
            files.push_back(file);
        }
    }
    return files;
}
vector<File> Rapidshare::getFiles(Folder folder){
	return getFiles(folder.id);
}
/**
 * Rename remote file
 */ 
void Rapidshare::renameFile(File file, string newName)
{
	client.addParam("sub", "renamefile");
	client.addParam("fileid", lexical_cast<string>(file.id));
	client.addParam("newname", newName);
	
	client.getResult();
	
}
/**
 * Rename remote folder
 */ 
void Rapidshare::renameFolder(Folder folder, string newName)
{
	client.addParam("sub", "editfolders");
	client.addParam("commands", "folders%3D" + lexical_cast<string>(folder.id) + "%FFname%3D" + newName);
	client.getResult();
	
	// prejmenujeme slozku i na nasem seznamu
	for(int i = 0; i < (int)folders.size(); i++){
		 if(folders[i].id == folder.id){
			 folders[i].name = newName;
		 }
	 }	
	
}
/**
 * Move remote folder
 */ 
 void Rapidshare::moveFolder(Folder folder, Folder parent)
 {
	 client.addParam("sub", "moverealfolder");
	 client.addParam("realfolder", lexical_cast<string>(folder.id));
	 client.addParam("newparent", lexical_cast<string>(parent.id));
	 
	 client.getResult();
	 
	 // posuneme slozku
	 for(int i = 0; i < (int)folders.size(); i++){
		 if(folders[i].id == folder.id){
			 folders[i].parent = parent.id;
			 folders[i].path = getFolderPath(folders[i]);
			 break;
		 }
	 }
	 
 }
/**
 * Move remote file
 */ 
void Rapidshare::moveFile(File file, Folder folder)
{
	client.addParam("sub", "movefilestorealfolder");
	client.addParam("files", lexical_cast<string>(file.id));
	client.addParam("realfolder", lexical_cast<string>(folder.id));
	
	client.getResult();
}
  
/**
 * Delete remote file
 */
void Rapidshare::deleteFile(File file)
{
	client.addParam("sub", "deletefiles");
	client.addParam("files", lexical_cast<string>(file.id));
	
	client.getResult();
	
}
/**
 * Delete remote folder
 * Warning - nefunguje správně, je nutno smazat i všechny soubory, které jsou v těchto složkách.
 */
void Rapidshare::deleteFolder(Folder folder)
{
	/*client.addParam("sub", "delrealfolder");
	client.addParam("realfolder", lexical_cast<string>(folder.id));
	
	client.getResult();

	for(int i = 0; i < (int)folders.size(); i++){
		if(folders[i].id == folder.id)
			folders.erase(folders.begin() + i);
	}*/
	
}
void Rapidshare::writeFolderList(Folder folder)
{
    // aktualizace složek
	if(update == true){
		updateFolderList();
		update = false;
	}
		

    // aktuální složka
    Folder current;

    // soubory
    vector<File> files;

    bool found = false;
    if(folder.isRoot())
    {
        found = true;
        current = folder;
    }
	
    // vypsání první úrovně složek
    for(int i = 0; i < (int)folders.size(); i++)
    {
        // nalezení aktuální složky
        if(folders[i].id == folder.id && !found)
        {
            current = folders[i];
            //cout << "Aktuální složka : " << current.name << " : " << current.id << endl;

            found = true;
            i = 0;

            // vypsání souborů
			//writeFilesList(current);
        }

        // Našli jsme nadřazenou složku, můžeme začít vypisovat children
        if(folders[i].parent == folder.id && found)
        {
            output->writeLine(folders[i].name);
			current = folders[i];
            // vypsání souborů
            /*files = getFiles(folders[i].id);
            for(int z = 0; z < (int)files.size(); z++)
            {
                cout << "* " << files[z].name  << " | " << files[z].id << "\n";
            } */
            /*// Druhá úroveň složek
            for(int j = 0; j < (int)folders.size(); j++)
            {
                if(folders[j].parent == folders[i].id)
                {
                    cout << "-->" << folders[j].name << " : " << folders[j].id << endl;
                }
            }*/

        }
		

    }
	writeFilesList(folder);
}
/**
 * Vypíše soubory v dané složce.
 */ 
void Rapidshare::writeFilesList(Folder folder){

	vector<File> files = getFiles(folder.id);
	string result;
	for(int z = 0; z < (int)files.size(); z++)
	{
		result = "";
		result += lexical_cast<string>(z + 1);
		result += "* ";
		result += files[z].name;
		output->writeLine(result);
	}
	
}
/**
 * Funkce rozebere aktuální url a vybere danou složku.
 */
/*
Folder Rapidshare::getFolder(string folderPath)
{

    // aktualizujeme folder list
    updateFolderList();

    Folder result;

    // rozebereme path
    vector<string> pathParts;
    boost::split(pathParts, folderPath, boost::is_any_of("/"));

    //cout << folders[0] << "/" << folders[1] << "/" << folders[2];

    for(int i = 1; i < (int)pathParts.size(); i++)
    {
        //if(folders[i].name == )

    }
    return result;


}*/

Rapidshare::~Rapidshare()
{
    //dtor
}


bool Rapidshare::replace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
