////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Symbol.hpp"
#include <yq/b3fmt/logging.hpp>
#include <yq/math/utility.hpp>
#include <yq/resource/ResourceMetaWriter.hpp>
#include <yq/symbol/Pin.hpp>
#include <yq/symbol/Shape.hpp>
#include <yq/container/vector_utils.hpp>
#include <yq/vector/Vector2.hxx>

YQ_RESOURCE_IMPLEMENT(yq::Symbol)

namespace yq {
    Symbol::Symbol() = default;
    Symbol::~Symbol() = default;
    size_t Symbol::data_size() const { return 0; }
    void Symbol::init_meta()
    {
        auto w = writer<Symbol>();
        w.description("User Symbol (ie Glyph, etc)");
    }
    
    void Symbol::normalize()
    {
        AxBox2F     bounds = NAN;
        for(auto& sh : shape){
            AxBox2F     bb  = bounds_for(sh.primitive);
            if(is_nan(bb))
                continue;
            if(is_nan(bounds)){
                bounds  = bb;
            } else {
                bounds  |= bb;
            }
        }
        
        if(is_nan(bounds))  // done
            return ;

        Vector2F    ctr = bounds.center();
        Vector2F    spa = bounds.span();
        Vector2F    sca = ONE;

        if(spa.x >= 0.01)
            sca.x   = 2. / spa.x;
        if(spa.y >= 0.01)
            sca.y   = 2. / spa.y;
        

        bool    invariant   = false;
        if(aspectLocked){
            sca = Vector2F(ALL, std::min(sca.x, sca.y));
            invariant = true;
        } else if(fabs(sca.x / sca.y - 1.) < 0.001){
            invariant   = true;
        }
        
        sca.y = -sca.y; // flip y

        auto pos    = [&](const Vector2F& v) -> Vector2F {
            return (v - ctr).emul(sca);
        };
        
        for(auto& sh : shape){
            if(const auto p = std::get_if<AxBox2F>(&sh.primitive)){
                AxBox2F bx(SORT, pos(p->lo), pos(p->hi));
                sh.primitive  = AxBox2F(SORT, pos(p->lo), pos(p->hi));
            } else if(const auto p = std::get_if<Circle2F>(&sh.primitive)){
                Vector2F    pt  = pos(p->center);
                if(invariant){
                    sh.primitive  = Circle2F(pt, p->radius*sca.x);
                } else {
                    sh.primitive  = Oval2F(pt, sca * p->radius);
                }
            } else if(const auto p = std::get_if<Oval2F>(&sh.primitive)){
                sh.primitive  = Oval2F(pos(p->center), sca.emul(p->radius));
            } else if(const auto p = std::get_if<Polygon2F>(&sh.primitive)){
                sh.primitive = Polygon2F( ::yq::transform((std::span<const Vector2F>) p->vertex, pos));
            } else if(const auto p = std::get_if<Polyline2F>(&sh.primitive)){
                sh.primitive = Polygon2F( ::yq::transform((std::span<const Vector2F>) p->vertex, pos));
            } else if(const auto p = std::get_if<Segment2F>(&sh.primitive)){
                sh.primitive  = Segment2F(pos(p->a), pos(p->b));
            } else if(const auto p = std::get_if<Triangle2F>(&sh.primitive)){
                sh.primitive  = Triangle2F(pos(p->a), pos(p->b), pos(p->c));
            } else if(const auto p = std::get_if<symbol::image_t>(&sh.primitive)){
                symbol::image_t cp      = *p;
                cp.box          = AxBox2F(SORT, pos(p->box.lo), pos(p->box.hi));
                sh.primitive    = cp;
            } else if(const auto p = std::get_if<symbol::text_t>(&sh.primitive)){
                symbol::text_t  cp  = *p;
                cp.point    = pos(p->point);
                sh.primitive    = cp;
            }
        }
    }
}
