////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/core/Logging.hpp>
#include <yq/b3fmt/line.hpp>
#include <yq/meta/Meta.hpp>
#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::b3;

int main(int argc, char* argv[])
{
    Meta::init();
    log_to_std_error();

    "empty line"_test = []{
        
        auto ret    = loadB3Buffer("");
        expect(true == ret.has_value());
        expect(ret -> lines.empty());
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
            auto ret    = loadB3Buffer(z);
            expect(true == ret.has_value());
            expect(ret->lines.empty());
        }
    
    };

    "simple line"_test = []{
        auto ret    = loadB3Buffer("simple 1 2 3 4 5");
        expect(true == ret.has_value());
        expect(1ULL == ret->lines.size());
        if(!ret->lines.empty()){
            const line_t& b  = ret->lines[0];
            expect(b.values == string_vector_t{ "simple", "1", "2", "3", "4", "5" });
        }
    };

    "semi simple line"_test = []{
        auto ret    = loadB3Buffer(R"(
        simple 1 2 3 4 5
)");
        expect(true == ret.has_value());
        expect(1ULL == ret->lines.size());
        if(!ret->lines.empty()){
            const line_t& b  = ret->lines[0];
            expect(b.values == string_vector_t{ "simple", "1", "2", "3", "4", "5" });
        }
        //expect(b.indent == 8);
    };
    
    "multi line"_test = []{
        auto ret = loadB3Buffer(R"(
        utter 1 2 3 4 5 \
            6 7 8 9 10
)");

        expect(true == ret.has_value());
        expect(1ULL == ret->lines.size());
        if(!ret->lines.empty()){
            const line_t& b  = ret->lines[0];
            expect(b.values == string_vector_t{ "utter", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" });
        }
    
    };
    
    "quote line"_test = []{
        auto ret=loadB3Buffer(R"(
    udder foo="1" "bar=2" spartan="1 2 3"
)");

        expect(true == ret.has_value());
        expect(1ULL == ret->lines.size());
        if(!ret->lines.empty()){
            const line_t& b  = ret->lines[0];
            expect(b.values == string_vector_t{ "udder", "bar=2" });
            
            expect(b.attrs.size() == 2);
            expect(b.attrs.get("foo") == "1");
            expect(b.attrs.get("spartan") == "1 2 3");
        }
    };
    
    "blocked"_test = []{
        auto ret=loadB3Buffer(R"(
    udder foo="1" "bar=2" spartan="1 2 3" {
        simple 1 2 3 4 5
    }
)");

        expect(true == ret.has_value());
        expect(1ULL == ret->lines.size());
        if(!ret->lines.empty()){
            const line_t& b  = ret->lines[0];
            expect(b.values == string_vector_t{ "udder", "bar=2" });
            

            expect(b.attrs.size() == 2);
            expect(b.attrs.get("foo") == "1");
            expect(b.attrs.get("spartan") == "1 2 3");
            
            expect(b.sublines.size() == 1);
            if(!b.sublines.empty()){
                const line_t& c = b.sublines[0];

                expect(c.values == string_vector_t{ "simple", "1", "2", "3", "4", "5" });
            }
        }
    };
    
    "multiple"_test = []{
        auto ret=loadB3Buffer(R"(
    udder foo="1" "bar=2" spartan="1 2 3"
    udder foo="1" "bar=2" spartan="1 2 3"
)");

        expect(true == ret.has_value());
        expect(2ULL == ret->lines.size());
    };

    return ut::cfg<>.run();
}
