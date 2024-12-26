////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

/*
    WIZ is meant as a meta-extractor of information from a header file, and
    shoves it into source files as reflection type of data.
    
    (ie enumerations, types, objects, etc, along the lines of MOC)
    
    We'll start with the assumption of well formatted code
*/

#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include <yq/core/Flags.hpp>
#include <yq/text/transform.hpp>

using namespace yq;

using fs_path       = std::filesystem::path;
using fs_vector     = std::vector<fs_path>;
using fs_set        = std::set<fs_path>;
using string_set    = std::set<std::string>;

struct Env {
    fs_path     executable;
    fs_path     outdir;
    fs_vector   include_path;
    fs_vector   input_files;
};

Env  g;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool            equal(const char* lhs, const char* rhs)
{
    for(;*lhs && *rhs; ++lhs, ++rhs){
        if(*rhs != *lhs)
            return false;
    }
    return !(*lhs || *rhs);
}

bool            equal(igcase_k, const char* lhs, const char* rhs)
{
    for(;*lhs && *rhs; ++lhs, ++rhs){
        if(tolower(*rhs) != tolower(*lhs))
            return false;
    }
    return !(*lhs || *rhs);
}

const char*    start(const char* str, const char* pat)
{
    // skip whitespace
    for(;*str && isspace(*str); ++str)
        ;
        
    for(;*str && *pat; ++str, ++pat){
        if(*str != *pat)
            return nullptr;
    }
    
    return *pat ? nullptr : str;
}


const char*    start(igcase_k, const char* str, const char* pat)
{
    // skip whitespace
    for(;*str && isspace(*str); ++str)
        ;
        
    for(;*str && *pat; ++str, ++pat){
        if(tolower(*str) != tolower(*pat))
            return nullptr;
    }

    return *pat ? nullptr : str;
}

fs_path resolve(std::string_view s, const fs_path& dir={})
{
    if(!dir.empty()){
        fs_path p   = dir / s;
        if(std::filesystem::exists(p))
            return p;
    }
    
    for(const fs_path& fs : g.include_path){
        fs_path p   = fs / s;
        if(std::filesystem::exists(p))
            return p;
    }
    
    return {};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum class Bit : uint8_t {
    
};


struct Token {
    std::string         name;
    yq::Flags<Bit>      bits;
};

struct Enumeration : public Token {
};

struct Type : public Token {
    string_set      aliases;
};

struct Class : public Token {

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class WorkFile {
private:

    struct Stat {
        const fs_path   file;
        const fs_path   dir;
        unsigned        line    = 0;
        
        Stat(const fs_path& fp) : file(fp), dir(fp.parent_path()) {}
    };

    const fs_path       m_input;
    const fs_path       m_output;
    fs_set              m_seen;
    std::vector<Stat>   m_stat;

public:

    static fs_path      output_for(const fs_path& input)
    {
        fs_path stem        = input.stem();
        std::string tmp     = stem.string() + "_wiz.cpp";
        return g.outdir / tmp.c_str();
    }

    WorkFile(const fs_path& _input) : m_input(_input), m_output(output_for(_input))
    {
    }
    
    void        parse()
    {
        read(m_input, true);
    }
    
    void        write()
    {
        std::cout << "Would write to " << m_output << "\n";
    }
    
private:
    
    ////// READING ////////////////////////


    void        include(std::string_view spec)
    {
        std::string_view s   = trimmed(spec);
        if(s.size() <= 2)
            throw "Bad filestring for header detected!";
        
        fs_path p;
        bool    local   = s[0] == '"';
        s = s.substr(1, s.size()-2);
        if(local){
            p = resolve(s, m_stat.back().dir);
        } else {
            p = resolve(s);
        }

        if(p.empty()){
            if(local)
                throw "Unable to resolve header";
            return ;
        }
        
        read(p);
    }
    
    void        doxygen_begin(bool prev)
    {
    }

    void        doxygen_line(std::string_view k)
    {
std::cout << "Doxygen: " << k << "\n";
    }
    
    void        doxygen_end()
    {
    }
    
    void        class_start(std::string_view k)
    {
    }
    
    void        enum_begin(std::string_view k)
    {
    }
    
    void        class_begin(std::string_view k)
    {
    }
    
    void        wiz_line(std::string_view k)
    {
    }

    void        read(const fs_path& fp, bool meta=false)
    {
        auto [itr, fFirst]   = m_seen.insert(fp);
        if(!fFirst)
            return ;
            
        m_stat.push_back(Stat(fp));
        Stat&   stat    = m_stat.back();
        
        std::ifstream   in(fp);
        if(!in.good())
            throw "Unable to open file";
        
        char    buffer[1024];

        while(in.getline(buffer, sizeof(buffer))){
            ++stat.line;
            const char*     txt   = nullptr;
            std::cout << "> " << buffer << '\n';
            if((txt = start(buffer, "#include"))){
std::cout << stat.line << ": include " << txt << '\n';
                include(txt);
            } else if((txt = start(buffer, "//>"))){
std::cout << stat.line << ": wiz " << txt << '\n';
                wiz_line(txt);
            } else if((txt = start(buffer, "//!<"))){
std::cout << stat.line << ": doxygen " << txt << '\n';
                doxygen_begin(true);
                doxygen_line(txt);
                doxygen_end();
            } else if((txt = start(buffer, "//!"))){
std::cout << stat.line << ": doxygen " << txt << '\n';
                doxygen_begin(false);
                doxygen_line(txt);
                doxygen_end();
            } else if((txt = start(buffer, "enum "))){
std::cout << stat.line << ": enumeration " << txt << '\n';
                enum_begin(txt);
            } else if((txt = start(buffer, "class "))){
                class_begin(txt);
            } else {
std::cout << stat.line << ": unrecognized\n";
            }
        }

        
        m_stat.pop_back();
    }

    ////// WRITING ////////////////////////
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool    process(const std::filesystem::path& input)
{
    WorkFile    file(input);
std::cout << "Processing(" << input << ")\n";

    enum class Stage {
        None,
        Parse,
        Write,
        Done
    };

    Stage stage     = Stage::None;
    const char* msg = "No reason specified";

    try {
        stage   = Stage::Parse;
        file.parse();
        stage   = Stage::Write;
        file.write();
        stage   = Stage::Done;
    }
    catch(const char* exMsg)
    {
        msg     = exMsg;
    }
    
    if(stage != Stage::Done){
        std::cerr << "Process(" << input << "): " << msg;
    }
    
    return true;
}


int main(int argc, char* argv[])
{
    g.executable     = argv[0];
    g.include_path.push_back(YQ_API_DIR);

    for(int i=1;i<argc;++i){
        if(argv[i][0] == '-'){
            if(const char* z = start(argv[i], "-I"))
                g.include_path.push_back(z);
        } else {
            g.input_files.push_back(argv[i]);
        }
    }
    
    unsigned    pass    = 0;
    unsigned    fail    = 0;
    
    for(auto& fs : g.input_files){
        if(process(fs)){
            ++pass;
        } else {
            ++fail;
        }
    }
    
    return -(int) fail;
}
