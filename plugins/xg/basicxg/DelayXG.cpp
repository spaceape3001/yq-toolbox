////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    class DelayXG : public XGElement {
        YQ_OBJECT_DECLARE(DelayXG, XGElement)
    public:
        DelayXG(){}
        ~DelayXG(){}
        
        static void init_meta()
        {
            auto w = writer<DelayXG>();
            w.category("Timing");
            w.label("Delay");
            //w.icon(0, "pp:yq/icon/xg/delay.svg");
            w.description("Delay execution");
            w.symbol("yq/symbol/xgtiming.sym#delay");
        }
        
        xg_result_t execute(XGContext&)
        {
            return WAIT;
        }
    };
}

YQ_OBJECT_IMPLEMENT(DelayXG)
