////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Quaternion3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

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
        w.property(szW, &Quaternion3D::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3D::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3D::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3D::z).description(szZ_Quaternion);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector3D>();
        w.print<print_quaternion3<double>>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Quaternion3D>();
    }

    {
        auto w = writer<Quaternion3F>();
        w.description("3D Quaternion in float");
        w.property(szW, &Quaternion3F::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3F::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3F::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3F::z).description(szZ_Quaternion);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector3F>();
        w.print<print_quaternion3<float>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Quaternion3F>();
    }

}

YQ_INVOKE(reg_quaternion3();)
