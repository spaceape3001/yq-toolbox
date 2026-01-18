////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    /*! \brief An ALWAYS node
    
        \note Always nodes should *NEVER* have inbound edges.
    */

    class AlwaysXG : public XGElement {
        YQ_OBJECT_DECLARE(AlwaysXG, XGElement)
    public:
        AlwaysXG(){}
        ~AlwaysXG(){}
        
        static void init_meta()
        {
            auto w = writer<AlwaysXG>();
            w.category("1..2..3");
            w.label("Always");
            w.description("Always execution");
            w.node_type(XGNodeType::Always);
            w.symbol("pp:yq/symbol/xgflow.sym#always");
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};
        }
    };
}

YQ_OBJECT_IMPLEMENT(AlwaysXG)
