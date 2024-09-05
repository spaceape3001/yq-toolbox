////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Bivector3.hpp>
#include <yq-toolbox/vector/Multivector3.hpp>
#include <yq-toolbox/vector/Trivector3.hpp>

#include "Vector3.hxx"
#include "Multivector3.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector3D)
YQ_TYPE_IMPLEMENT(yq::Vector3F)
YQ_TYPE_IMPLEMENT(yq::Vector3I)
YQ_TYPE_IMPLEMENT(yq::Vector3U)

using namespace yq;

template <typename T>
void    print_vector3(Stream& str, const Vector3<T>& v)
{
    str << "(" << v.x << "," << v.y << "," << v.z << ")";
}

static void reg_vector3()
{
    {
        auto w = writer<Vector3D>();
        w.description("3D vector in double");
        w.property(szLength², &Vector3D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3D::x).description(szX_Vector);
        w.property(szY, &Vector3D::y).description(szY_Vector);
        w.property(szZ, &Vector3D::z).description(szZ_Vector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector3D>();
        w.operate_with<Multivector3D>();
        w.operate_with<Trivector3D>();
        w.print<print_vector3<double>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Vector3D>();
    }

    {
        auto w = writer<Vector3F>();
        w.description("3D vector in float");
        w.property(szLength², &Vector3F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3F::x).description(szX_Vector);
        w.property(szY, &Vector3F::y).description(szY_Vector);
        w.property(szZ, &Vector3F::z).description(szZ_Vector);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector3F>();
        w.operate_with<Multivector3F>();
        w.operate_with<Trivector3F>();
        w.print<print_vector3<float>>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector3F>();
    }

    {
        auto w = writer<Vector3I>();
        w.description("3D vector in integer");
        w.property(szLength², &Vector3I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3I::x).description(szX_Vector);
        w.property(szY, &Vector3I::y).description(szY_Vector);
        w.property(szZ, &Vector3I::z).description(szZ_Vector);
        w.print<print_vector3<int>>();
    }

    {
        auto w = writer<Vector3U>();
        w.description("3D vector in unsigned integer");
        w.property(szLength², &Vector3U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3U::x).description(szX_Vector);
        w.property(szY, &Vector3U::y).description(szY_Vector);
        w.property(szZ, &Vector3U::z).description(szZ_Vector);
        w.print<print_vector3<unsigned>>();
    }
}

namespace {
    YQ_INVOKE(reg_vector3();)
}
