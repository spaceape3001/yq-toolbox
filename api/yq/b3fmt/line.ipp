////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "line.hpp"
#include <yq/errors.hpp>
#include <yq/core/Logging.hpp>
#include <yq/container/Stack.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/text/transform.hpp>

#include <fstream>
#include <regex>
#include <sstream>

namespace yq::errors {
    using b3_indent_crash   = error_db::entry<"B3 indentation stack crash, means whitespace clashed....">;
    using b3_parsing        = error_db::entry<"B3 parsing error">;
}

namespace yq::b3 {
    namespace {
        static std::error_code parseCode(std::regex_constants::error_type etype) 
        {
            switch (etype) {
            case std::regex_constants::error_collate:
                return create_error<"B3 regex error_collate: invalid collating element request">();
            case std::regex_constants::error_ctype:
                return create_error<"B3 regex error_ctype: invalid character class">();
            case std::regex_constants::error_escape:
                return create_error<"B3 regex error_escape: invalid escape character or trailing escape">();
            case std::regex_constants::error_backref:
                return create_error<"B3 regex error_backref: invalid back reference">();
            case std::regex_constants::error_brack:
                return create_error<"B3 regex error_brack: mismatched bracket([ or ])">();
            case std::regex_constants::error_paren:
                return create_error<"B3 regex error_paren: mismatched parentheses(( or ))">();
            case std::regex_constants::error_brace:
                return create_error<"B3 regex error_brace: mismatched brace({ or })">();
            case std::regex_constants::error_badbrace:
                return create_error<"B3 regex error_badbrace: invalid range inside a { }">();
            case std::regex_constants::error_range:
                return create_error<"B3 regex error_range: invalid character range(e.g., [z-a])">();
            case std::regex_constants::error_space:
                return create_error<"B3 regex error_space: insufficient memory to handle this regular expression">();
            case std::regex_constants::error_badrepeat:
                return create_error<"B3 regex error_badrepeat: a repetition character (*, ?, +, or {) was not preceded by a valid regular expression">();
            case std::regex_constants::error_complexity:
                return create_error<"B3 regex error_complexity: the requested match is too complex">();
            case std::regex_constants::error_stack:
                return create_error<"B3 regex error_stack: insufficient memory to evaluate a match">();
            default:
                return create_error<"B3 unknown regex error">();
            }
        }

#if 0
        size_t     leadingWhitespaceCount(std::string_view text)
        {
            size_t     n=0, sz=text.size();
            for(; (n < sz) && is_space(text[n]); ++n)
                ;
            return n;
        }
#endif

        ssize_t     endsWith(std::string_view text, char ch)
        {
            ssize_t     j   = 1;
            for(auto i = text.rbegin(); i!=text.rend(); ++i, ++j){
                if(is_space(*i))
                    continue;
                return (*i == ch) ? (text.size()-j) : -1;
            }
            return j;
        }
        
        bool    isEmptyOrComment(std::string_view text)
        {
            for(auto i : text){
                if(i == '#')
                    return true;
                if(!is_space(i))
                    return false;
            }
            return true;
        }
    }
    
    
    
    file_x      loadB3(std::istream& file)
    {
        struct status_t {
            line_vector_t*      where = nullptr;
        };
    
        uint32_t                line        = 0;
        file_t                  ret;
        Stack<line_vector_t*>   blocks;
        blocks << &ret.lines;
        
        enum class Block {
            Unknown,
            Push,
            Pop
        };
        
        auto readline = [&]() -> std::string {
            if(file.eof() || file.bad())
                return {};
            ++line;
            char        text[1024];
            file.getline(text, sizeof(text)-1);
            text[sizeof(text)-1] = '\0';
            return text;
        };

        // Regex expressions are such a pain....
        std::regex  bit("(\\S+=\"[^\"]*\"|\\S+=\\S+|\"[^\"]*\"|\\S+)");
        std::regex  arg1("(\\S+)=\"([^\"]*)\"");
        std::regex  arg2("(\\S+)=(\\S+)");
        std::regex  quoted("\"([^\"]*)\"");

        //  In theory, this should match all components......    
        try {
            while(file.good() && !file.eof()){
                if(blocks.empty())
                    return errors::b3_indent_crash();
            
                std::string fline   = readline();
                do {
                    ssize_t q   = endsWith(fline, '\\');
                    if(q < 0)
                        break;
                    fline       = fline.substr(0, q) + readline();
                } while(file.good() && !file.eof());
                    
                if(isEmptyOrComment(fline))
                    continue;

                Block  blk      = Block::Push;
                ssize_t qb      = endsWith(fline, '{');
                ssize_t qe      = endsWith(fline, '}');
                if(qb != -1){
                    fline       = fline.substr(0,qb);
                    blk         = Block::Push;
                }
                if(qe != -1){
                    fline       = fline.substr(0,qe);
                    blk         = Block::Pop;
                }
                
                std::string    qline(trimmed(fline));
                if(!qline.empty()){
                    line_t      proto{.line=line};
                    
                    Vector<std::string>     toks;
                    std::sregex_token_iterator i(qline.begin(), qline.end(), bit, 1);
                    std::sregex_token_iterator j;
                    while(i != j)
                    {
                        toks << (*i++);
                    }

                    int     n   = 0;
                    for(const std::string &tok : toks){
                        ++n;
                        std::smatch sm;
                        if(std::regex_match(tok, sm, quoted)){
                            proto.values << sm[1];
                        } else if(std::regex_match(tok, sm, arg1) || 
                            std::regex_match(tok, sm, arg2)
                        ){
                            proto.attrs[sm[1]] = sm[2];
                        } else {
                            proto.values << tok;
                        }
                    }
                    
                    blocks.top()->push_back(std::move(proto));
                }

                switch(blk){
                case Block::Push:
                    {
                        line_t*  last    = &blocks.top()->back();
                        blocks << &last->sublines;
                    }
                    break;
                case Block::Pop:
                    blocks.pop();
                    break;
                default:
                    break;
                }
            }
        }
        catch(std::regex_error& ex)   // just to swallow...
        {
            return unexpected(parseCode(ex.code()));
        }
        
        return ret;
    }

    file_x      loadB3File(const std::filesystem::path& pth)
    {
        std::ifstream   fin(pth);
        if(!fin.good())
            return errors::cant_open_read();
        return loadB3(fin);
    }
    
    file_x      loadB3Buffer(std::string_view sv)
    {
        std::string data(sv);
        std::istringstream  fin(data);
        //std::istringstream  fin(sv); // not yet available
        
        return loadB3(fin);
    }
    
}
