////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    /*! \brief An Any (OR) node
    
        This will return TRUE if any node returns true.
    */

    class AnyXG : public XGElement {
        YQ_OBJECT_DECLARE(AnyXG, XGElement)
    public:
        AnyXG(){}
        ~AnyXG(){}
        
        static void init_meta()
        {
            auto w = writer<AnyXG>();
            w.category("1..2..3");
            w.label("ANY");
            w.description("Any/Or execution");
            w.icon(0, "yq/icon/xg/logic.svg");
            //w.node_type(XGNodeType::Any);
            w.symbol("yq/symbol/xgflow.sym#conditional");
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};
        }
    };
}

YQ_OBJECT_IMPLEMENT(AnyXG)
