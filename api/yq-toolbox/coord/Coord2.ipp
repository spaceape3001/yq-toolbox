////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Coord2.hxx"
#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Coord2D)
YQ_TYPE_IMPLEMENT(yq::Coord2F)
YQ_TYPE_IMPLEMENT(yq::Coord2I)
YQ_TYPE_IMPLEMENT(yq::Coord2U)

template <typename T>
void     print_coord2(Stream& str, const Coord2<T>& v)
{
    str << "(" << v.i << "," << v.j << ")";
}

static void reg_coord2()
{
    {
        auto w = writer<Coord2D>();
        w.description("2D coordinate in double");
        w.property(szI, &Coord2D::i).description(szI_Coord);
        w.property(szJ, &Coord2D::j).description(szJ_Coord);
        w.print<print_coord2<double>>();
        w.operate_self();
        w.operate_with<double>();
    }

    {
        auto w = writer<Coord2F>();
        w.description("2D coordinate in float");
        w.property(szI, &Coord2F::i).description(szI_Coord);
        w.property(szJ, &Coord2F::j).description(szJ_Coord);
        w.print<print_coord2<float>>();
        w.operate_self();
        w.operate_with<float>();
    }

    {
        auto w = writer<Coord2I>();
        w.description("2D coordinate in integer");
        w.property(szI, &Coord2I::i).description(szI_Coord);
        w.property(szJ, &Coord2I::j).description(szJ_Coord);
        w.print<print_coord2<int>>();
        w.operate_self();
        w.operate_with<int>();
    }

    {
        auto w = writer<Coord2U>();
        w.description("2D coordinate in unsigned integer");
        w.property(szI, &Coord2U::i).description(szI_Coord);
        w.property(szJ, &Coord2U::j).description(szJ_Coord);
        w.print<print_coord2<unsigned>>();
        w.operate_self();
        w.operate_with<unsigned>();
    }
}

YQ_INVOKE(reg_coord2();)
