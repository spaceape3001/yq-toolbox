////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/xfg/ExecNode.hpp>
#include <0/meta/ObjectInfoWriter.hpp>

namespace yq::xfg {
    template <typename C>
    class ExecNodeInfo::Writer : public ObjectInfo::Writer<C> {
    public:
        Writer(ExecNodeInfo* widgetInfo) : ObjectInfo::Writer<C>(widgetInfo), m_meta(widgetInfo)
        {
        }
        
        Writer(ExecNodeInfo& widgetInfo) : Writer(&widgetInfo)
        {
        }
    private:
        ExecNodeInfo* m_meta;
    };
    
    
    
    
}
