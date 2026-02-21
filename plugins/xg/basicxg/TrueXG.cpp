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
    class TrueXG : public XGElement {
        YQ_OBJECT_DECLARE(TrueXG, XGElement)
    public:
        TrueXG(){}
        ~TrueXG(){}
        
        static void init_meta()
        {
            auto w = writer<TrueXG>();
            w.category("1..2..3 Debug");
            w.label("TRUE");
            w.description("Always true trigger");
            w.icon(0, "yq/icon/xg/true.svg");
            //w.node_type(XGNodeType::True);
            w.symbol("yq/symbol/xgflow.sym#logic");
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};
        }
    };
}

YQ_OBJECT_IMPLEMENT(TrueXG)
