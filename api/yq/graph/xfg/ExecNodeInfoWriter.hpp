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
    class ExecNodeInfo::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(ExecNodeInfo* widgetInfo) : ObjectMeta::Writer<C>(widgetInfo), m_meta(widgetInfo)
        {
        }
        
        Writer(ExecNodeInfo& widgetInfo) : Writer(&widgetInfo)
        {
        }
    private:
        ExecNodeInfo* m_meta;
    };
    
    
    
    
}
