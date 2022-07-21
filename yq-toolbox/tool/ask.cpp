////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
//  (c) Copyright 2020, licenced under GPL-v3.
//
//
//  Simple utility for asking a target for its data, printing it out to standard
//  output.
//
////////////////////////////////////////////////////////////////////////////////

#include <curl/curl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

size_t  curl_write(char* ptr, size_t size, size_t nmbem, void*)
{
    size_t  N   = size * nmbem;
    (void) !write(1, ptr, N);
    return N;
}


int main(int argc, char*argv[])
{
    if(argc<2){
        cout << "Usage: ask (url)\n";
        return 0;
    }
    
    CURL* c = curl_easy_init();
    if(!c){
        cerr << "Unable to initialize curl\n";
        return -1;
    }
    
    curl_easy_setopt(c, CURLOPT_URL, argv[1]);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, curl_write);
    auto cc = curl_easy_perform(c);
    
    if(cc){
        cerr << "Curl error " << cc << "-> " << curl_easy_strerror(cc) << "\n";
    }
    
    cout << '\n';
    
    curl_easy_cleanup(c);
    return 0;
}

