////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Spinor2.hpp"
#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <yq/vector/Multivector2.hpp>
#include <yq/vector/Vector2.hpp>

#include "Spinor2.hxx"

YQ_TYPE_IMPLEMENT(yq::Spinor2D)
YQ_TYPE_IMPLEMENT(yq::Spinor2F)


using namespace yq;

template <typename T>
void    print_spinor2(Stream& str, const Spinor2<T>& v)
{
    str << "(" << v.a << "," << v.xy << ")";
}

static void reg_spinor2()
{
    {
        auto w = writer<Spinor2D>();
        w.description("2D Spinor in double");
        w.property(szA, &Spinor2D::a).description(szA_Spinor).tag(kTag_Save).tag(kTag_Print);
        w.property(szXY, &Spinor2D::xy).description(szXY_Spinor).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        //w.operate_with<Vector3D>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.format<math_io::format<Spinor2D>>();
        w.parse<math_io::parse<Spinor2D>>();
        w.print<math_io::print<Spinor2D>>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Spinor2D>();
    }

    {
        auto w = writer<Spinor2F>();
        w.description("2D Spinor in float");
        w.property(szA, &Spinor2F::a).description(szA_Spinor).tag(kTag_Save).tag(kTag_Print);
        w.property(szXY, &Spinor2F::xy).description(szXY_Spinor).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        //w.operate_with<Vector3F>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.format<math_io::format<Spinor2F>>();
        w.parse<math_io::parse<Spinor2F>>();
        w.print<math_io::print<Spinor2F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Spinor2F>();
    }

}

YQ_INVOKE(reg_spinor2();)

