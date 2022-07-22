////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Enum.hpp"
#include <basic/TextUtils.hpp>
#include <cassert>
#include <optional>

namespace yq {
    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  ENUMERATION
    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    EnumDef::EnumDef(const char* name, const char* def) : 
        m_name(name), m_defValue(-1)
    {
        int             val         = 0;
        bool            first       = true;

        const char*    begin   = def;
        const char*    c       = begin;
        const char*    s       = nullptr;
        const char*    end     = c + strlen(def);
        
        bool    cmtcxx          = false;
        bool    cmtc            = false;
        char    last            = ' ';
        bool    alpha           = false;
        bool    skip            = false;    // skip to next significant thing
        
        std::string_view        k, v;
        
        enum mode_t { 
            LINE,   //  new line (or start)
            KEY,
            VALUE
        };
        
        mode_t                  mode    = LINE;
        
        
        auto    mkey     = [&]() {
            if(s){
                k       = std::string_view(s, c-s);
                s       = nullptr;
            }
        };
        
        
        auto    mval    = [&]() {
            if(s){
                v       = std::string_view(s, c-s);
                s       = nullptr;
            }
        };
        
        
            // Subroutine to process the enum into the maps
        auto    proc    = [&]() {
            if(v.empty() && k.empty())
                return ;
        
            if(!v.empty()){
                if(alpha){
                    auto    itr = m_name2value.find(v);
                    assert(itr != m_name2value.end());  // shouldn't ever trigger, as it was compilable code
                    if(itr != m_name2value.end())
                        val = itr -> second;
                } else {
                    auto ir = to_integer(v);
                    assert(ir.good);                    // shouldn't ever trigger, as it was compilable code
                    val  = ir.value;
                }
            }

            m_name2value[k]     = val;
            m_value2name[val]   = k;
            
            if(first){
                m_defValue  = val;
                first       = false;
            }
            
            ++val;
            mode    = LINE;
            k       = {};
            v       = {};
            alpha   = false;
        };
        

        //  Iterate....
        for(;c<end;++c){
            switch(*c){
            case '/':
                if(cmtcxx)
                    break;
                if(cmtc && (last == '*')){
                    cmtc    = false;
                    break;
                }
                if(cmtc)
                    break;
                if(last == '/')
                    cmtcxx  = true;
                break;
            case '*':
                if(cmtc || cmtcxx)
                    break;
                if(last == '/')
                    cmtc    = true;
                break;
            case '\n':
            case '\r':
                if(cmtcxx)
                    cmtcxx  = false;
                break;
            case ',':
                if(cmtc || cmtcxx)
                    break;
                
                switch(mode){
                case LINE:
                    break;
                case KEY:
                    mkey();
                    break;
                case VALUE:
                    mval();
                    break;
                }
                skip    = false;
                proc();
                break;

            case '=':
                if(cmtc || cmtcxx)
                    break;
                
                mkey();
                mode    = VALUE;
                skip    = false;
                break;
                
            case '_':
            case '-':
            default:
                if(cmtc || cmtcxx)
                    break;
                
                if(isspace(*c)){
                    if(s){
                        switch(mode){
                        case KEY:
                            mkey();
                            break;
                        case VALUE:
                            mval();
                            break;
                        default:
                            break;
                        }
                    }
                } else {
                    if(s && (mode == VALUE)){
                        if(is_alpha(*c))
                            alpha   = true;
                    }
                    if(!s && !skip){
                        s   = c;
                        if(mode == LINE)
                            mode    = KEY;
                        skip    = true;
                    }
                }
                break;
            }
            
            last = *c;
        }
        
        switch(mode){
        case KEY:
            mkey();
            break;
        case VALUE:
            mval();
            break;
        default:
            break;
        }
        
        proc();
        
        m_sorted    = m_keys;
        m_sorted.sort(is_less_igCase);
        m_ordered   = m_keys;
        m_ordered.sort([&](std::string_view  a, std::string_view b) -> bool {
            return m_name2value.get(a) < m_name2value.get(b);
        });
    }


    bool    EnumDef::has_key(std::string_view key) const
    {
        return m_name2value.has(std::string(key));
    }

    bool    EnumDef::has_value(int v) const
    {
        return m_value2name.has(v);
    }


    string_view_r EnumDef::key_of(int v) const
    {
        return m_value2name(v);
    }


    int     EnumDef::minimum_value() const
    {
        if(m_value2name.empty())
            return -1;
        return m_value2name.begin()->first;
    }

    int     EnumDef::maximum_value() const
    {
        if(m_value2name.empty())
            return -1;
        return m_value2name.rbegin()->first;
    }


    Vector<int>  EnumDef::parse_comma_list(std::string_view str)  const
    {
        Vector<int>  ret;
        ret.reserve(count_characters(str, ','));
        vsplit(str, ',', [&](std::string_view  s){
            auto itr = m_name2value.find(trimmed(s));
            if(itr != m_name2value.end())
                ret.push_back(itr->second);
        });
        return ret;
    }

    std::string     EnumDef::make_comma_list(const Vector<int>&vals) const
    {
        std::vector<std::string_view>   bits;
        for(int v : vals){
            auto itr = m_value2name.find(v);
            if(itr != m_value2name.end())
                bits.push_back(itr->second);
        }
        if(!bits.empty())
            return join(bits, ",");
        else
            return std::string();
    }

    Vector<int>             EnumDef::all_values() const
    {
        return m_value2name.keys();
    }

    Enum            EnumDef::make_enum(int v) const
    {
        return Enum(this, v);
    }


    int_r     EnumDef::value_of(std::string_view  key) const
    {
        return m_name2value(key);
    }




    //  ============================================================================


    Enum::Enum(const EnumDef*def, int v) : m_def(def)
    {
        assert(def);
        if(def){
            if(def->has_value(v)){
                m_value = v;
            } else {
                m_value = def->default_value();
            }
        } else {
            m_value     = -1;
        }
    }

    std::string_view Enum::key() const
    {
        if(m_def){
            return m_def->key_of(m_value);
        } else {
            return std::string_view();
        }
    }

    Enum&  Enum::operator=(int v)
    {
        if(m_def){
            if(m_def->has_value(v)){
                m_value     = v;
            }
        }
        return *this;
    }
}

