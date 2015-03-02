
#include "include/Manager.h"

Manager::Manager()
{
	//cloneStructure("/Test", "/home/worker/Structure/");
	//renameFile("/Test/file.avi", "new-file-name.avi");
	//rapidshare.deleteFolder(Folder(5857, 0, "Folder"));
    //rapidshare.getFiles(2223);
    //mkdir("/home/worker/ahoj", S_IRWXU);
    //createDesktopFile("/home/worker/Temp/", "https://rapidshare.com/files/740499837/flash.forward.s01e22.hdtv.xvid.mkv", "Star Gate");
}
/**
 * Vytvoření struktury složek společně se zástupy pro video.
 * @param string default_path Cesta ke složce, kde se bude tvořit struktura
 * @param int folder Složka, která bude root.
 */
void Manager::createAgentStructure(){

    bool x = true, found;
    int zanoreni = 0;

    string default_path = "/home/worker/Structure/", path;
    vector<Folder> folders = rapidshare.folders;

    Folder max = getFolder("/Test");
    Folder current = max;


    cout << "Creating folder image : " << max.name << " on location " << default_path << endl;

    while(x){

        found = false;

        for(int i = 0; i < (int)folders.size(); i++){

            // nalezneme složku a ještě jsme ji prošly
            if(folders[i].parent == current.id && folders[i].check == false){

                current = folders[i];

                for(int y = 0; y < zanoreni; y++){
                    cout << "  ";
                }

                cout << current.name << endl;

                folders[i].check = true;
                found = true;
                // řešení pathu
                path += current.name + "/";
                // vytvoření složky
                mkdir((default_path + path).c_str(), S_IRWXU);

                // vytvoření zástupce
                vector<File> files = rapidshare.getFiles(current.id);
                for(int z = 0; z < (int)files.size(); z++){
                    createDesktopFile(default_path + path, files[z].getUrl(), files[z].name);
                }
                zanoreni++;
                break;
            }

        }
        if(found == false){

            if(current.parent == max.parent){
                x = false;
            }else{

                path = path.substr(0, path.size() - (current.name.size() + 1));

                current = rapidshare.getFolder(current.parent);
                zanoreni--;
            }

        }
    }

}
/**
 * Klonování slozky z disku na vzdaleny server.
 * 
 */
/*void Manager::cloneLocalStructure(string localPath, string remotePath)
{
	
	
	
}*/
/**
 * Naklonuje strukturu z remote serveru a stahne do ni vsechny soubory.
 * @param string FolderPath Cesta ke slozce, kterou chceme zkopirovat.
 * @param string localPath Cesta ke slozce na disku, kam chceme obraz vytvorit.
 */ 
void Manager::cloneStructure(string folderPath, string localPath){

    bool x = true, found;
    int zanoreni = 0;

    //string default_path = "/home/worker/Structure/", path;
    string path;
	vector<Folder> folders = rapidshare.folders;

    Folder max = getFolder(folderPath);
    Folder current = max;
	
	// vytvoreni max slozky
	mkdir((localPath + max.name).c_str(), S_IRWXU);
	path += max.name + "/";

    cout << endl << "Creating copy of : " << max.name << " on :" << localPath << endl;

    while(x){

        found = false;
        for(int i = 0; i < (int)folders.size(); i++){

            // nalezneme složku a ještě jsme ji prošly
            if(folders[i].parent == current.id && folders[i].check == false){

                current = folders[i];

                for(int y = 0; y < zanoreni; y++){
                    cout << "  ";
                }
				
                //cout << current.name << endl;

                folders[i].check = true; // slozka je prosla
                found = true; // a nasly sme
				
                // řešení pathu
                path += current.name + "/";
                // vytvoření složky
                mkdir((localPath + path).c_str(), S_IRWXU);
				
                // stahneme soubory
                vector<File> files = rapidshare.getFiles(current);
                for(int z = 0; z < (int)files.size(); z++){
					
					File file = rapidshare.getFile(files[z].id, files[z].name);
                    rapidshare.downloadFile(file, localPath + path);
                
				}
                zanoreni++;
                break;
            }

        }
	
        if(found == false){
			// pokud sme v nejvyssim patre
            if(current.parent == max.parent){
                x = false;
				
				// stahneme vsechny soubory
				vector<File> files = rapidshare.getFiles(current);
                for(int z = 0; z < (int)files.size(); z++){
					
					File file = rapidshare.getFile(files[z].id, files[z].name);
                    rapidshare.downloadFile(file, localPath + path);
                
				}
			
            }else{
				// jinak pokracujeme
                path = path.substr(0, path.size() - (current.name.size() + 1));
                current = rapidshare.getFolder(current.parent);
                zanoreni--;
            }

        }
    }

}
/**
 * Kontrola souboru podle url.
 * @param string url Url adresa souboru.
 */ 
bool Manager::fileExists(string url){
	
	return (bool)getFile(url);
}
/**
 * Kontrola lokálního souboru.
 * @param string path Path k souboru. 
 */
bool Manager::localFileExists(string path)
{
	FILE* fp = NULL;
    fp = fopen(path.c_str(), "rb");
    if(fp != NULL)
    {
        fclose(fp);
        return true;
    }

    return false;	
}
/**
 * Prejmenovani souboru.
 * @param string path
 * @param string name Novy nazev souboru.
 */ 
void Manager::renameFile(string path, string name)
{
	File file = getFileByPath(path);
	rapidshare.renameFile(file, name);
}
void Manager::renameFolder(string path, string name)
{
	Folder folder = getFolder(path);
	rapidshare.renameFolder(folder, name);
}
/**
 * Smazání souboru.
 */ 
void Manager::deleteFile(string path)
{
	File file = getFileByPath(path);
	rapidshare.deleteFile(file);
}
/**
 * Smazání složky.
 */  
 void Manager::deleteFolder(string path)
 {
	Folder folder = getFolder(path);
	rapidshare.deleteFolder(folder);
 }
/**
 * Stažení jedoho souboru.
 * @param string url 
 * @param string location
 */ 
void Manager::downloadFile(string url, string location){
	
	File current = getFile(url);
	if(!current){
		cout << "File not found!!";
	}else{
		rapidshare.downloadFile(current, location);
	}
	
}
void Manager::downloadFileByPath(string path, string location)
{
	File current = getFileByPath(path);
	if(!current){
		cout << "File not found!!";
	}else{
		rapidshare.downloadFile(current, location);
	}
}
/**
 * Stažení jedoho souboru.
 * @param string url 
 */ 
void Manager::downloadFile(string url){
	
	// defaultni location je slozka kde se aktualne pracuje
	FILE *output = popen("pwd", "r");
	
	char location[512];
	fgets(location, 512, output);
	
	File current = getFile(url);
	if(!current){
		cout << "File not found!!";
	}else{
		rapidshare.downloadFile(current, location);
	}
	
}
/**
 * Stažení více souboru, vetsinou v .txt
 */ 
void Manager::downloadFiles(string path, string location){
	
	ifstream file(path.c_str(), ios::in);
	
	File current;
	string url;
	while(getline(file, url)) // Read line by line
	{
		current = getFile(url);
		
		if(!current){
			cout << url << " : not found"  << endl; 
		}else{
			rapidshare.downloadFile(current, location);
		}
	}
	
	
}
void Manager::downloadFiles(string path){
	
	ifstream file(path.c_str(), ios::in);
		
	// defaultni location je slozka s links.txt
	FILE *output = popen(("dirname " + path).c_str(), "r");
	
	char res[512];
	fgets(res, 512, output);
	
	string location = res;
	algorithm::trim(location); // zbavime se mezer

	File current;
	string url;
	while(getline(file, url)) // Read line by line
	{
		current = getFile(url);
		
		if(!current){
			cout << url << " : not found"  << endl; 
		}else{
			rapidshare.downloadFile(current, location);
		}
	}
	
	
}
/**
 * Overi zda se jedna o slozku.
 */ 
bool Manager::isFolder(string path){
	
	if(getFolder(path).notFound()){
		return false;
	}
	return true;
	
}
/**
 * Jedna se o soubor?
 */ 
bool Manager::isFile(string path){
	
	if(getFileByPath(path).notFound()){
		return false;
	}
	return true;
	
}
void Manager::moveFolder(string path, string newPath)
{
	Folder folder = getFolder(path);
	Folder newFolder = getFolder(newPath);
	
	rapidshare.moveFolder(folder, newFolder);
}
void Manager::moveFile(string path, string newPath)
{
	File file = getFileByPath(path);
	Folder folder = getFolder(newPath);
	
	rapidshare.moveFile(file, folder);
}
/**
 * Upload souboru.
 */
void Manager::uploadFile(string path){
	
	// upload in root
	rapidshare.uploadFile(path, Folder(0,0, "root"));
	 
} 
void Manager::uploadFile(string path, string destination){
	 
	Folder folder = getFolder(destination);
	rapidshare.uploadFile(path, folder);
	 
}
void Manager::createFolder(string path, string name)
{
	Folder folder = getFolder(path);
	rapidshare.createFolder(folder, name);
}
Folder Manager::getFolder(string path){
	
	trim(path);
	Folder result = rapidshare.getFolder(path);
	return result;
	
}
Folder Manager::getFolder(int idFolder){
	return rapidshare.getFolder(idFolder);
}
/**
 * Vrátí vybraný rapidshare soubor.
 */
File Manager::getFile(string url){
	return rapidshare.getFile(url);
}

/**
 * Ziskani souboru pomoci path
 */ 
File Manager::getFileByPath(string path){
				
	vector<string> pieces;
	string fileName;

	split(pieces, path, is_any_of("/"));
	
	// odstrihneme soubor i s lomitkem
	path = path.substr(0, path.length() - (pieces.back().size() + 1));
	fileName = pieces.back();
	// nazev souboru v poslednim prvku
	//cout << "path : " << path << " file: " << pieces.back() << endl;
	
	Folder folder;
	// pokud se jedna o root
	if(path == "" && fileName != ""){
	
		folder = Folder(0,0, "root");
		
	}else{
		// overime slozku
		folder = getFolder(path);
	}
	

	
	if(folder.notFound()){
		cout << "Cesta neexistuje" << endl;
		return File(-1);
	}
	
	vector<File> files = rapidshare.getFiles(folder);
	for(int i = 0; i < (int)files.size(); i++){
		if(files[i].name == fileName){
			
			// jelikoz nemame vsechno, musime znovu nacist cely soubor
			return rapidshare.getFile(files[i].id, files[i].name);
			
		}
	}
	
	return File(-1);	
	

}
/**
 * Přehrání daného odkazu
 * @param string url Url odkazu.
 */ 
void Manager::playFile(string url){
	
	File file = getFile(url);
	playFile(file);
	
}
void Manager::playFile(File file){
	
	string command;
	if(!file){
		cout << "File doesn't exists";
		exit(1);
	}
	if(global::player == "vlc")
		command = "vlc --file-logging=/home/worker/log.txt --no-video-title-show '" + file.direct + "' > /dev/null 2>&1 &";
	if(global::player == "totem")
		command = "totem '" + file.direct + "' > /dev/null 2>&1 &";
		
	system(command.c_str());
	
}
void Manager::playFile(string path,int pointer)
{
	Folder folder = getFolder(path);
	vector<File> files = rapidshare.getFiles(folder);
	
	// projdeme soubory
	for(int i = 0; i < (int)files.size(); i++){
		if(i == (pointer - 1)){	
			playFile(rapidshare.getFile(files[i].id, files[i].name));
		}
	}
	
}
/**
 * Vypsání obsahu složek.
 */ 
void Manager::listFolder(string path){
	
	trim(path);
	Folder folder;
	
	if(path == "/"){
		folder = Folder(0,0, "root");
	}else{
		folder = getFolder(path);
	}
		 
	rapidshare.writeFolderList(folder);
		
}
void Manager::listFolder(Folder folder){
	rapidshare.writeFolderList(folder);
}
/**
 * Předáme buffer, do kterého budeme vypisovat.
 */  
void Manager::setBuffer(Buffer* gBuffer)
{
	output = gBuffer;

	// predame buffer zase dale
	rapidshare.setBuffer(output);
	
}
/**
 * Vytvoření zástupce na desktop.
 */
void Manager::createDesktopFile(string path, string url, string name){

    path += name;
    path += ".desktop";
    ofstream file(path.c_str());
    // hlavička
    file << "[Desktop Entry]" << endl << "Type=Application" << endl << "Encoding=UTF-8" << endl;

    file << "Name=" << name << endl;
    file << "Exec=rapidshare -p " << url << endl;

    // patička
    file << "Icon=video.png" << endl << "Terminal=false" << endl;

}

Manager::~Manager()
{
    //dtor
	cout << endl;
}
