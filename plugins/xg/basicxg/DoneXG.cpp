////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;
using namespace yq::xg;

namespace {
    class DoneXG : public XGElement {
        YQ_OBJECT_DECLARE(DoneXG, XGElement)
    public:
        DoneXG(){}
        ~DoneXG(){}
        
        static void init_meta()
        {
            auto w = writer<DoneXG>();
            w.category("Basic");
            w.label("Done");
            w.description("Done execution");
        }
        
        result_t execute(XGContext&)
        {
            return DONE;
        }
    };
}

YQ_OBJECT_IMPLEMENT(DoneXG)
