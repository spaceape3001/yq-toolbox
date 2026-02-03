////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>

namespace yq {
    class GNode;

    class GPort : public GBase {
    public:
        
        bool    is_input() const;
        bool    is_output() const;
        
        GNode   node() const;
        
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
