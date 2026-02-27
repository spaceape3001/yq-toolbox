////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    /*! \brief A debugging node that will always trigger false
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
