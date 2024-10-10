////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Coord5.hxx"
#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Coord5D)
YQ_TYPE_IMPLEMENT(yq::Coord5F)
YQ_TYPE_IMPLEMENT(yq::Coord5I)
YQ_TYPE_IMPLEMENT(yq::Coord5U)

template <typename T>
void     print_coord5(Stream& str, const Coord5<T>& v)
{
    str << "(" << v.i << "," << v.j << "," << v.k << "," << v.l << "," << v.m << ")";
}

static void reg_coord5()
{
    {
        auto w = writer<Coord5D>();
        w.description("5D coordinate in double");
        w.property(szI, &Coord5D::i).description(szI_Coord);
        w.property(szJ, &Coord5D::j).description(szJ_Coord);
        w.property(szK, &Coord5D::k).description(szK_Coord);
        w.property(szL, &Coord5D::l).description(szL_Coord);
        w.property(szM, &Coord5D::m).description(szM_Coord);
        w.print<print_coord5<double>>();
        w.operate_self();
        w.operate_with<double>();
    }

    {
        auto w = writer<Coord5F>();
        w.description("5D coordinate in float");
        w.property(szI, &Coord5F::i).description(szI_Coord);
        w.property(szJ, &Coord5F::j).description(szJ_Coord);
        w.property(szK, &Coord5F::k).description(szK_Coord);
        w.property(szL, &Coord5F::l).description(szL_Coord);
        w.property(szM, &Coord5F::m).description(szM_Coord);
        w.print<print_coord5<float>>();
        w.operate_self();
        w.operate_with<float>();
    }

    {
        auto w = writer<Coord5I>();
        w.description("5D coordinate in integer");
        w.property(szI, &Coord5I::i).description(szI_Coord);
        w.property(szJ, &Coord5I::j).description(szJ_Coord);
        w.property(szK, &Coord5I::k).description(szK_Coord);
        w.property(szL, &Coord5I::l).description(szL_Coord);
        w.property(szM, &Coord5I::m).description(szM_Coord);
        w.print<print_coord5<int>>();
        w.operate_self();
        w.operate_with<int>();
    }

    {
        auto w = writer<Coord5U>();
        w.description("5D coordinate in unsigned integer");
        w.property(szI, &Coord5U::i).description(szI_Coord);
        w.property(szJ, &Coord5U::j).description(szJ_Coord);
        w.property(szK, &Coord5U::k).description(szK_Coord);
        w.property(szL, &Coord5U::l).description(szL_Coord);
        w.property(szM, &Coord5U::m).description(szM_Coord);
        w.print<print_coord5<unsigned>>();
        w.operate_self();
        w.operate_with<unsigned>();
    }
}

YQ_INVOKE(reg_coord5();)
