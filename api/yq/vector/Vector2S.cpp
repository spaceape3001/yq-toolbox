////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector2S.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/core/StreamOps.hpp>

YQ_TYPE_IMPLEMENT(yq::Vector2S)

namespace yq {
    bool Vector2S::operator==(const Vector2S&) const = default;

    static void    print_vector2s(Stream& str, const Vector2S& v)
    {
        str << "(" << v.x << "," << v.y << ")";
    }

    static void reg_vector2s()
    {
        auto w = writer<Vector2S>();
        w.description("Vector in 2D using strings");
        w.property(szX, &Vector2S::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2S::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.print<print_vector2s>();
    }
    
    YQ_INVOKE(reg_vector2s();)
}
