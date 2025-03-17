////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/core/Logging.hpp>
//#include <0/basic/CollectionUtils.hpp>
#include <ys/io/b3grammar.hpp>
#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::spatial;


ut::suite tests = []{
    "empty line"_test = []{
        
        auto ret    = B3Line::decode("");
        expect(true == ret.has_value());
        expect(ret -> empty());
    };
    
    "comment line"_test = []{
static const std::string_view kComments[] = {
    "# This is a test...",
    R"(

#  This is a multiline test...

#  This is a multiline test...

)"
};

        for(std::string_view z : kComments){
            auto ret    = B3Line::decode(z);
            expect(true == ret.has_value());
            expect(ret->empty());
        }
    
    };
    
    "simple line"_test = []{
        auto ret    = B3Line::decode("simple 1 2 3 4 5");
        expect(true == ret.has_value());
        B3Line b  = *ret;
        expect(b.tokens == string_vector_t{ "simple", "1", "2", "3", "4", "5" });
    };

    "semi simple line"_test = []{
        auto ret    = B3Line::decode(R"(
        simple 1 2 3 4 5
)");
        expect(true == ret.has_value());
        B3Line b  = *ret;
        expect(b.tokens == string_vector_t{ "simple", "1", "2", "3", "4", "5" });
        expect(b.indent == 8);
    };
    
    "multi line"_test = []{
        auto ret = B3Line::decode(R"(
        utter 1 2 3 4 5 \
            6 7 8 9 10
)");

        expect(true == ret.has_value());
        B3Line b  = *ret;
        expect(b.tokens == string_vector_t{ "utter", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" });
        expect(b.indent == 8);
    
    };
    
    "quote line"_test = []{
        auto ret=B3Line::decode(R"(
    udder foo="1" "bar=2" spartan="1 2 3"
)");

        expect(true == ret.has_value());
        B3Line b  = *ret;
        expect(b.tokens == string_vector_t{ "udder", "foo=1", "bar=2", "spartan=1 2 3" });
        expect(b.indent == 4);

    };
};

int main(){
    log_to_std_output();
    return ut::cfg<>.run();
};
