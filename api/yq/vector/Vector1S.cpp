////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector1S.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/core/StreamOps.hpp>

YQ_TYPE_IMPLEMENT(yq::Vector1S)

namespace yq {
    static void    print_vector1s(Stream& str, const Vector1S& v)
    {
        str << "(" << v.x << ")";
    }

    static void reg_vector1s()
    {
        auto w = writer<Vector1S>();
        w.description("Vector in 1D using strings");
        w.property(szX, &Vector1S::x).description(szX_Vector);
        w.print<print_vector1s>();
    }
    
    YQ_INVOKE(reg_vector1s();)
}
