////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <ys/io/b3grammar.hpp>
#include <yq/errors.hpp>
#include <yq/text/chars.hpp>

#include <iostream>

namespace yq::errors {
    using blank_line    = error_db::entry<"Blank line">;
}

namespace yq::spatial {

    Expect<B3Line>  B3Line::decode(const char*& text, const char* end, uint32_t& line)
    {
        if(!text || !end)
            return errors::null_pointer();
    
        enum class Mode {
            Start   = 0,
            Comment,
            Entry,
            Gap,
            NewLine,
            Done
        };

        B3Line      ret;
        Mode        mode    = Mode::Start;
        char        last    = '\n';
        std::string snip;
        bool        done    = false;
        bool        quote   = false;
        
        auto process    = [&](){
            if(!snip.empty()){
                if(!is_blank(snip))
                    ret.tokens.push_back(std::move(snip));
                snip.clear();
            }
        };
        
        for(;(text < end) && !done; last = *text++){
            switch(*text){
            case '\n':
            case '\r':
                ++line;
                switch(mode){
                case Mode::Start:
                case Mode::Comment:
                    ret.indent  = 0;
                    mode    = Mode::Start;
                    break;
                case Mode::Gap:
                    if(last == '\\'){
                        mode    = Mode::NewLine;
                    } else {
                        mode    = Mode::Done;
                    }
                    break;
                case Mode::NewLine:
                    break;
                case Mode::Entry:
                    process();
                    if(last == '\\'){
                        mode    = Mode::NewLine;
                    } else
                        mode    = Mode::Done;
                    break;
                default:
                    break;
                }
                break;
            case '#':
                switch(mode){
                case Mode::Start:
                    mode    = Mode::Comment;
                    break;
                case Mode::Comment:
                    break;
                case Mode::Gap:
                    mode    = Mode::Done;
                    if(last) 
                        --text;
                    break;
                case Mode::NewLine:
                    mode    = Mode::Done;
                    break;
                case Mode::Entry:
                    snip += '#';
                    break;
                default:
                    break;
                }
                break;
                
            case ' ':
            case '\t':
                switch(mode){
                case Mode::Start:
                    ++ret.indent;
                    break;
                case Mode::Comment:
                case Mode::Gap:
                    break;
                case Mode::NewLine:
                    mode    = Mode::Gap;
                    break;
                case Mode::Entry:
                    if(quote || (last == '\\')){
                        snip += *text;
                        break;
                    }
                    
                    mode    = Mode::Gap;
                    process();
                    break;
                default:
                    break;
                }
                break;
            case '"':
                switch(mode){
                case Mode::Comment:
                    break;
                case Mode::Start:
                case Mode::Gap:
                case Mode::NewLine:
                    mode        = Mode::Entry;
                    quote       = true;
                    ret.line    = line;
                    break;
                case Mode::Entry:
                    if(last == '\\'){
                        snip += '"';
                    } else {
                        quote   = !quote;
                    }
                    break;
                default:
                    break;
                }
                break;
            case '\\':
                switch(mode){
                case Mode::Start:
                    mode    = Mode::Entry;
                    break;
                case Mode::Comment:
                    break;
                case Mode::Gap:
                    mode    = Mode::Entry;
                    break;
                case Mode::NewLine:
                    mode    = Mode::Entry;
                    break;
                default:
                    if(last == '\\')
                        snip += '\\';
                    break;
                }
                break;
            default:
                if(*text < ' ') // some stupid control
                    break;
                
                switch(mode){
                case Mode::Start:
                    snip       += *text;
                    mode        = Mode::Entry;
                    ret.line    = line;
                    quote       = false;
                    break;
                case Mode::Comment:
                    break;
                case Mode::Gap:
                case Mode::NewLine:
                    snip       += *text;
                    mode        = Mode::Entry;
                    break;
                case Mode::Entry:
                    snip       += *text;
                    break;
                default:
                    break;
                }
            }
        }
        
        if(!snip.empty() && !is_blank(snip))
            ret.tokens.push_back(std::move(snip));
        return ret;
        

    }

    Expect<B3Line>  B3Line::decode(std::string_view sv)
    {
        const char* begin   = sv.data();
        uint32_t    line    = 0;
        return decode(begin, begin+sv.size(), line);
    }
}
