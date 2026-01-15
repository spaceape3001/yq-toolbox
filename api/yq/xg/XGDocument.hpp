////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/core/Enum.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/xg/XGDocDoc.hpp>
#include <yq/xg/XGDocBase.hpp>
#include <yq/xg/types.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq {
    class XGDocument : public Resource, public XGDocDoc {
        YQ_RESOURCE_DECLARE(XGDocument, Resource)
    public:
        XGDocument();
        ~XGDocument();
        XGDocument(const XGDocument&);

        virtual size_t                  data_size() const override;

        static void init_meta();
    };
}


