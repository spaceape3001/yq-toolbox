////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/xfg/ExecNode.hpp>
#include <0/meta/ObjectMetaWriter.hpp>

namespace yq::xfg {
    template <typename C>
    class ExecNodeMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(ExecNodeMeta* widgetInfo) : ObjectMeta::Writer<C>(widgetInfo), m_meta(widgetInfo)
        {
        }
        
        Writer(ExecNodeMeta& widgetInfo) : Writer(&widgetInfo)
        {
        }
    private:
        ExecNodeMeta* m_meta;
    };
    
    
    
    
}
