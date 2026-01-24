////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GNodeObjectMetaWriter.hpp>
#include <yq/xg/XGElement.hpp>

namespace yq {
    template <typename C>
    class XGElementMeta::Writer : public GNodeObjectMeta::Writer<C> {
    public:
        Writer(XGElementMeta* metaPtr) : GNodeObjectMeta::Writer<C>(metaPtr), m_meta(metaPtr)
        {
        }
        
        Writer(XGElementMeta& metaRef) : Writer(&metaRef)
        {
        }
        
        //void    bgcolor(const color_t&v)
        //{
            //if(m_meta && Meta::thread_safe_write()){
                //m_meta -> m_bgcolor  = rgba4f(v);
            //}
        //}
        
        //void    color(const color_t&v)
        //{
            //if(m_meta && Meta::thread_safe_write()){
                //m_meta -> m_color  = rgba4f(v);
            //}
        //}

        void    priority(float v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_priority  = v;
            }
        }

        void    node_type(XGNodeType v)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_nodeType = v;
            }
        }
        
        //void    symbol(std::string_view v)
        //{
            //if(m_meta && Meta::thread_safe_write()){
                //m_meta -> m_symbol  = v;
            //}
        //}

    private:
        XGElementMeta*  m_meta;
    };
}
