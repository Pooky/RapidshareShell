#include "include/curlClient.h"

const string cookie = "C6D34293D0E6A0A551A4CDE4850BF5C697FD6BC4C75101A61D0B5DA3E847E83B2DCCFA7390B04C148A3D85B6B30E0A66";
const string api = "https://api.rapidshare.com/cgi-bin/rsapi.cgi";

CURL *curl;
FILE *fp;
string buffer;

struct curl_httppost* post = NULL;
struct curl_httppost* last = NULL;

// deklarace funkce
//int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);

/**
 * Inicilizace curl a základní nastavení na POST
 */
curlClient::curlClient()
{
    curl = curl_easy_init();
	upload = false;
    setupCurl();
    
	//curl_easy_setopt(curl, CURLOPT_POST, 1);
    //curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 64000);

    // nastavení progress funkce
    /*curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 64000);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);*/


}
string curlClient::getCookie(){
	
	return cookie;
	
}
void curlClient::setupCurl(){

    // nastavení api
    curl_easy_setopt(curl, CURLOPT_URL, api.c_str());
    // nastavení bufferu
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlClient::writer);
    // SSL nastavení
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

    url = api;

}
/**
 * Přidání souboru k POST, nutnost odeslat vše přes tento formulář
 * @param string fileName Název souboru.
 */
void curlClient::setFile(string fileName, string folderId)
{
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "filecontent", CURLFORM_FILE, fileName.c_str(), CURLFORM_END);
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "sub", CURLFORM_COPYCONTENTS, "upload", CURLFORM_END);
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "cookie", CURLFORM_COPYCONTENTS, cookie.c_str(), CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "folder", CURLFORM_COPYCONTENTS, folderId.c_str(), CURLFORM_END);
}
void curlClient::allowProgressBar(bool param)
{
    if(param)
    {
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);

    }
    else
    {



    }
}
/**
 * Vložení parametru do POST
 * @param name string Jméno atributu.
 * @param param string Obsah parametru.
 */
void curlClient::addParam(string name, string param)
{
    params += name + "=" + param + "&";
}
void curlClient::setDownloadLocation(string location)
{
    fp = fopen(location.c_str(),"wb");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

}
/**
 * Vložení nové url pro curl.
 * @param newUrl string Nová url.
 */
void curlClient::setUrl(string newUrl)
{
    url = newUrl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
}
/**
 * Spuštění curl dotazu a zístkání výsledku.
 * @return string Vrací buffer s odpovědí stránky.
 * TODO: Nejak dokoncit parametry pro curl form.
 */
string curlClient::getResult()
{
    CURLcode res;
    string result;

    // nastaveni cookies
    curlClient::addParam("cookie", cookie);
    // přidání souboru
    if(post != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
		
    }
    else
    {
        // přidání parametrů
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
    }

    res = curl_easy_perform(curl);
    if(res)
    {
        printf("curl_easy_perform failed: %d\n", res);
    }

    // vycisteni vysledku


    result = buffer;

    resetCurl();
    setupCurl();

    return result;
}

void curlClient::resetCurl()
{
    params.clear();
    buffer.clear();
    url.clear();
	
	// http post
	post = NULL;
	last = NULL;
	
    // reset
    curl_easy_reset(curl);
}
string curlClient::getParams()
{
    return params;
}
string curlClient::getApi()
{
    return api;
}
string curlClient::getUrl()
{
    //cout << "url::" << url << endl;
    return url;
}
curlClient::~curlClient()
{
    curl_easy_cleanup(curl);
}
/**
 * Progress bar
 */
int curlClient::progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
{
    static time_t currentTime, oldTime;
    static double old;
    static double speed = 0;
    bool download = false,upload = false;

    int seconds;

    if(TotalToDownload > 2050)
    {
        download = true;
    }
    else
    {
        upload = true;
    }

    if(oldTime == 0)
    {
        oldTime = time (&oldTime);
    }
    else
    {
        // aktuální čas
        time(&currentTime);
        seconds = currentTime - oldTime;
        // budeme meřit po 5s
        if(seconds > 1)
        {
            oldTime = time(&oldTime);
            if(download)
            {
                speed = ((NowDownloaded - old)/seconds)/1024;
                old = NowDownloaded;
            }
            else
            {
                speed = ((NowUploaded - old)/seconds)/1024;
                old = NowUploaded;
            }
            //printf(" seconds ---- %i", seconds);
            //printf("old = %f | new = %f - speed %f", oldUploaded, NowUploaded, speed);
            //oldUploaded = NowUploaded;
        }

    }

    // délka progress baru
    int totaldotz=40;

    double fraction;
    //double fraction = NowDownloaded / TotalToDownload;
    if(upload)
    {
        fraction = NowUploaded / TotalToUpload;
    }
    else
    {
        fraction = NowDownloaded / TotalToDownload;
    }



    //printf("---- %f", TotalToDownload);
    //fraction = NowUploaded / TotalToUpload;


    // kolik už je zaplněno
    int dotz = round(fraction * totaldotz);

    // create the "meter"
    int ii=0;
    printf("%3.0f%% [",fraction*100);
    // part  that's full already
    for ( ; ii < dotz; ii++)
    {
        printf("=");
    }
    // remaining part (spaces)
    for ( ; ii < totaldotz; ii++)
    {
        printf(" ");
    }

    //printf("\r --- %i --- \r",a );
    // and back to line begin - do not forget the fflush to avoid output buffering problems!
    printf("] - %.2f Kb/s \r", speed);
    fflush(stdout);
    return 0;
}

int curlClient::writer(char *data, size_t size, size_t nmemb,string *buffer)
{
    int result = 0;
    if (buffer != NULL)
    {
        buffer->append(data, size * nmemb);
        // How much did we write?
        result = size * nmemb;
    }
    return result;
}

size_t curlClient::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
