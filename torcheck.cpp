//To find whether the IP is a tor IP or not , I have used a program where we would get information from exonerator.torproject.org where it would give us some information anout whether the IP was used as an exit node . 
// I have used curl function
// required packages to install sudo apt-get install libcurl4-openssl-dev
// to be run in the following format g++ <filename.cpp> -lcurl -o <outputfile>
//Output file ./<output file> <ip to be checked>
#include <bits/stdc++.h>
#include <curl/curl.h>
using namespace std;
struct MemoryStruct {//Our structure ,where we would be getting the contents from exonerator and storing and getting the size of the chunks recieved using CURL function
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{ size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
	FILE *fp;
    fp=fopen("tempfile","w");//The contents of the site will be put onto a file since contents from a void * to char * are not as easy as this 
    fwrite(contents,realsize,1,fp);
    fclose(fp);
  return realsize;//Size will be returned for extracting information from the same file
}

int main(int argc,char * argv[])
{
  CURL *curl_handle;
  CURLcode res;

  struct MemoryStruct chunk;

  chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  string ip(argv[1]);
  string ss="https://exonerator.torproject.org/?ip=";
  ss+=ip;

    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    timeinfo->tm_mday-=2;
    std::strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
  ss+="&timestamp=";
  string g(buffer);
  ss+=g;ss+="&lang=en";

  curl_easy_setopt(curl_handle, CURLOPT_URL, ss.c_str());

  /* send all data to this function  */
  //printf("%d",curl_handle);
 curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
 curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  //curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
  res = curl_easy_perform(curl_handle);

  /* check for errors */
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */
    FILE *fp;
    string s2="Result is negative";//If tor IP , then the Result is positive information would have been given there ,else Result is negative 
    fp=fopen("tempfile","r");//Getting info of the file
    char *data=(char*)malloc(chunk.size+1);
    fread(data,chunk.size,1,fp);
    string s1(data);
    if(s1.find(s2)!=std::string::npos){cout<<"Not a tor IP";}
      else cout<<"Yes tor IP";
    system("rm tempfile");//Deleting the temp file 


  }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  free(chunk.memory);

  /* we're done with libcurl, so clean it up */
  curl_global_cleanup();

  return 0;
}