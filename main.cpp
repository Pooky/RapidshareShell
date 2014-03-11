#include "include/Global.h"

#include "include/Rapidshare.h"
#include "include/Manager.h"
#include "include/Browser.h"

using namespace std;


void showHelp(){
	
	cout << "## Rapidshare manager 0.1 beta \n";
	cout << "This script help manage files from rapidshare.\n\n";
	cout << "OPTIONS: \n";
	cout << "\t -h Show this message.\n";
	cout << "\t -d Download specific file.\n";
		//cout << "\t\t - can be rapidshare url like https://rapidshare.com/file \n";
		//cout << "\t\t - file with links one per line.\n";
	cout << "\t -u Upload specific file.\n";
	cout << "\t -l Specify location - download or upload.\n";
	cout << "\t -p Play specific file.\n";
	
}
int main(int argc, char **argv)
{   
	//setlocale(LC_ALL, "cs_CZ.utf8");
	//Manager manager;
	string action, param, location;
	
	char c;
    while (( c = getopt (argc, argv, "hl:d:u:p:b:X")) != -1)
    {
        switch (c)
        {
        case 'h':
			showHelp();
            break;
        case 'p':
		    //manager.playFile(optarg);			       
			break;
		case 'l':
			location = optarg;
			break;
        case 'd':
			action = "download";
			param = optarg;
            break;
		case 'u':
			action = "upload";
			param = optarg;
			break;
		case 'b':
			//manager.listFolder(optarg);
			break;
		case 'X':
			Browser();
			break;
        case '?':
			cout << "?";
			break;
        default:
			break;
        }
    }
	if(argc < 2){
		showHelp();
	}
	/*
	if(action != ""){
		// stahovani
		if(action == "download"){			
			// kontrola zda soubor existuje soubor
			if(ifstream(param.c_str())){
				if(location != ""){
					manager.downloadFiles(param, location);
				}else{
					manager.downloadFiles(param);
				}
					
			}else{
				if(location != ""){
					manager.downloadFile(param, location);
				}else{
					manager.downloadFile(param);
				}
			}	
		}
		if(action == "upload"){
			if(ifstream(param.c_str())){
				if(location != ""){
					manager.uploadFile(param, location);
				}else{
					manager.uploadFile(param);
				}
					
			}else{
				cout << "File : " << param << " not found." << endl;
			}				
		}
	}
	*/
	//manager.uploadFile("/home", "home");
	//manager.listFolder("/");
	//manager.playFile("https://rapidshare.com/files/2334287317/13x11_-_Srdci_neporu______.avi");
	//cout << rapidshare.getNextUploadServer();
    //rapidshare.uploadFile("/home/worker/rapidshare.zip", 8884);
    //rapidshare.writeFolderList(8884);
	//manager.downloadFiles("/home/worker/links.txt", "/home/worker");
	//manager.downloadFile("https://rapidshare.com/files/1986869849/pixel.pdf");
			
	//cout << file.direct;
    //rapidshare.downloadFile("https://rapidshare.com/files/2389973288/xxx2.rar");
    //rapidshare.downloadFile("https://rapidshare.com/files/1986869849/pixel.pdf");
    //rapidshare.downloadFile("https://rapidshare.com/files/1192352226/two.and.a.half.men.4x01.working.for.caligula.ws.dvb.xvid.cz-sdtv.avi");
    //client.uploadFile(client.getNextUploadServer());
    //rapidshare.getFiles(0);

    //rapidshare.writeFolderList(8884);


}