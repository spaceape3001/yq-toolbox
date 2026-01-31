////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    class ContinueXG : public XGElement {
        YQ_OBJECT_DECLARE(ContinueXG, XGElement)
    public:
        ContinueXG(){}
        ~ContinueXG(){}
        
        static void init_meta()
        {
            auto w = writer<ContinueXG>();
            w.category("1..2..3");
            w.label("Continue");
            w.description("Continue execution");
            w.node_type(XGNodeType::Continue);
            w.icon(0, "yq/icon/xg/done.svg");
            w.symbol("yq/symbol/xgflow.sym#done");
        }
        
        xg_result_t execute(XGContext&)
        {
            return CONTINUE;
        }
    };
}

YQ_OBJECT_IMPLEMENT(ContinueXG)
