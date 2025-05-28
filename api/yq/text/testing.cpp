////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/text/testing.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/container/set_utils.hpp>

namespace yq {
    //! Used for unit tests
    bool        is_similar(const string_view_set_t&expected, std::initializer_list<std::string_view> actual)
    {
        string_view_set_t   consider = make_set(actual, IgCase());
        return expected == consider;
    }
}
