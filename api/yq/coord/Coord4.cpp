////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Coord4.hxx"
#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Coord4D)
YQ_TYPE_IMPLEMENT(yq::Coord4F)
YQ_TYPE_IMPLEMENT(yq::Coord4I)
YQ_TYPE_IMPLEMENT(yq::Coord4U)

template <typename T>
void     print_coord4(Stream& str, const Coord4<T>& v)
{
    str << "(" << v.i << "," << v.j << "," << v.k << "," << v.l << ")";
}

static void reg_coord4()
{
    {
        auto w = writer<Coord4D>();
        w.description("4D coordinate in double");
        w.property(szI, &Coord4D::i).description(szI_Coord);
        w.property(szJ, &Coord4D::j).description(szJ_Coord);
        w.property(szK, &Coord4D::k).description(szK_Coord);
        w.property(szL, &Coord4D::l).description(szL_Coord);
        w.print<print_coord4<double>>();
        w.operate_self();
        w.operate_with<double>();
    }

    {
        auto w = writer<Coord4F>();
        w.description("4D coordinate in float");
        w.property(szI, &Coord4F::i).description(szI_Coord);
        w.property(szJ, &Coord4F::j).description(szJ_Coord);
        w.property(szK, &Coord4F::k).description(szK_Coord);
        w.property(szL, &Coord4F::l).description(szL_Coord);
        w.print<print_coord4<float>>();
        w.operate_self();
        w.operate_with<float>();
    }

    {
        auto w = writer<Coord4I>();
        w.description("4D coordinate in integer");
        w.property(szI, &Coord4I::i).description(szI_Coord);
        w.property(szJ, &Coord4I::j).description(szJ_Coord);
        w.property(szK, &Coord4I::k).description(szK_Coord);
        w.property(szL, &Coord4I::l).description(szL_Coord);
        w.print<print_coord4<int>>();
        w.operate_self();
        w.operate_with<int>();
    }

    {
        auto w = writer<Coord4U>();
        w.description("4D coordinate in unsigned integer");
        w.property(szI, &Coord4U::i).description(szI_Coord);
        w.property(szJ, &Coord4U::j).description(szJ_Coord);
        w.property(szK, &Coord4U::k).description(szK_Coord);
        w.property(szL, &Coord4U::l).description(szL_Coord);
        w.print<print_coord4<unsigned>>();
        w.operate_self();
        w.operate_with<unsigned>();
    }
}

YQ_INVOKE(reg_coord4();)
