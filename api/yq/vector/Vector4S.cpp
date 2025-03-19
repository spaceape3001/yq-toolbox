////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector4S.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/core/StreamOps.hpp>

YQ_TYPE_IMPLEMENT(yq::Vector4S)

namespace yq {
    bool Vector4S::operator==(const Vector4S&) const = default;

    static void    print_vector4s(Stream& str, const Vector4S& v)
    {
        str << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    }

    static void reg_vector4s()
    {
        auto w = writer<Vector4S>();
        w.description("Vector in 4D using strings");
        w.property(szX, &Vector4S::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector4S::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector4S::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szW, &Vector4S::w).description(szW_Vector).tag(kTag_Save).tag(kTag_Print);
        w.print<print_vector4s>();
    }
    
    YQ_INVOKE(reg_vector4s();)
}
