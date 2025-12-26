////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/ObjectMetaWriter.hpp>
#include <yq/xg/XGElement.hpp>

namespace yq {
    template <typename C>
    class XGElementMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(XGElementMeta* metaPtr) : ObjectMeta::Writer<C>(metaPtr), m_meta(metaPtr)
        {
        }
        
        Writer(XGElementMeta& metaRef) : Writer(&metaRef)
        {
        }
        
        void    always(bool f=true)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_always  = f;
            }
        }

        void    bgcolor(const color_t&v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_bgcolor  = rgba4f(v);
            }
        }
        
        void    color(const color_t&v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_color  = rgba4f(v);
            }
        }

        void    decision(bool f=true)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_decision  = f;
            }
        }
        
        void    priority(float v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_priority  = v;
            }
        }

        void    start(bool f=true)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_start  = f;
            }
        }

    private:
        XGElementMeta*  m_meta;
    };
}
