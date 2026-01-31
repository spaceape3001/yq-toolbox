////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Symbol.hpp"

#include <yq/errors.hpp>
#include <yq/b3fmt/logging.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/symbol/Pin.hpp>
#include <yq/symbol/Shape.hpp>
#include <yq/xml/XmlUtils.hpp>
#include <rapidxml.hpp>

#include <yq/resource/Resource.hxx>
#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Circle2.hxx>
#include <yq/shape/Oval2.hxx>

//  have PNG (different file)


namespace yq {
    namespace {
        std::error_code exportSVG(XmlDocument& doc, const Symbol& sym, const SymbolSVGOptions& opts={})
        {
            using namespace yq::symbol;
            
            auto& svg           = *doc.create_element("svg");
            AxBox2F     bounds  = NAN;
            
            auto augment = [&](const AxBox2F& bx){
                if(is_nan(bounds))
                    bounds  = bx;
                else
                    bounds |= bx;
            };
            
            auto _fill  = [&](XmlNode& node, const fill_style_t& sty){
                if(sty.use == Tristate::NO){
                    write_attribute(node, "fill", "none"sv);
                    return ;
                }
            };
            
            auto fill   = [&](XmlNode& node, const symbol::Shape& sh){
                _fill(node, (sh.style.fill.use == Tristate::Inherit) ? sym.style.fill : sh.style.fill );
            };

            auto _font  = [&](XmlNode& node, const font_style_t& sty){
            };

            auto font   = [&](XmlNode& node, const symbol::Shape& sh){
                _font(node, (sh.style.font.use == Tristate::Inherit) ? sym.style.font : sh.style.font );
            };

            auto _stroke  = [&](XmlNode& node, const stroke_style_t& sty){
                if(sty.use == Tristate::NO){
                    write_attribute(node, "stroke", "none"sv);
                    return ;
                }
            };

            auto stroke   = [&](XmlNode& node, const symbol::Shape& sh){
                _stroke(node, (sh.style.stroke.use == Tristate::Inherit) ? sym.style.stroke : sh.style.stroke );
            };
            
            
            for(auto& sh : sym.shape){
                if(const auto* p = std::get_if<AxBox2F>(&sh.primitive)){
                    AxBox2F bx  = *p * opts.scale;
                
                    augment(bx);
                    auto &xml   = *svg.create_element("rect");
                    write_attribute(xml, "x", bx.lo.x);
                    write_attribute(xml, "y", bx.lo.y);
                    write_attribute(xml, "width", bx.width());
                    write_attribute(xml, "height", bx.height());
                    fill(xml, sh);
                    stroke(xml, sh);
                }
                if(const auto* p = std::get_if<Circle2F>(&sh.primitive)){
                    Circle2F    cir = *p * opts.scale;
                    
                    augment(cir.bounds());
                    auto& xml = *svg.create_element("circle");
                    write_attribute(xml, "cx", cir.center.x);
                    write_attribute(xml, "cy", cir.center.y);
                    write_attribute(xml, "r", cir.radius);
                    fill(xml, sh);
                    stroke(xml, sh);
                }
                if(const auto* p = std::get_if<Oval2F>(&sh.primitive)){
                    Oval2F    cir = *p * opts.scale;
                    
                    augment(cir.bounds());
                    auto& xml = *svg.create_element("ellipse");
                    write_attribute(xml, "cx", cir.center.x);
                    write_attribute(xml, "cy", cir.center.y);
                    write_attribute(xml, "rx", cir.radius.x);
                    write_attribute(xml, "ry", cir.radius.y);
                    fill(xml, sh);
                    stroke(xml, sh);
                }
                if(const auto* p = std::get_if<Polygon2F>(&sh.primitive)){
                }
                if(const auto* p = std::get_if<Polyline2F>(&sh.primitive)){
                }
                if(const auto* p = std::get_if<Segment2F>(&sh.primitive)){
                }
                if(const auto* p = std::get_if<Triangle2F>(&sh.primitive)){
                }
            }
            for(auto& sh : sym.pin){
            
            }
            for(auto& sh : sym.pins){
            }
            
            if(!is_nan(bounds)){
                write_attribute(svg, "width", bounds.width());
                write_attribute(svg, "height", bounds.height());
                write_attribute(svg, "viewBox", std::format("{} {} {} {}", bounds.lo.x, bounds.lo.y, bounds.width(), bounds.height()));
            }
        
            return {};
        }
    }
    
    std::error_code exportSymSVG_xml(const Symbol& sym, XmlDocument& doc, const ResourceSaveAPI& api)
    {
        SymbolSVGOptions    opts;   
        
        // TODO set options from the API
        
        return exportSVG(doc, sym);
    }
    

    std::error_code     exportSymbolToSVG(const std::filesystem::path& fp, const Symbol& sym, const SymbolSVGOptions& opts)
    {
        XmlDocument doc;
        std::error_code ec  = exportSVG(doc, sym);
        if(ec != std::error_code()) 
            return ec;
        return save_file(doc, fp);
    }
    
    static void reg_svgexport()
    {
        Symbol::IO::add_saver({.extensions={"svg"}}, exportSymSVG_xml);
    }
    
    YQ_INVOKE(reg_svgexport();)
}
