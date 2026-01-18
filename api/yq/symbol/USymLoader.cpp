////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Symbol.hpp"
#include "SymbolLibrary.hpp"
#include <yq/errors.hpp>
#include <yq/b3fmt/line.hpp>
#include <yq/b3fmt/parse.hpp>
#include <yq/b3fmt/logging.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/net/Url.hpp>
#include <yq/resource/ResourceDriverAPI.hpp>
#include <istream>

#include <yq/resource/Resource.hxx>

using namespace yq;
using namespace yq::b3;
using namespace yq::symbol;

namespace {
    symbol_library_ptr_x    _load(const file_t& file)
    {
        
    
        return errors::todo();
    }
    
    SymbolLibraryPtr    loadSymLibrary_Stream(std::istream& p, const ResourceLoadAPI&api)
    {
        auto fx = loadB3(p);
        if(!fx){
            b3Error << "Unable to load (" << to_string(api.url()) << "): " << fx.error().message();
            return {};
        }
        auto rx =  _load(*fx);
        if(!rx){
            b3Error << "Unable to load (" << to_string(api.url()) << "): " << rx.error().message();
            return {};
        }
        return *rx;
    }
    
    void reg_usym()
    {
        SymbolLibrary::IO::add_loader({.extensions={"sym"}}, loadSymLibrary_Stream);
    }
    
    YQ_INVOKE(reg_usym();)
}

namespace yq {
    symbol_library_ptr_x    loadSymLibrary(const std::filesystem::path& p)
    {
        auto fx = loadB3File(p);
        if(!fx){
            b3Error << "Unable to load (" << p << "): " << fx.error().message();
            return {};
        }
        return _load(*fx);
    }
}
