////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>

#include <yq/core/Logging.hpp>
#include <yq/process/Settings.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/text/match.hpp>
#include <yq/text/testing.hpp>

using namespace yq;

const char* szTestData = R"""(
; a comment
key1=value1
key2  = value2

[section]

key1  = value3

key2  = value4

key1  = value5

)""";

namespace ut = boost::ut;
using namespace ut;

const char* szTestFile  = "settings.ini";

int main(int argc, char* argv[])
{
    log_to_std_output();
    file_write(szTestFile, szTestData);
    
    "read"_test = []{
        Settings    ini(szTestFile);
        expect(true == is_similar(ini.sections(), { "section" }));
        expect(true == is_similar(ini.keys(), { "key1", "key2" }));
        expect(true == is_similar(ini.keys("section"), { "key1", "key2" }));
        expect(true == is_similar(ini.value("key1"), "value1"));
        expect(true == is_similar(ini.value("key2"), "value2"));
        expect(true == is_similar(ini.value("key1","section"), "value5"));
        expect(true == is_similar(ini.value("key2","section"), "value4"));
    };
    
    return ut::cfg<>.run();
}


