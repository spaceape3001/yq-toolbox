////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Quaternion3.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Quaternion3.hxx"

YQ_TYPE_IMPLEMENT(yq::Quaternion3D)
YQ_TYPE_IMPLEMENT(yq::Quaternion3F)

using namespace yq;

template <typename T>
void    print_quaternion3(Stream& str, const Quaternion3<T>& v)
{
    str << "(" << v.w << "," << v.x << "," << v.y << "," << v.z << ")";
}

static void reg_quaternion3()
{
    {
        auto w = writer<Quaternion3D>();
        w.description("3D Quaternion in double");
        w.property(szW, &Quaternion3D::w).description(szW_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Quaternion3D::x).description(szX_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Quaternion3D::y).description(szY_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Quaternion3D::z).description(szZ_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        //w.operate_with<Vector3D>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.format<math_io::format<Quaternion3D>>();
        w.parse<math_io::parse<Quaternion3D>>();
        w.print<math_io::print<Quaternion3D>>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Quaternion3D>();
    }

    {
        auto w = writer<Quaternion3F>();
        w.description("3D Quaternion in float");
        w.property(szW, &Quaternion3F::w).description(szW_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Quaternion3F::x).description(szX_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Quaternion3F::y).description(szY_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Quaternion3F::z).description(szZ_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        //w.operate_with<Vector3F>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.format<math_io::format<Quaternion3F>>();
        w.parse<math_io::parse<Quaternion3F>>();
        w.print<math_io::print<Quaternion3F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Quaternion3F>();
    }

}

YQ_INVOKE(reg_quaternion3();)
