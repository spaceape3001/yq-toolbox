////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Coord6.hxx"
#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Coord6D)
YQ_TYPE_IMPLEMENT(yq::Coord6F)
YQ_TYPE_IMPLEMENT(yq::Coord6I)
YQ_TYPE_IMPLEMENT(yq::Coord6U)

template <typename T>
void     print_coord6(Stream& str, const Coord6<T>& v)
{
    str << "(" << v.i << "," << v.j << "," << v.k << "," << v.l << "," << v.m << "," << v.n << ")";
}

static void reg_coord6()
{
    {
        auto w = writer<Coord6D>();
        w.description("6D coordinate in double");
        w.property(szI, &Coord6D::i).description(szI_Coord);
        w.property(szJ, &Coord6D::j).description(szJ_Coord);
        w.property(szK, &Coord6D::k).description(szK_Coord);
        w.property(szL, &Coord6D::l).description(szL_Coord);
        w.property(szM, &Coord6D::m).description(szM_Coord);
        w.property(szN, &Coord6D::n).description(szN_Coord);
        w.print<print_coord6<double>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord6F>();
        w.description("6D coordinate in float");
        w.property(szI, &Coord6F::i).description(szI_Coord);
        w.property(szJ, &Coord6F::j).description(szJ_Coord);
        w.property(szK, &Coord6F::k).description(szK_Coord);
        w.property(szL, &Coord6F::l).description(szL_Coord);
        w.property(szM, &Coord6F::m).description(szM_Coord);
        w.property(szN, &Coord6F::n).description(szN_Coord);
        w.print<print_coord6<float>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord6I>();
        w.description("6D coordinate in integer");
        w.property(szI, &Coord6I::i).description(szI_Coord);
        w.property(szJ, &Coord6I::j).description(szJ_Coord);
        w.property(szK, &Coord6I::k).description(szK_Coord);
        w.property(szL, &Coord6I::l).description(szL_Coord);
        w.property(szM, &Coord6I::m).description(szM_Coord);
        w.property(szN, &Coord6I::n).description(szN_Coord);
        w.print<print_coord6<int>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord6U>();
        w.description("6D coordinate in unsigned integer");
        w.property(szI, &Coord6U::i).description(szI_Coord);
        w.property(szJ, &Coord6U::j).description(szJ_Coord);
        w.property(szK, &Coord6U::k).description(szK_Coord);
        w.property(szL, &Coord6U::l).description(szL_Coord);
        w.property(szM, &Coord6U::m).description(szM_Coord);
        w.property(szN, &Coord6U::n).description(szN_Coord);
        w.print<print_coord6<unsigned>>();
        w.operate_self();
    }
}

YQ_INVOKE(reg_coord6();)
