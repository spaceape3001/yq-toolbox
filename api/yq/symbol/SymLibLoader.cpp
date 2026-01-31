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
#include <yq/math/Cardinal.hpp>
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
        Pins&               pins;
        arg_span_t          args;
    };
    
    using FNSymCmd  = std::function<std::error_code(SymAPI&)>;
    using FNPinCmd  = std::function<std::error_code(PinAPI&)>;
    using FNPinsCmd  = std::function<std::error_code(PinsAPI&)>;

    FNSymCmd        symCmd(std::string_view);
    FNPinCmd        pinCmd(std::string_view);
    FNPinsCmd       pinsCmd(std::string_view);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::error_code _float(float& v, std::string_view txt)
    {
        auto x  = to_float(txt);
        if(!x)
            return x.error();
        v   = *x;
        return {};
    }
    
    std::error_code _vector2(Vector2F&ret, std::span<const std::string> values, float sca=1.) // sca applies to cardinals
    {
        switch(values.size()){
        case 0:
        case 1:
            return create_error<"Insufficient vector arguments">();
        case 2:
            {
                bool        ok  = false;
                Cardinal    c(values[1], &ok);
                if(!ok)
                    return create_error<"Bad cardinal value">();
                switch(c){
                case Cardinal::Center:
                    ret = { 0.f, 0.f };
                    break;
                case Cardinal::NW:
                    ret = { -sca, sca };
                    break;
                case Cardinal::NNW:
                    ret = { -0.5f*sca, sca };
                    break;
                case Cardinal::North:
                    ret = { 0.f, sca };
                    break;
                case Cardinal::NNE:
                    ret = { 0.5f*sca, sca };
                    break;
                case Cardinal::NE:
                    ret = { sca, sca };
                    break;
                case Cardinal::ENE:
                    ret = { sca, 0.5f*sca };
                    break;
                case Cardinal::East:
                    ret = { sca, 0.f };
                    break;
                case Cardinal::ESE:
                    ret = { sca, -0.5f*sca };
                    break;
                case Cardinal::SE:
                    ret = { sca, -sca };
                    break;
                case Cardinal::SSE:
                    ret = { 0.5f*sca, -sca };
                    break;
                case Cardinal::South:
                    ret = { 0.f, -sca };
                    break;
                case Cardinal::SSW:
                    ret = { -0.5f*sca, -sca };
                    break;
                case Cardinal::SW:
                    ret = { -sca, -sca };
                    break;
                case Cardinal::WSW:
                    ret = { -sca, -0.5f*sca };
                    break;
                case Cardinal::West:
                    ret = { -sca, 0 };
                    break;
                case Cardinal::WNW:
                    ret = { -sca, 0.5f*sca };
                    break;
                case Cardinal::Unknown:
                default:
                    return create_error<"Unknown cardinal value">();

                }
                return {};
            }
        case 3:
            if(auto ec = _float(ret.x, values[1]); ec != std::error_code()) 
                return ec;
            if(auto ec = _float(ret.y, values[2]); ec != std::error_code()) 
                return ec;
            return {};
        default:
            return create_error<"Too many vector arguments">();
        }
    }



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
    std::error_code _color(RGBA4F& clr, std::string_view val)
    {
        auto x = to_rgba4f(val);
        if(!x)
            return create_error<"unable to identify color">();
        clr   = *x;
        return {};
    }

    std::error_code _color(absstyle_t& sty, const line_t& line, std::span<const std::string> values={})
    {
        if(values.empty())
            values  = line.values;

        switch(values.size()){
        case 0:
        case 1:
            if(line.attrs.contains("color")){
                if(auto ec = _color(sty.color, line.attrs.get("color")); ec != std::error_code())
                    return ec;
                break;
            }
            return create_error<"insufficient color attributes">();
        case 2:
            if(is_in(values[1], { "none", "nil" })){
                sty.use = Tristate::No;
                return {};
            }
            if(is_in(values[1], { "yes", "true" })){
                sty.use = Tristate::Yes;
                return {};
            }
            if(auto ec = _color(sty.color, values[1]); ec != std::error_code())
                return ec;
            sty.use = Tristate::Yes;
            break;
        case 3:
            if(auto ec = _color(sty.color, values[1]); ec != std::error_code())
                return ec;
            if(auto ec = _float(sty.color.alpha, values[2]); ec != std::error_code())
                return ec;
            break;
        case 4:
            if(auto ec = _float(sty.color.red, values[1]); ec != std::error_code())
                return ec;
            if(auto ec = _float(sty.color.green, values[2]); ec != std::error_code())
                return ec;
            if(auto ec = _float(sty.color.blue, values[3]); ec != std::error_code())
                return ec;
            sty.color.alpha = 1.;
            break;
        case 5:
            if(auto ec = _float(sty.color.red, values[1]); ec != std::error_code())
                return ec;
            if(auto ec = _float(sty.color.green, values[2]); ec != std::error_code())
                return ec;
            if(auto ec = _float(sty.color.blue, values[3]); ec != std::error_code())
                return ec;
            if(auto ec = _float(sty.color.alpha, values[4]); ec != std::error_code())
                return ec;
            break;
        default:
            return create_error<"too many color attributes">();
        }
        
        if(line.attrs.contains("alpha")){
            if(auto ec = _float(sty.color.alpha, line.attrs.get("alpha")); ec != std::error_code())
                return ec;
        }
        
        sty.use = Tristate::Yes;
        return {};
    }
    
    std::error_code _fill(fill_style_t& sty, const line_t& line)
    {
        return _color(sty, line);
    }
    
    std::error_code _font(font_style_t& sty, const line_t& line)
    {
        switch(line.values.size()){
        case 0:
        case 1:
            break;
        case 2:
            sty.family = line.values[1];
            break;
        case 3:
        default:
            sty.family = line.values[1];
            if(auto ec = _float(sty.size, line.values[2]); ec != std::error_code())
                return ec;
            break;
        }
        
        for(auto & l : line.sublines){
            if(l.values.empty())
                continue;
            if(is_similar(l.values[0], "color")){
                if(auto ec = _color(sty, l); ec != std::error_code())
                    return ec;
            }
            if(is_similar(l.values[0], "size") && (l.values.size() > 1)){
                if(auto ec = _float(sty.size, l.values[1]); ec != std::error_code())
                    return ec;
            }
            if(is_similar(l.values[0], "bold") && (l.values.size() > 1)){
                auto x = to_boolean(l.values[1]);
                if(!x)
                    return x.error();
                sty.bold    = *x;
            }
            if(is_similar(l.values[0], "italic") && (l.values.size() > 1)){
                auto x = to_boolean(l.values[1]);
                if(!x)
                    return x.error();
                sty.italic    = *x;
            }
        }
        return {};
    }

    std::error_code _stroke(stroke_style_t& sty, const line_t& line)
    {
        if(auto ec = _color(sty, line); ec != std::error_code())
            return ec;
        if(sty.use == Tristate::No)
            return {};
        if(line.attrs.contains("width")){
            if(auto ec = _float(sty.width, line.attrs.get("width")); ec != std::error_code())
                return ec;
        }
        return {};
    }
    
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    std::error_code    _pinShape(PinShape& ret, std::string_view k)
    {
        if(is_similar(k, "none")){
            ret = PinShape::None;
        } else if(is_similar(k, "arrow")){
            ret = PinShape::Arrow;
        } else if(is_similar(k, "circle")){
            ret = PinShape::Circle;
        } else if(is_similar(k, "diamond")){
            ret = PinShape::Diamond;
        } else if(is_similar(k, "oval")){
            ret = PinShape::Oval;
        } else if(is_in(k, {"rect", "rectangle", "square"})){
            ret = PinShape::Rectangle;
        } else if(is_in(k, {"tri", "triangle"})){
            ret = PinShape::Triangle;
        } else if(is_in(k, {"+", "plus"})){
            ret = PinShape::Plus;
        } else if(is_in(k, {"-", "minus"})){
            ret = PinShape::Minus;
        } else
            return create_error<"Pin Type not recognized">();
        return {};
    }
    
    std::error_code _pinSize(Size2F&ret, std::span<const std::string> values)
    {
        return errors::todo();
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::error_code cmdPinDirection(PinAPI& api)
    {
        return _vector2(api.pin.direction, api.line.values);
    }

    std::error_code cmdPinFill(PinAPI& api)
    {
        return _fill(api.pin.style.fill, api.line);
    }

    std::error_code cmdPinPosition(PinAPI& api)
    {
        return _vector2(api.pin.position, api.line.values, 100.);
    }

    std::error_code cmdPinShape(PinAPI& api)
    {
        if(api.line.values.size() < 2)
            return create_error<"Insufficient pin type arguments">();
        return _pinShape(api.pin.shape, api.line.values[1]); 
    }

    std::error_code cmdPinSize(PinAPI& api)
    {
        return _pinSize(api.pin.size, api.line.values);
    }

    std::error_code cmdPinStroke(PinAPI& api)
    {
        return _stroke(api.pin.style.stroke, api.line);
    }

    static struct {
        const char*     zCmd;
        FNPinCmd        fn;
    } kPinCommands[] = {
        { "dir", cmdPinDirection },
        { "direction", cmdPinDirection },
        { "fill", cmdPinFill },
        { "pos", cmdPinPosition },
        { "position", cmdPinPosition },
        { "shape", cmdPinShape },
        { "size", cmdPinSize },
        { "stroke",     cmdPinStroke }
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

    std::error_code cmdPinsDirection(PinsAPI& api)
    {
        return _vector2(api.pins.direction, api.line.values);
    }

    std::error_code cmdPinsEndPos(PinsAPI& api)
    {
        return _vector2(api.pins.segment.b, api.line.values, 100.);
    }

    std::error_code cmdPinsFill(PinsAPI& api)
    {
        return _fill(api.pins.style.fill, api.line);
    }

    std::error_code cmdPinsStartPos(PinsAPI& api)
    {
        return _vector2(api.pins.segment.a, api.line.values, 100.);
    }

    std::error_code cmdPinsShape(PinsAPI& api)
    {
        if(api.line.values.size() < 2)
            return create_error<"Insufficient pin type arguments">();
        return _pinShape(api.pins.shape, api.line.values[1]); 
    }

    std::error_code cmdPinsSize(PinsAPI& api)
    {
        return _pinSize(api.pins.size, api.line.values);
    }

    std::error_code cmdPinsStroke(PinsAPI& api)
    {
        return _stroke(api.pins.style.stroke, api.line);
    }

    static struct {
        const char*     zCmd;
        FNPinsCmd       fn;
    } kPinsCommands[] = {
        { "a",          cmdPinsStartPos },
        { "b",          cmdPinsEndPos },
        { "begin",      cmdPinsStartPos },
        { "end",        cmdPinsEndPos },
        { "dir",        cmdPinsDirection },
        { "direction",  cmdPinsDirection },
        { "fill",       cmdPinsFill },
        { "from",       cmdPinsStartPos },
        { "pos",        cmdPinsStartPos },
        { "position",   cmdPinsStartPos },
        { "shape",      cmdPinsShape },
        { "size",       cmdPinsSize },
        { "start",      cmdPinsStartPos },
        { "stop",       cmdPinsEndPos },
        { "stroke",     cmdPinsStroke },
        { "to",         cmdPinsEndPos }
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
            if(is_similar(l.values[0], "key") && l.values.size() > 1)
                ret.key     = l.values[1];
            if(is_similar(l.values[0], "fill")){
                if(std::error_code ec  = _fill(ret.style.fill, l); ec != std::error_code())
                    return ec;
            }
            if(is_similar(l.values[0], "font")){
                if(std::error_code ec  = _font(ret.style.font, l); ec != std::error_code())
                    return ec;
            }
            if(is_similar(l.values[0], "stroke")){
                if( std::error_code ec  = _stroke(ret.style.stroke, l); ec != std::error_code())
                    return ec;
            }
        }
        api.sym.shape.push_back(ret);
        return {};
    }
    
    std::error_code _text(SymAPI& api, TextType tt)
    {
        text_t  ret;
        ret.type    = tt;
        if(api.line.values.size() > 1)
            ret.text    = api.line.values[1];
        for(auto& l : api.line.sublines){
            if(l.values.empty())
                continue;
            if(is_similar(l.values[0], "align")){
                for(size_t n=1;n<l.values.size();++n){
                    if(is_in(l.values[n], {"bottom"})){
                        ret.valign   = VAlign::Bottom;
                    }
                    if(is_in(l.values[n], {"center"})){
                        ret.halign   = HAlign::Center;
                    }
                    if(is_in(l.values[n], {"left"})){
                        ret.halign   = HAlign::Left;
                    }
                    if(is_in(l.values[n], {"middle"})){
                        ret.valign   = VAlign::Middle;
                    }
                    if(is_in(l.values[n], {"right"})){
                        ret.halign   = HAlign::Right;
                    }
                    if(is_in(l.values[n], {"top"})){
                        ret.valign   = VAlign::Top;
                    }
                }
            }
            if(is_in(l.values[0], { "pos", "position", "point", "pt" })){
                if(auto ec = _vector2(ret.position, l.values); ec != std::error_code())
                    return ec;
            }
        }
        return _shape(api, ret);
    }
    
    std::error_code _pin(SymAPI& api, PinFlow pf = PinFlow::Bi)
    {
        Pin     ret;
        ret.flow    = pf;
        if( api.line.values.size() > 1)
            ret.key  = api.line.values[1];
        for(auto& l : api.line.sublines){
            PinAPI  api2( api.url, l, api.sym, ret, arg_span_t( l.values.begin()+1, l.values.end() ));
            if(l.values.empty())
                return create_error<"No command on line for pin's definition">();
            FNPinCmd    fn  = pinCmd(l.values[0]);
            if(!fn){
                b3Warning << "Unrecognized command [" << to_string(api.url) << "] line " << l.line;
                return create_error<"Bad pin command">();
            }
            std::error_code ec = fn(api2);
            if(ec != std::error_code())
                return ec;
        }
        api.sym.pin.push_back(ret);
        return {};
    }
    
    std::error_code _pins(SymAPI& api, PinFlow pf = PinFlow::Bi)
    {
        Pins    ret;
        ret.flow    = pf;
        for(size_t n=1;n<api.line.values.size();++n)
            ret.keys.push_back(api.line.values[n]);
        for(auto& l : api.line.sublines){
            PinsAPI  api2( api.url, l, api.sym, ret, arg_span_t( l.values.begin()+1, l.values.end() ));
            if(l.values.empty())
                return create_error<"No command on line for pins's definition">();

            FNPinsCmd    fn  = pinsCmd(l.values[0]);
            if(!fn){
                b3Warning << "Unrecognized command [" << to_string(api.url) << "] line " << l.line;
                return create_error<"Bad pins command">();
            }
            std::error_code ec = fn(api2);
            if(ec != std::error_code())
                return ec;
        }
        api.sym.pins.push_back(ret);
        return {};
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

    std::error_code cmdSymFill(SymAPI& api)
    {
        return _fill(api.sym.style.fill, api.line);
    }

    std::error_code cmdSymFont(SymAPI& api)
    {
        return _font(api.sym.style.font, api.line);
    }

    std::error_code cmdSymInput(SymAPI& api)
    {
        return _pin(api, PinFlow::In);
    }

    std::error_code cmdSymInputs(SymAPI&api)
    {
        return _pins(api, PinFlow::In);
    }

    std::error_code cmdSymLabel(SymAPI&api)
    {
        return _text(api, TextType::Label);
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

    std::error_code cmdSymProg(SymAPI&api)
    {
        return _text(api, TextType::Prog);
    }

    std::error_code cmdSymQuadrilateral(SymAPI& api)
    {
        return _shape(api, _polygon(api.line, 4));
    }

    std::error_code cmdSymStroke(SymAPI&api)
    {
        return _stroke(api.sym.style.stroke, api.line);
    }

    std::error_code cmdSymText(SymAPI& api)
    {
        return _text(api, TextType::Text);
    }

    std::error_code cmdSymTriangle(SymAPI& api)
    {
        return _shape(api, _polygon(api.line, 3));
    }

    std::error_code cmdSymUser(SymAPI&api)
    {
        return _text(api, TextType::User);
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
        { "font", cmdSymFont },
        // image reserved
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
