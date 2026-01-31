////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    class DoneXG : public XGElement {
        YQ_OBJECT_DECLARE(DoneXG, XGElement)
    public:
        DoneXG(){}
        ~DoneXG(){}
        
        static void init_meta()
        {
            auto w = writer<DoneXG>();
            w.category("1..2..3");
            w.label("Done");
            w.icon(0, "pp:yq/icon/xg/done.svg");
            w.description("Done execution");
            w.node_type(XGNodeType::Done);
            w.symbol("yq/symbol/xgflow.sym#done");
        }
        
        xg_result_t execute(XGContext&)
        {
            return DONE;
        }
    };
}

YQ_OBJECT_IMPLEMENT(DoneXG)
