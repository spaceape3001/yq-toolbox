////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Pin.hpp"
#include "Shape.hpp"
#include "Symbol.hpp"
#include "SymbolLibrary.hpp"
#include <yq/errors.hpp>
#include <yq/b3fmt/line.hpp>
#include <yq/b3fmt/parse.hpp>
#include <yq/b3fmt/logging.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/net/Url.hpp>
#include <yq/resource/ResourceDriverAPI.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/match.hpp>
#include <istream>

#include <yq/resource/Resource.hxx>

using namespace yq;
using namespace yq::b3;
using namespace yq::symbol;


namespace {
    using pin_x     = Expect<Pin>;
    using pins_x    = Expect<Pins>;
    
    using arg_span_t    = std::span<const std::string>;
    
    struct SymAPI {
        Symbol&             sym;
        const line_t&       line;
        std::string_view    cmd;
        arg_span_t          args;
    };
    
    Expect<fill_style_t>      _loadFill(const line_t& line, const Url& url)
    {
        return errors::todo();
    }
    
    Expect<stroke_style_t>      _loadStroke(const line_t& line, const Url& url)
    {
        return errors::todo();
    }

    pin_x                   _loadPin(const line_t& line, const Url& url, PinFlow pf=PinFlow::Bi)
    {
        return errors::todo();
    }

    pins_x                   _loadPins(const line_t& line, const Url& url, PinFlow pf=PinFlow::Bi)
    {
        return errors::todo();
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    std::error_code cmdSymAllow(SymAPI&api)
    {
        for(auto sv : api.args){
            if(is_similar(sv, "ar")){
                api.sym.aspectLocked = false;
            } else if(is_similar(sv, "rot")){
                api.sym.transforms |= TransformType::Rotation;
            } else if(is_similar(sv, "x")){
                api.sym.transforms |= TransformType::HorizontalFlip;
            } else if(is_similar(sv, "xy")){
                api.sym.transforms |= TransformType::XYSwitch;
            } else if(is_similar(sv, "y")){
                api.sym.transforms |= TransformType::VerticalFlip;
            } else
                return create_error<"Sym: Unrecognized 'allow' flag">();
        }
        return {};
    }
    
    std::error_code cmdSymBox(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymCircle(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymDead(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymFill(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymInput(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymInputs(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymLabel(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymOutput(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymOutputs(SymAPI&)
    {
        return errors::todo();
    }
    
    std::error_code cmdSymOval(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymPin(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymPins(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymStroke(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymText(SymAPI&)
    {
        return errors::todo();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    using FNSymCmd  = std::function<std::error_code(SymAPI&)>;
    
    static struct {
        const char*     zCmd;
        FNSymCmd        fn;
    } kSymCommands[] = {
        { "allow", cmdSymAllow },
        { "aab", cmdSymBox },
        // arc reserved
        { "box", cmdSymBox },
        { "dead", cmdSymDead },
        { "fill", cmdSymFill },
        { "in", cmdSymInput },
        { "input", cmdSymInput },
        { "inputs", cmdSymInputs },
        { "ins", cmdSymInputs },
        { "nc", cmdSymDead },
        { "out", cmdSymOutput },
        { "output", cmdSymOutput },
        { "outputs", cmdSymOutputs },
        { "outs", cmdSymOutputs },
        { "pin", cmdSymOutput },
        { "pins", cmdSymOutputs },
        { "rect", cmdSymBox },
        { "rectangle", cmdSymBox },
        { "stroke", cmdSymStroke }
        // wedge .. reserved
    };


    symbol_ptr_x            _loadSym(const line_t& line, const Url& url)
    {
        SymbolPtr   sym = new Symbol;
        sym->set_key(line.values[0]);
        if(line.values.size() > 1)
            sym->set_name(line.values[1]);
            
        for(auto& l : line.sublines){
            if(l.values.empty())
                continue;
            SymAPI api{ *sym, l, l.values[0], arg_span_t(l.values.begin()+1, l.values.end()) };
            for(const auto& k : kSymCommands){
                if(is_similar(api.cmd, k.zCmd) && k.fn){
                    std::error_code ec = k.fn(api);
                    if(ec != std::error_code()){
                        b3Warning << "Unable to parse [" << to_string(url) << "], line " << l.line << ": " << ec.message();
                        return unexpected(ec);
                    }
                }
            }
        }
        return sym;
    }

    symbol_library_ptr_x    _load(const file_t& file, const Url& url)
    {
        SymbolLibraryPtr    ret = new SymbolLibrary;
        ret -> set_url(url);
        for(auto& l : file.lines){
            if(l.values.empty())
                continue;
            auto sx = _loadSym(l, url);
            if(!sx)
                return unexpected(sx.error());
            ret -> add( *sx );
            
        }
        return ret;
    }
    
    SymbolLibraryPtr    loadSymLibrary_Stream(std::istream& p, const ResourceLoadAPI&api)
    {
        auto fx = loadB3(p);
        if(!fx){
            b3Error << "Unable to load (" << to_string(api.url()) << "): " << fx.error().message();
            return {};
        }
        auto rx =  _load(*fx, api.url());
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
        return _load(*fx, to_url(p));
    }
}
