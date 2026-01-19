////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Result.hpp>
#include <yq/graph/GNodeObject.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq {
    template <typename C>
    class GNodeObjectMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(GNodeObjectMeta* metaPtr) : ObjectMeta::Writer<C>(metaPtr), m_meta(metaPtr)
        {
        }
        
        Writer(GNodeObjectMeta& metaRef) : Writer(&metaRef)
        {
        }
        
        void    color(dark_k, const color_spec& v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_colorDark  = v;
            }
        }

        void    color(light_k, const color_spec& v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_colorLight  = v;
            }
        }
        
        void    symbol(const Url& v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_symbol  = v;
            }
        }
        
        //  TODO pins

        void    symbol(std::string_view v)
        {
            if(m_meta && Meta::thread_safe_write()){
                auto ux = to_url_view(v);
                if(ux.good){
                    m_meta -> m_symbol  = copy(ux.value);
                }
            }
        }

    private:
        GNodeObjectMeta*  m_meta;
    };
}
