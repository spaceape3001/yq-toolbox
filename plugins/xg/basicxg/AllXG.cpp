////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    /*! \brief An All node (Logical AND)
    
        Returns TRUE if ALL connected nodes are true
    */

    class AllXG : public XGElement {
        YQ_OBJECT_DECLARE(AllXG, XGElement)
    public:
        AllXG(){}
        ~AllXG(){}
        
        static void init_meta()
        {
            auto w = writer<AllXG>();
            w.category("1..2..3");
            w.label("ALL");
            w.description("All conditional");
            w.icon(0, "yq/icon/xg/logic.svg");
            w.node_type(XGNodeType::Logic);
            w.symbol("yq/symbol/xgflow.sym#conditional");
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};
        }
    };
}

YQ_OBJECT_IMPLEMENT(AllXG)
