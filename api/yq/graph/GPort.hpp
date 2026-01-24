////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>

namespace yq {
    class GPort : public GBase {
    public:
        
        GPort();
        GPort(const GPort&);
        GPort(GPort&&);
        GPort(GDocumentPtr, gid_t);
        ~GPort();
        GPort& operator=(const GPort&);
        GPort& operator=(GPort&&);
        
        operator bool() const;
        GPortData*  data();
        const GPortData*  data() const;
        
    };
}
