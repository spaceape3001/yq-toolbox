////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector3.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor34.hpp>
#include <yq/vector/Bivector3.hpp>
#include <yq/vector/Multivector3.hpp>
#include <yq/vector/Quaternion3.hpp>
#include <yq/vector/Trivector3.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <yq/core/Logging.hpp>

#include "Vector3.hxx"
#include "Multivector3.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector3D)
YQ_TYPE_IMPLEMENT(yq::Vector3F)
YQ_TYPE_IMPLEMENT(yq::Vector3I)
YQ_TYPE_IMPLEMENT(yq::Vector3U)

namespace yq {
    Vector3I    iround(const Vector3D&v)
    {
        return { iround(v.x), iround(v.y), iround(v.z) };
    }
}

using namespace yq;

template <typename T>
Vector3<T>    construct_vector3(T x, T y, T z)
{
    return Vector3<T>(x,y,z);
}

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
        w.property(szX, &Vector3D::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector3D::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector3D::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector3D>();
        w.operate_with<Multivector3D>();
        w.operate_with<Quaternion3D>();
        w.operate_with<Trivector3D>();
        w.operate_with<Tensor31D>(Operator::Multiply);
        w.operate_with<Tensor32D>(Operator::Multiply);
        w.operate_with<Tensor33D>(Operator::Multiply);
        w.operate_with<Tensor34D>(Operator::Multiply);
        w.format<math_io::format<Vector3D>>();
        w.parse<math_io::parse<Vector3D>>();
        w.print<math_io::print<Vector3D>>();
        w.constructor(construct_vector3<double>);
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
        w.property(szX, &Vector3F::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector3F::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector3F::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector3F>();
        w.operate_with<Multivector3F>();
        w.operate_with<Quaternion3F>();
        w.operate_with<Trivector3F>();
        w.operate_with<Tensor31F>(Operator::Multiply);
        w.operate_with<Tensor32F>(Operator::Multiply);
        w.operate_with<Tensor33F>(Operator::Multiply);
        w.operate_with<Tensor34F>(Operator::Multiply);
        w.format<math_io::format<Vector3F>>();
        w.parse<math_io::parse<Vector3F>>();
        w.print<math_io::print<Vector3F>>();
        w.constructor(construct_vector3<float>);
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector3F>();
    }

    {
        auto w = writer<Vector3I>();
        w.description("3D vector in integer");
        w.property(szLength², &Vector3I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3I::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector3I::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector3I::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.format<math_io::format<Vector3I>>();
        w.parse<math_io::parse<Vector3I>>();
        w.print<math_io::print<Vector3I>>();
        w.constructor(construct_vector3<int>);
    }

    {
        auto w = writer<Vector3U>();
        w.description("3D vector in unsigned integer");
        w.property(szLength², &Vector3U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3U::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector3U::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector3U::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.format<math_io::format<Vector3U>>();
        w.parse<math_io::parse<Vector3U>>();
        w.print<math_io::print<Vector3U>>();
        w.constructor(construct_vector3<unsigned>);
    }
}

namespace {
    YQ_INVOKE(reg_vector3();)
}
