////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/core/Enum.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/vector/Vector2.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq {
    class XGDocument : public GDocument {
        YQ_RESOURCE_DECLARE(XGDocument, GDocument)
    public:
        XGDocument();
        XGDocument(new_k);
        ~XGDocument();

        virtual size_t                  data_size() const override;

        static void init_meta();
        
    private:
        XGDocument(const XGDocument&) = delete;
        XGDocument(XGDocument&&) = delete;
        XGDocument& operator=(const XGDocument&) = delete;
        XGDocument& operator=(XGDocument&&) = delete;
    };
}


