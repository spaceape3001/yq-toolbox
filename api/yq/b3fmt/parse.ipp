////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "parse.hpp"
#include "context.hpp"
#include <yq/container/Map.hpp>
#include <yq/container/Set.hpp>
#include <yq/math/Range.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/match.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/vsplit.hpp>

namespace yq::b3::parse {
    unit::Degree    angle(std::string_view v, unit::Degree def)
    {
        return unit::Degree{real(v, def.value)};
    }

    bool    boolean(std::string_view v, bool def)
    {
        auto x = to_boolean(v);
        if(!x)
            return def;
        return *x;
    }

    Brush           brush(std::string_view v)
    {
        return Brush{ color(v) };
    }

    Color   color(std::string_view v)
    {
        std::string k(v);
        if(const context_t* ctx = context_t::current())
            return { std::string(ctx->color(k)) };
        else
            return { std::move(k) };
    }

    CoordN              coord(std::string_view v)
    {
        CoordN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.indices.push_back(integer(s));
        });
        return ret;
    }
    
    Coord2I             coord2(std::string_view v)
    {
        return (Coord2I) coord(v);
    }
    
    Coord3I             coord3(std::string_view v)
    {
        return (Coord3I) coord(v);
    }

    CountN              count(std::string_view v)
    {
        CountN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(integer(s));
        });
        return ret;
    }

    Font            font(std::string_view v)
    {
        Font    ret;
        auto bits = split(v,',');
        if(bits.size() > 0)
            ret.family    = std::string(bits[0]);
        if(bits.size() > 1)
            ret.size = real(bits[1]);
        return ret;
    }

    int                 integer(std::string_view v, int def)
    {
        auto x =  to_integer(v);
        if(!x)
            return def;
        return *x;
    }

    IntegerSet          integer_set(std::string_view v)
    {
        IntegerSet      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.insert(integer(s));
        });
        return ret;
    }
    
    RangeI          irange(std::string_view v, const RangeI& def)
    {
        auto n  = v.find("..");
        if(n != std::string_view::npos){
            auto    a   = v.substr(0,n);
            auto    b   = v.substr(n+2);
            return { integer(a, def.lo), integer(b, def.hi) };
        } else {
            return { integer(v, def.lo), integer(v, def.hi) };
        }
    }
    

    double          length(std::string_view v, double def)
    {
        size_t n;
        for(n=v.size()-1;n>=0; --n)
            if(!is_alpha(v[n]))
                break;

        if(n < v.size()-1){
            std::string         unit(v.substr(n+1));
            std::string_view    value   = v.substr(0,n);
            
            auto x  = to_double(value);
            if(!x)
                return def;
            
            if(const context_t* ctx = context_t::current())
                return ctx -> unit(unit) * *x;
            return *x;
        } else {
            auto x  = to_double(v);
            if(!x)
                return def;
            return *x;
        }
    }
    
    Pen             pen(std::string_view v)
    {
        Pen ret;
        auto bits   = split(v, '/');
        if(bits.size() > 0)
            ret.color   = color(bits[0]);
        if(bits.size() > 1)
            ret.width   =  real(bits[1]);
        if(bits.size() > 2){
            auto style  = bits[2];
            if(is_similar(style, "solid")){
                ret.style  = PenStyle::Solid;
            } else if(is_similar(style, "dash")) {
                ret.style  = PenStyle::Dash;
            } else if(is_similar(style, "dot")) {
                ret.style  = PenStyle::Dot;
            } else if(is_similar(style, "dashdot") || is_similar(style, "dotdash")){
                ret.style  = PenStyle::DashDot;
            } 
        }
        return ret;
    }

    PointN           point(std::string_view v)
    {
        PointN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(length(s));
        });
        return ret;
    }

    Vector2D         point2(std::string_view v)
    {
        return (Vector2D) point(v);
    }
    
    Vector3D         point3(std::string_view v)
    {
        return (Vector3D) point(v);
    }

    double              real(std::string_view v, double def)
    {
        auto x = to_double(v);
        if(!x)
            return def;
        return *x;
    }
    
    SizeN               size(std::string_view v)
    {
        SizeN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(length(s));
        });
        return ret;
    }

    Size2D        size2(std::string_view v)
    {
        return (Size2D) size(v);
    }
    
    Size3D        size3(std::string_view v)
    {
        return (Size3D) size(v);
    }

    StringSet       string_set(std::string_view v)
    {
        StringSet       ret;
        vsplit(v, ',', [&](std::string_view s){
            ret.insert(std::string(trimmed(s)));
        });
        return ret;
    }
    
    VectorN         vector(std::string_view v)
    {
        VectorN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(real(s));
        });
        return ret;
    }

    Vector2D        vector2(std::string_view v)
    {
        return (Vector2D) vector(v);
    }
    
    Vector3D        vector3(std::string_view v)
    {
        return (Vector3D) vector(v);
    }

    Vector4D        vector4(std::string_view v)
    {
        return (Vector4D) vector(v);
    }
}
