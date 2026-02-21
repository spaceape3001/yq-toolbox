////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    /*! \brief An NOR node that will return TRUE if none of its connected nodes are true.
        
        \note A none with no conditionals will return TRUE
    */
    class FalseXG : public XGElement {
        YQ_OBJECT_DECLARE(FalseXG, XGElement)
    public:
        FalseXG(){}
        ~FalseXG(){}
        
        static void init_meta()
        {
            auto w = writer<FalseXG>();
            w.category("1..2..3 Debug");
            w.label("FALSE");
            w.description("Always false trigger");
            w.icon(0, "yq/icon/xg/false.svg");
            //w.node_type(XGNodeType::False);
            w.symbol("yq/symbol/xgflow.sym#logic");
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};
        }
    };
}

YQ_OBJECT_IMPLEMENT(FalseXG)
