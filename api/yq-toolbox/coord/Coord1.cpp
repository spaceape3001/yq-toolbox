////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Coord1.hxx"
#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Coord1D)
YQ_TYPE_IMPLEMENT(yq::Coord1F)
YQ_TYPE_IMPLEMENT(yq::Coord1I)
YQ_TYPE_IMPLEMENT(yq::Coord1U)


template <typename T>
void     print_coord1(Stream& str, const Coord1<T>& v)
{
    str << "(" << v.i << ")";
}

static void reg_coord1()
{
    {
        auto w = writer<Coord1D>();
        w.description("1D coordinate in double");
        w.property(szI, &Coord1D::i).description(szI_Coord);
        w.print<print_coord1<double>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord1F>();
        w.description("1D coordinate in float");
        w.property(szI, &Coord1F::i).description(szI_Coord);
        w.print<print_coord1<float>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord1I>();
        w.description("1D coordinate in integer");
        w.property(szI, &Coord1I::i).description(szI_Coord);
        w.print<print_coord1<int>>();
        w.operate_self();
    }

    {
        auto w = writer<Coord1U>();
        w.description("1D coordinate in unsigned integer");
        w.property(szI, &Coord1U::i).description(szI_Coord);
        w.print<print_coord1<unsigned>>();
        w.operate_self();
    }

}

YQ_INVOKE(reg_coord1();)