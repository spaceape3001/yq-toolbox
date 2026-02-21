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
    class NoneXG : public XGElement {
        YQ_OBJECT_DECLARE(NoneXG, XGElement)
    public:
        NoneXG(){}
        ~NoneXG(){}
        
        static void init_meta()
        {
            auto w = writer<NoneXG>();
            w.category("1..2..3");
            w.label("NONE");
            w.description("Not/nor execution");
            w.icon(0, "yq/icon/xg/not.svg");
            //w.node_type(XGNodeType::None);
            w.symbol("yq/symbol/xgflow.sym#conditional");
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};
        }
    };
}

YQ_OBJECT_IMPLEMENT(NoneXG)
