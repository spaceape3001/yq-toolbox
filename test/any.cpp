////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/Any.hpp>
#include <0/basic/Logging.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

bool    string_test(const char* z)
{
    return Any(z).value<std::string>().value == z;
}

int    parse_int(int n)
{
    try {
        std::string     z   = to_string(n);
        Any     v(PARSE, meta<int>(), z, THROW);
        return v.value<int>();
    } 
    catch(std::error_code ec)
    {
        yInfo() << "Failed to parse int " << n << ": " << ec.message();
        return 0;
    }
}

int main(){
    log_to_std_output();
    Meta::freeze();

    "blank variant"_test = [](){
        Any     v;
        expect(0_u == v.type().id());
        expect(false == (v != v));
        expect(true == (v == v));
    };
    
    "strings"_test = [](){
        expect(true == string_test("foo"));
        expect(true == string_test("foobar"));
    };
    
    "parse int64"_test = [](){
        expect( 0_i == parse_int(0));
        expect( 42_i == parse_int(42));
        expect( -42_i == parse_int(-42));
    };

    return ut::cfg<>.run();
}

