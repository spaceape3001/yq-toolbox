////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/math/Statistics.hxx>
#include <yq/math/utility.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <boost/ut.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute    tol(1e-8);
    "simple"_test = [&]{
        auto stats  = statistics({1., 2., 3., 4.});
        expect(is_close(tol, stats.mean, 2.5 ));
        expect(is_close(tol, stats.min, 1. ));
        expect(is_close(tol, stats.max, 4. ));
        expect(is_close(tol, stats.normI, 4. ));
        expect(is_close(tol, stats.stddev, 1.290994448735806 ));
    };

    return ut::cfg<>.run();
}
