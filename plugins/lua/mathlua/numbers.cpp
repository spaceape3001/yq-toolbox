////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/DelayInit.hpp>
#include <yq/lua/lualua.hpp>
#include <yq/trait/numbers.hpp>
#include <numbers>

using namespace yq;
using namespace yq::lua;

namespace {
    void reg_numbers()
    {
        reg(GLOBAL, "pi", std::numbers::pi);
        reg(GLOBAL, "sqrt2", yq::sqrt2);
        reg(GLOBAL, "sqrt3", yq::sqrt3);
        reg(GLOBAL, "e", std::numbers::e);
    }
    
    YQ_INVOKE(reg_numbers();)
}
