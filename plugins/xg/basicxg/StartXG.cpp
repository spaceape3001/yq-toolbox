////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGElementMetaWriter.hpp>

using namespace yq;

namespace {
    class StartXG : public XGElement {
        YQ_OBJECT_DECLARE(StartXG, XGElement)
    public:
        StartXG(){}
        ~StartXG(){}
        
        static void init_meta()
        {
            auto w = writer<StartXG>();
            w.category("Basic");
            w.label("Start");
            w.description("Start execution");
            w.start();
        }
        
        xg_result_t execute(XGContext&)
        {
            return {};
        }
    };
}

YQ_OBJECT_IMPLEMENT(StartXG)
