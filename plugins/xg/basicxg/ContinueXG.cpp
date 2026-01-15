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
            w.category("Basic");
            w.label("Continue");
            w.description("Continue execution");
            w.node_type(XGNodeType::Continue);
        }
        
        xg_result_t execute(XGContext&)
        {
            return CONTINUE;
        }
    };
}

YQ_OBJECT_IMPLEMENT(ContinueXG)
