////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Coord3.hxx"
#include <yq/strings.hpp>
#include <yq/basic/DelayInit.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Coord3D)
YQ_TYPE_IMPLEMENT(yq::Coord3F)
YQ_TYPE_IMPLEMENT(yq::Coord3I)
YQ_TYPE_IMPLEMENT(yq::Coord3U)

template <typename T>
void     print_coord3(Stream& str, const Coord3<T>& v)
{
    str << "(" << v.i << "," << v.j << "," << v.k << ")";
}

static void reg_coord3()
{
    {
        auto w = writer<Coord3D>();
        w.description("3D coordinate in double");
        w.property(szI, &Coord3D::i).description(szI_Coord);
        w.property(szJ, &Coord3D::j).description(szJ_Coord);
        w.property(szK, &Coord3D::k).description(szK_Coord);
        w.print<print_coord3<double>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord3F>();
        w.description("3D coordinate in float");
        w.property(szI, &Coord3F::i).description(szI_Coord);
        w.property(szJ, &Coord3F::j).description(szJ_Coord);
        w.property(szK, &Coord3F::k).description(szK_Coord);
        w.print<print_coord3<float>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord3I>();
        w.description("3D coordinate in integer");
        w.property(szI, &Coord3I::i).description(szI_Coord);
        w.property(szJ, &Coord3I::j).description(szJ_Coord);
        w.property(szK, &Coord3I::k).description(szK_Coord);
        w.print<print_coord3<int>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord3U>();
        w.description("3D coordinate in unsigned integer");
        w.property(szI, &Coord3U::i).description(szI_Coord);
        w.property(szJ, &Coord3U::j).description(szJ_Coord);
        w.property(szK, &Coord3U::k).description(szK_Coord);
        w.print<print_coord3<unsigned>>();
        w.operate_self();
    }
}

YQ_INVOKE(reg_coord3();)
