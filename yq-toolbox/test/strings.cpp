////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <basic/Vector.hpp>
#include <basic/IterUtf8.hpp>
#include <basic/TextUtils.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    
    "is alnum"_test =  [](){
        expect(true == is_alnum('a'));
        expect(true == is_alnum('A'));
        expect(true == is_alnum('0'));
        expect(false == is_alnum('+'));
    };
    
    "is alpha"_test = [](){
        expect(true == is_alpha('A'));
        expect(false == is_alpha('1'));
        expect(false == is_alpha('+'));
    };
    
    "is digit"_test = [](){
        expect(true == is_digit('1'));
        expect(false == is_digit('A'));
        expect(false == is_digit('+'));
    };
    
    "is lowercase"_test = [](){
        expect(false == is_lower('0'));
        expect(false == is_lower('A'));
        expect(true == is_lower('a'));
        expect(true == is_lower('z'));
        expect(false == is_lower('+'));
    };

    "is uppercase"_test = [](){
        expect(false == is_upper('0'));
        expect(true == is_upper('A'));
        expect(false == is_upper('a'));
        expect(false == is_upper('z'));
        expect(false == is_upper('+'));
    };

    "bad booleans"_test = [](){
        expect(false == to_boolean("bad").good);
        expect(false == to_boolean("falsey").good);
        expect(false == to_boolean("truy").good);
        expect(false == to_boolean("truey").good);
    };
    
    "false booleans"_test = [](){
        expect(to_boolean("0") == boolean_r{ false, true });
        expect(to_boolean("False") == boolean_r{ false, true });
        expect(to_boolean("false") == boolean_r{ false, true });
        expect(to_boolean("fAlSe") == boolean_r{ false, true });
        expect(to_boolean("NO") == boolean_r{ false, true });
        expect(to_boolean("No") == boolean_r{ false, true });
        expect(to_boolean("no") == boolean_r{ false, true });
        expect(to_boolean("nO") == boolean_r{ false, true });
    };
    
    "true booleans"_test = [](){
        expect(to_boolean("1") == boolean_r{ true, true });
        expect(to_boolean("True") == boolean_r{ true, true });
        expect(to_boolean("true") == boolean_r{ true, true });
        expect(to_boolean("truE") == boolean_r{ true, true });
        expect(to_boolean("YES") == boolean_r{ true, true });
        expect(to_boolean("yes") == boolean_r{ true, true });
    };
    
    "is_similar"_test = [](){
        expect(is_similar("foobar", "FooBar") == true);
        expect(is_similar("foodar", "FooBar") == false);
        expect(is_similar("foobar", "Foo Bar") == false);
    };
    
    "split string"_test = [](){
        expect(split("1 2 3", ' ') == Vector<std::string_view>({ "1", "2", "3" }));
        expect(split("1,2,3", ',') == Vector<std::string_view>({ "1", "2", "3" }));
    };
    
    "split sql"_test  = [](){
        const char* szText = 
"CREATE TABLE Classes (\n\
        -- ID is the document ID\n\
    id          INTEGER PRIMARY KEY,\n\
    k           VARCHAR(255) NOT NULL UNIQUE COLLATE NOCASE,\n\
    edge        BOOLEAN NOT NULL DEFAULT 0,\n\
	removed     BOOLEAN NOT NULL DEFAULT 0,\n\
    name        VARCHAR(255),\n\
    icon        INTEGER NOT NULL DEFAULT 0,\n\
    \n\
        -- dependency graph!\n\
    deps        INTEGER,\n\
    plural      VARCHAR(255),\n\
    brief       VARCHAR(255)\n\
);\n\
\n\
CREATE TABLE CDepends (\n\
    class       INTEGER NOT NULL,\n\
    base        INTEGER NOT NULL,\n\
    UNIQUE(class,base) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CDependsDef (\n\
    class       INTEGER NOT NULL,\n\
    base        INTEGER NOT NULL,\n\
    UNIQUE(class,base) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CEdges (\n\
    class   INTEGER NOT NULL,\n\
    source  INTEGER NOT NULL,\n\
    target INTEGER NOT NULL,\n\
    UNIQUE(class,source,target) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CFields (\n\
    class       INTEGER NOT NULL,\n\
    field       INTEGER NOT NULL,\n\
    UNIQUE(class, field) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CFieldsDef (\n\
    class       INTEGER NOT NULL,\n\
    field       INTEGER NOT NULL,\n\
    UNIQUE(class, field) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CReverses (\n\
    class       INTEGER NOT NULL,\n\
    reverse     INTEGER NOT NULL,\n\
    UNIQUE(class,reverse) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CReversesDef (\n\
    class       INTEGER NOT NULL,\n\
    reverse     INTEGER NOT NULL,\n\
    UNIQUE(class,reverse) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CSources (\n\
    class       INTEGER NOT NULL,\n\
    source      INTEGER NOT NULL,\n\
    UNIQUE(class,source) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CSourcesDef (\n\
    class       INTEGER NOT NULL,\n\
    source      INTEGER NOT NULL,\n\
    UNIQUE(class,source) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CTargets (\n\
    class       INTEGER NOT NULL,\n\
    target      INTEGER NOT NULL,\n\
    UNIQUE(class,target) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CTargetsDef (\n\
    class       INTEGER NOT NULL,\n\
    target      INTEGER NOT NULL,\n\
    UNIQUE(class,target) ON CONFLICT IGNORE\n\
);\n\
\n\
CREATE TABLE CTags (\n\
    class       INTEGER NOT NULL,\n\
    tag         INTEGER NOT NULL,\n\
    UNIQUE(class,tag) ON CONFLICT IGNORE\n\
);\n\
";

        const char* szLines[] = {
"CREATE TABLE Classes (",
"        -- ID is the document ID",
"    id          INTEGER PRIMARY KEY,",
"    k           VARCHAR(255) NOT NULL UNIQUE COLLATE NOCASE,",
"    edge        BOOLEAN NOT NULL DEFAULT 0,",
"	removed     BOOLEAN NOT NULL DEFAULT 0,",
"    name        VARCHAR(255),",
"    icon        INTEGER NOT NULL DEFAULT 0,",
"    ",
"        -- dependency graph!",
"    deps        INTEGER,",
"    plural      VARCHAR(255),",
"    brief       VARCHAR(255)",
");",
"",
"CREATE TABLE CDepends (",
"    class       INTEGER NOT NULL,",
"    base        INTEGER NOT NULL,",
"    UNIQUE(class,base) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CDependsDef (",
"    class       INTEGER NOT NULL,",
"    base        INTEGER NOT NULL,",
"    UNIQUE(class,base) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CEdges (",
"    class   INTEGER NOT NULL,",
"    source  INTEGER NOT NULL,",
"    target INTEGER NOT NULL,",
"    UNIQUE(class,source,target) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CFields (",
"    class       INTEGER NOT NULL,",
"    field       INTEGER NOT NULL,",
"    UNIQUE(class, field) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CFieldsDef (",
"    class       INTEGER NOT NULL,",
"    field       INTEGER NOT NULL,",
"    UNIQUE(class, field) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CReverses (",
"    class       INTEGER NOT NULL,",
"    reverse     INTEGER NOT NULL,",
"    UNIQUE(class,reverse) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CReversesDef (",
"    class       INTEGER NOT NULL,",
"    reverse     INTEGER NOT NULL,",
"    UNIQUE(class,reverse) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CSources (",
"    class       INTEGER NOT NULL,",
"    source      INTEGER NOT NULL,",
"    UNIQUE(class,source) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CSourcesDef (",
"    class       INTEGER NOT NULL,",
"    source      INTEGER NOT NULL,",
"    UNIQUE(class,source) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CTargets (",
"    class       INTEGER NOT NULL,",
"    target      INTEGER NOT NULL,",
"    UNIQUE(class,target) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CTargetsDef (",
"    class       INTEGER NOT NULL,",
"    target      INTEGER NOT NULL,",
"    UNIQUE(class,target) ON CONFLICT IGNORE",
");",
"",
"CREATE TABLE CTags (",
"    class       INTEGER NOT NULL,",
"    tag         INTEGER NOT NULL,",
"    UNIQUE(class,tag) ON CONFLICT IGNORE",
");",
""
        };
        
        size_t  i   = 0;
        vsplit(szText, '\n', [&](std::string_view s){
            expect( szLines[i++] == s );
        });
    };
    
    "starts_with"_test = [](){
    
        expect( true == starts("--", "--") );
        expect( true == starts("-- frostbite", "--") );
        expect( false == starts("-foobar", "--"));
    
    };
    
    "is_in"_test = [](){
        expect( true == is_in("foo", std::initializer_list<std::string_view>{ "foo", "bar" }));
        expect( false == is_in("foox", std::initializer_list<std::string_view>{ "foo", "bar" }));
        expect( true == is_in("foo", std::initializer_list<std::string_view>{ "bar", "FOO" }));
    };
    
    "starts_igCase"_test = [](){
        expect( true == starts_igCase("BODY {", "body") );
    };
    
    "iter_utf8"_test = [](){
        std::string_view    txt = "² ";
        IterUtf8      a(txt);
        char32_t    ch  = a.next();
        expect(U'²' == ch);
    };
    
    "equal_test"_test = [](){
        std::string_view    a   = "unit::Centimeter";
        std::string_view    b   = "unit::Centimeter²";
        expect( true == (a != b ));
    };
    
    "equal_isCase"_test = [](){
        
        std::string_view    a   = "unit::Centimeter";
        std::string_view    b   = "unit::Centimeter²";
    
        expect( true == is_less_igCase(a,b));
        expect( true == !is_less_igCase(b,a));
    };
};

int main(){
    return ut::cfg<>.run();
}
