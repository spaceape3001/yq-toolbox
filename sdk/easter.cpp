////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
//  Simple utilitiy for printing out easter dates
//
////////////////////////////////////////////////////////////////////////////////

#include <0/gis/Date.hpp>
#include <iostream>
#include <cstdlib>

using namespace yq;

int main(int argc, char* argv[])
{
    if(argc <= 1){
        std::cout << "Usage: easter [year1] ... [yearN]\n";
        return 0;
    }
    
    for(int i=1;i<argc;++i){
        int n   = atoi(argv[i]);
        if(!n)
            continue;
        std::cout << easter(n) << '\n';
    }
    
    return 0;
}
