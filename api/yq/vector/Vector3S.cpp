////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector3S.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/core/StreamOps.hpp>

YQ_TYPE_IMPLEMENT(yq::Vector3S)

namespace yq {
    bool Vector3S::operator==(const Vector3S&) const = default;

    static void    print_vector3s(Stream& str, const Vector3S& v)
    {
        str << "(" << v.x << "," << v.y << "," << v.z << ")";
    }

    static void reg_vector3s()
    {
        auto w = writer<Vector3S>();
        w.description("Vector in 3D using strings");
        w.property(szX, &Vector3S::x).description(szX_Vector);
        w.property(szY, &Vector3S::y).description(szY_Vector);
        w.property(szZ, &Vector3S::z).description(szZ_Vector);
        w.print<print_vector3s>();
    }
    
    YQ_INVOKE(reg_vector3s();)
}
