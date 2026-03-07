////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    class PassXG : public XGElement {
        YQ_OBJECT_DECLARE(PassXG, XGElement)
    public:
        PassXG(){}
        ~PassXG(){}
        
        static void init_meta()
        {
            auto w = writer<PassXG>();
            w.category("1..2..3");
            w.label("Pass");
            w.icon(0, "pp:yq/icon/xg/done.svg");
            w.description("Pass through execution (useful for merging execution paths)");
            w.symbol("yq/symbol/xgbasic.sym#pass");
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};  // does nothing except continue on (useful for merging execution paths)
        }
    };
}

YQ_OBJECT_IMPLEMENT(PassXG)
