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
#include <yq/text/basic.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/match.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/trait/has_nan.hpp>
#include <istream>

#include <yq/resource/Resource.hxx>
#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Polygon2.hxx>

using namespace yq;
using namespace yq::b3;
using namespace yq::symbol;


namespace {


    using pin_x             = Expect<Pin>;
    using pins_x            = Expect<Pins>;
    using shape_x           = Expect<Shape>;
    using primitive_x       = Expect<primitive_t>;
    
    using arg_span_t    = std::span<const std::string>;
    
    struct SymAPI {
        const Url&          url;
        const line_t&       line;
        Symbol&             sym;
        arg_span_t          args;
    };
    
    struct PinAPI {
        const Url&          url;
        const line_t&       line;
        Symbol&             sym;
        Pin&                pin;
        arg_span_t          args;
    };

    struct PinsAPI {
        const Url&          url;
        const line_t&       line;
        Symbol&             sym;
        Pins&               pin;
        arg_span_t          args;
    };
    
    using FNSymCmd  = std::function<std::error_code(SymAPI&)>;
    using FNPinCmd  = std::function<std::error_code(PinAPI&)>;
    using FNPinsCmd  = std::function<std::error_code(PinsAPI&)>;

    FNSymCmd        symCmd(std::string_view);
    FNPinCmd        pinCmd(std::string_view);
    FNPinsCmd       pinsCmd(std::string_view);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    static constexpr const float    kDefRadius  = 100.;
    
    primitive_x _box(const line_t& line)
    {
        AxBox2F     ret = NAN;
    
        switch(line.values.size()){
        case 1:
            {
                Vector2F    v{100, 100};
                ret = AxBox2F(-v, v);
            }
            break;
        case 2:
            {
                Vector2F s = parse::vector2(line.values[1]).cast<float>();
                ret = AxBox2F(SORT, -0.5f*s, 0.5f*s);
            }
            break;
        case 3:
            {
                Vector2F s = parse::vector2(line.values[1]).cast<float>();
                Vector2F c = parse::vector2(line.values[2]).cast<float>();
                ret = AxBox2F(SORT, c-0.5f*s, c+0.5f*s);
            }
            break;
        default:
            break;
        }

        if(line.attrs.contains("w"))
            ret.lo.x    = (float) parse::real(line.attrs.get("w"));
        if(line.attrs.contains("e"))
            ret.hi.x    = (float) parse::real(line.attrs.get("e"));
        if(line.attrs.contains("n"))
            ret.hi.y    = (float) parse::real(line.attrs.get("n"));
        if(line.attrs.contains("s"))
            ret.lo.y    = (float) parse::real(line.attrs.get("s"));

        if(is_nan(ret))
            return unexpected<"box needs dimensions">();
        return ret;
    }
    
    primitive_x _circle(const line_t& line)
    {
        float   r   = NaNf;
        if(line.attrs.contains("r"))
            r       = (float) parse::real(line.attrs.get("r"));
        
        switch(line.values.size()){
        case 1:
            if(is_nan(r))
                r   = kDefRadius;
            return Circle2F( ZERO, r );
        case 2:
            {
                Vector2F    pt  = parse::vector2(line.values[1]).cast<float>();
                if(is_nan(r))
                    r   = kDefRadius;
                return Circle2F( pt, r );
            }
            break;
        }
    
        return errors::todo();
    }
    
    primitive_x _line(const line_t& line)
    {
        std::vector<Vector2F>   points;
        for(size_t n=1;n<line.values.size();++n)
            points.push_back( parse::vector2(line.values[n]).cast<float>());
        switch(points.size()){
        case 0:
        case 1:
            return unexpected<"insufficient points">();
        case 2:
            return Segment2F( points[0], points[1] );
        default:
            return Polygon2F( std::move(points));
        }
    }

    primitive_x _oval(const line_t& line)
    {
        Vector2F   r   = NAN;
        if(line.attrs.contains("r"))
            r       = parse::vector2(line.attrs.get("r")).cast<float>();
        
        switch(line.values.size()){
        case 1:
            if(is_nan(r))
                r   = { kDefRadius, kDefRadius };
            return Oval2F( ZERO, r );
        case 2:
            {
                Vector2F    pt  = parse::vector2(line.values[1]).cast<float>();
                if(is_nan(r))
                    r   = { kDefRadius, kDefRadius};
                return Oval2F( pt, r );
            }
            break;
        }
    
        return errors::todo();
    }

    primitive_x _polygon(const line_t& line, unsigned N=0)  // expected size....
    {
        std::vector<Vector2F>   points;
        for(size_t n=1;n<line.values.size();++n)
            points.push_back( parse::vector2(line.values[n]).cast<float>());
        if(N){
            if(points.size() < N)
                return unexpected<"insufficient points">();
            if(points.size() > N)
                return unexpected<"too many points">();
        }
        switch(points.size()){
        case 0:
        case 1:
        case 2:
            return unexpected<"insufficient points">();
        case 3:
            return Triangle2F( points[0], points[1], points[2] );
        default:
            return Polygon2F( std::move(points) );
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    std::error_code _fill(Shape& sh, const line_t& line)
    {
        return errors::todo();
    }
    
    std::error_code _font(Shape& sh, const line_t& line)
    {
        return errors::todo();
    }

    std::error_code _stroke(Shape& sh, const line_t& line)
    {
        return errors::todo();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::error_code cmdPinDummy(PinAPI& api)
    {
        return errors::todo();
    }

    static struct {
        const char*     zCmd;
        FNPinCmd        fn;
    } kPinCommands[] = {
        { "dummy", cmdPinDummy }
    };

    FNPinCmd        pinCmd(std::string_view sv)
    {
        for(auto& k : kPinCommands){
            if(is_similar(k.zCmd, sv))
                return k.fn;
        }
        return {};
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::error_code cmdPinsDummy(PinsAPI& api)
    {
        return errors::todo();
    }

    static struct {
        const char*     zCmd;
        FNPinsCmd       fn;
    } kPinsCommands[] = {
        { "dummy", cmdPinsDummy }
    };

    FNPinsCmd        pinsCmd(std::string_view sv)
    {
        for(auto& k : kPinsCommands){
            if(is_similar(k.zCmd, sv))
                return k.fn;
        }
        return {};
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
    
        
    std::error_code _shape(SymAPI& api, const primitive_x& x)
    {
        if(!x)
            return x.error();
        Shape   ret(*x);
        for(auto& l : api.line.sublines){
            if(l.values.empty())
                continue;
            if(is_similar(l.values[0], "fill")){
                std::error_code ec  = _fill(ret, l);
                if(ec != std::error_code())
                    return ec;
            }
            if(is_similar(l.values[0], "font")){
                std::error_code ec  = _font(ret, l);
                if(ec != std::error_code())
                    return ec;
            }
            if(is_similar(l.values[0], "stroke")){
                std::error_code ec  = _stroke(ret, l);
                if(ec != std::error_code())
                    return ec;
            }
        }
        api.sym.shape.push_back(ret);
        return {};
    }
    
    std::error_code _pin(SymAPI& api, PinFlow pf = PinFlow::Bi)
    {
        return errors::todo();
    }
    
    std::error_code _pins(SymAPI& api, PinFlow pf = PinFlow::Bi)
    {
        return errors::todo();
    }
    
    std::error_code cmdSymBox(SymAPI& api)
    {
        return _shape(api, _box(api.line));
    }

    std::error_code cmdSymCircle(SymAPI&api)
    {
        return _shape(api, _circle(api.line));
    }

    std::error_code cmdSymDead(SymAPI& api)
    {
        return _pin(api, PinFlow::NC);
    }

    std::error_code cmdSymFill(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymInput(SymAPI& api)
    {
        return _pin(api, PinFlow::In);
    }

    std::error_code cmdSymInputs(SymAPI&api)
    {
        return _pins(api, PinFlow::In);
    }

    std::error_code cmdSymLabel(SymAPI&)
    {
        return errors::todo();
    }
    
    std::error_code cmdSymLine(SymAPI& api)
    {
        return _shape(api, _line(api.line));
    }

    std::error_code cmdSymOutput(SymAPI& api)
    {
        return _pin(api, PinFlow::Out);
    }

    std::error_code cmdSymOutputs(SymAPI& api)
    {
        return _pins(api, PinFlow::Out);
    }
    
    std::error_code cmdSymOval(SymAPI& api)
    {
        return _shape(api, _oval(api.line));
    }

    std::error_code cmdSymPin(SymAPI& api)
    {
        return _pin(api);
    }

    std::error_code cmdSymPins(SymAPI& api)
    {
        return _pins(api);
    }

    std::error_code cmdSymPolygon(SymAPI& api)
    {
        return _shape(api, _polygon(api.line));
    }

    std::error_code cmdSymProg(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymQuadrilateral(SymAPI& api)
    {
        return _shape(api, _polygon(api.line, 4));
    }

    std::error_code cmdSymStroke(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymText(SymAPI&)
    {
        return errors::todo();
    }

    std::error_code cmdSymTriangle(SymAPI& api)
    {
        return _shape(api, _polygon(api.line, 3));
    }

    std::error_code cmdSymUser(SymAPI&)
    {
        return errors::todo();
    }
    
    static struct {
        const char*     zCmd;
        FNSymCmd        fn;
    } kSymCommands[] = {
        { "allow", cmdSymAllow },
        { "aab", cmdSymBox },
        // arc reserved
        { "box", cmdSymBox },
        { "circle", cmdSymCircle },
        { "dead", cmdSymDead },
        { "edit", cmdSymUser },
        { "fill", cmdSymFill },
        { "in", cmdSymInput },
        { "input", cmdSymInput },
        { "inputs", cmdSymInputs },
        { "ins", cmdSymInputs },
        { "label", cmdSymLabel },
        { "line", cmdSymLine },
        { "nc", cmdSymDead },
        { "out", cmdSymOutput },
        { "output", cmdSymOutput },
        { "outputs", cmdSymOutputs },
        { "outs", cmdSymOutputs },
        { "oval", cmdSymOval },
        { "pin", cmdSymPin },
        { "pins", cmdSymPins },
        { "pgon", cmdSymPolygon },
        { "polygon", cmdSymPolygon },
        { "prog", cmdSymProg },
        { "quad", cmdSymQuadrilateral },
        { "quadrilateral", cmdSymQuadrilateral },
        { "rect", cmdSymBox },
        { "rectangle", cmdSymBox },
        { "stroke", cmdSymStroke },
        { "text", cmdSymText },
        { "tri", cmdSymTriangle },
        { "triangle", cmdSymTriangle },
        { "user", cmdSymUser },
        // wedge .. reserved
    };

    FNSymCmd        symCmd(std::string_view sv)
    {
        for(auto& k : kSymCommands){
            if(is_similar(k.zCmd,sv))
                return k.fn;
        }
        return {};
    }
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    symbol_ptr_x            _loadSym(const line_t& line, const Url& url)
    {
        SymbolPtr   sym = new Symbol;
        sym->set_key(line.values[0]);
        if(line.values.size() > 1)
            sym->set_name(line.values[1]);
            
        for(auto& l : line.sublines){
            if(l.values.empty())
                continue;

            FNSymCmd    cmd = symCmd(l.values[0]);
            if(!cmd){
                b3Warning << "Unrecognized command [" << to_string(url) << "] line " << l.line;
                return unexpected<"Unrecognized symbol command">();
            }
            
            SymAPI  api{ url, l, *sym, arg_span_t( l.values.begin()+1, l.values.end() )};
            std::error_code ec = cmd(api);
            if(ec != std::error_code()){
                b3Warning << "Unable to parse [" << to_string(url) << "], line " << l.line << ": " << ec.message();
                return unexpected(ec);
            }
        }
        sym -> normalize();
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
