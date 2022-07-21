#include <boost/ut.hpp>
#include <basic/HttpParser.hpp>
#include <basic/TextUtils.hpp>
#include <basic/Url.hpp>
#include <basic/VersionSpec.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "versions"_test = [](){
        expect( VersionSpec{ "http", 0, 9 } == to_version_spec("http/0.9") );
        expect( VersionSpec{ "https", 0, 9 } != to_version_spec("http/0.9") );
        expect( VersionSpec{ "http", 1, 1 } == to_version_spec("http/1.1") );
        expect( VersionSpec{ "sftp", 0, 9 } == to_version_spec("sftp/0.9") );
    };
    
    "versions match"_test = [](){
        expect( is_similar(http11(), http10()) == false );
        expect( is_similar(http10(), http10()) == true );
        expect( is_similar(http09(), http09()) == true );
        expect( is_similar(to_version_spec("HtTP/1.0"), http10()) == true);
    };
    
    "method line"_test = [](){
        expect( MethodUriVersion{ "get", "http://www.google.com", "" } == parse_method_uri( "get http://www.google.com" ));
        expect( MethodUriVersion{ "delete", "http://www.google.com", "http/1.2" } == parse_method_uri( "delete http://www.google.com  http/1.2 " ));
    };
    
    "headers"_test = [](){
        expect( KVView{ "User-Agent", "Dummy" } == parse_header_line("  User-Agent :  Dummy "));
    };
    
    "uri_parse"_test = [](){
    
        expect( UrlView{ "http", "", "", "www.google.com",  "/test.php", "", "", 0 } == to_url_view("http://www.google.com/test.php"));
        expect( UrlView{ "ftp", "nobody", "",  "www.google.com", "/test.php", "", "", 0 } == to_url_view("ftp://nobody@www.google.com/test.php"));
        expect( UrlView{ "ftp", "nobody", "secret",  "www.google.com", "/test.php", "foobar=true", "hello", 8080 } == to_url_view("ftp://nobody:secret@www.google.com:8080/test.php?foobar=true#hello"));
        expect( UrlView{ "https", "", "",  "www.google.com", "/test.php", "foobar=true", "hello", 8080 } == to_url_view("https://www.google.com:8080/test.php?foobar=true#hello"));
        expect( UrlView{ "file", "", "",  "", "/test.php", "foobar=true", "hello", 0 } == to_url_view("file:///test.php?foobar=true#hello"));
        expect( UrlView{ "", "", "",  "", "/test.php", "foobar=true", "hello", 0 } == to_url_view("///test.php?foobar=true#hello"));
        expect( UrlView{ "", "", "",  "", "/test.php", "foobar=true", "hello", 0 } == to_url_view("/test.php?foobar=true#hello"));
        expect( UrlView{ "", "", "",  "", "./test.php", "foobar=true", "hello", 0 } == to_url_view("./test.php?foobar=true#hello"));
        expect( UrlView{ "", "", "",  "", "/", "", "", 0 } == to_url_view("/"));
    };
    
    "uri_bad"_test = [](){
        expect( false == to_url_view("foobar.txt").good );
        expect( false == to_url_view("http[]//hello/foobar.txt").good );
    };
    
    "hostport parse"_test = [](){
        expect( UrlView("", "", "", "localhost", "", "", "", 12345) == as_host_port("localhost:12345"));
        expect( UrlView("", "", "", "localhost", "", "", "", 0) == as_host_port("localhost"));
    };
    
    "decode"_test = [](){
    
        std::string     s   = web_decode("%2Fadmin%2Ftag%2Fcreate");
        expect( "/admin/tag/create"s == s );
    };
};


int main(){
    return ut::cfg<>.run();
}
