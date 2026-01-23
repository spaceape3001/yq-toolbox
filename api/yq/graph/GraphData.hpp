////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>

namespace yq {
    struct GDocBase {
        uint32_t    id  = 0;    // set when needed, leave as zero otherwise
    };
    
    struct GGroup : public GDocBase {
    };
    
    struct GAnnotation : public GDocBase {
    };

    struct GLineAnnotation : public GAnnotation {
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

