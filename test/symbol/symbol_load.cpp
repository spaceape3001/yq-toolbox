////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/config/build.hpp>
#include <yq/core/Logging.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/symbol/Symbol.hpp>
#include <yq/symbol/SymbolLibrary.hpp>
#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main(int argc, char* argv[])
{
    log_to_std_error();
    Meta::init();
    Resource::add_paths(toolbox_data_directory());
    Meta::freeze();
    
    "basicLoad"_test = []{
        auto symlib    = SymbolLibrary::IO::load("pp:yq/symbol/basic.sym");
        expect(symlib.valid());
        if(!symlib)
            return;
    
        //  rest of it....
        auto square = Symbol::IO::load("pp:yq/symbol/basic.sym#square");
        expect(square.valid());
    
    };
    
    return ut::cfg<>.run();
}
