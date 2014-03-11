#ifndef CURLCLIENT_H
#define CURLCLIENT_H

#include <string>
#include <iostream>
#include <curl/curl.h>
#include <math.h>

using namespace std;

class curlClient
{
    public:
        string params, url;

        curlClient();
        void setUrl(string url);
        void addParam(string name, string param);
        
		string getParams();
		string getCookie();
		
        void setFile(string fileName, string folderId);

        void setDownloadLocation(string fileLocation);
        void allowProgressBar(bool param = true);

        string getUrl();
        string getApi();
        string getResult();
        void setMethod(string method);
        virtual ~curlClient();
    protected:

    private:
        void resetCurl();
        void setupCurl();
		bool upload;

        static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
        static int writer(char *data, size_t size, size_t nmemb,std::string *buffer);
        static int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
};

#endif // CURLCLIENT_H
