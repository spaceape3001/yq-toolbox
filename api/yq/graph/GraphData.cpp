////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphData.cpp"

namespace yq {
    struct GDocBase {
        uint32_t    id  = 0;    // set when needed
    };
    
    struct GLineAnnotation : public GDocBase {
    };

    struct GTextAnnotation : public GDocBase {
    };

    struct GPortData : public GDocBase {
    };
    
    
    struct GNodeData : public GDocBase {
    };
    
    struct GEdgeData : public GDocBase {
    };

    struct GGraphData : public GDocBase {
    };
}
