////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    class ResumeXG : public XGElement {
        YQ_OBJECT_DECLARE(ResumeXG, XGElement)
    public:
        ResumeXG(){}
        ~ResumeXG(){}
        
        static void init_meta()
        {
            auto w = writer<ResumeXG>();
            w.category("1..2..3");
            w.label("Resume");
            w.description("Resume execution");
            w.node_type(XGNodeType::Resume);
            w.icon(0, "pp:yq/icon/xg/done.svg");
        }
        
        xg_result_t execute(XGContext&)
        {
            return RESUME;
        }
    };
}

YQ_OBJECT_IMPLEMENT(ResumeXG)
