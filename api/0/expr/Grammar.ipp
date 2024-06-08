////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Grammar.hpp"
#include <0/basic/TextUtils.hpp>

namespace yq::expr {
    Grammar::Grammar()
    {
    }
    
    Grammar::~Grammar()
    {
    }

    void    Grammar::add_punct_text(char32_t ch)
    {
        m_punctText.insert(ch);
    }

    Token   Grammar::next_token(std::u32string_view in) const
    {
        if(in.empty())
            return Token{};
            
        Token       ret;
        size_t&     cnt = ret.len;
        char32_t    ch  = in[0];
        
        //  white space
        if(is_space(ch)){
            ret.type    = SymType::Space;
            for(cnt = 1; cnt<in.size(); ++cnt){
                if(!is_space(in[cnt]))
                    break;
            }
            return ret;
        }
        
        //  text identifier
        if(is_alpha(ch) || (m_punctStartText && m_punctText.contains(ch))){
            ret.type    = SymType::Text;
            for(cnt=1; cnt<in.size(); ++cnt){
                if(is_alpha(in[cnt]))
                    continue;
                if(m_digitsText && is_digit(in[cnt]))
                    continue;
                if(m_punctText.contains(in[cnt]))
                    continue;
                break;
            }
            return ret;
        } //    end of alpha

        char32_t    nx  = (in.size() > 1) ? in[1] : '\0';
        
        //  It's a NUMBER
        if(is_digit(ch) || ((ch == '.') && is_digit(nx))){
            ret.type    = SymType::Value;
        
            if( (ch == '0') && ((nx == 'x') || (nx == 'X'))){
                //  it's a hex constant
                for(cnt=2; cnt<in.size(); ++cnt){
                    if(!is_xdigit(in[cnt]))
                        break;
                }
                return ret;
            }
            
            if((ch == '0') && is_digit(nx)){
                //  it's an octal constant
                for(cnt=2; cnt<in.size(); ++cnt){
                    if(!is_digit(in[cnt]))
                        break;
                }
                
                return ret;
            }
            
            using   feature_t = std::pair<bool,size_t>;
            
            //  Ordinary number (may or may not be floating point)
            feature_t  decimal     = {};
            feature_t  exponent    = {};
            feature_t  expsign     = {};
            
            if(ch == '.')
                decimal = { true, 0 };
                
            for(cnt=1;cnt<in.size();++cnt){
            
                //  numbers are always allowed
                if(is_digit(in[cnt]))
                    continue;
                    
                //  decimal... one only
                if(in[cnt] == '.'){
                
                    //  but not after exponents
                    if(exponent.first){
                        if(exponent.second == cnt-1) {
                            cnt = exponent.second;
                        }
                        if(expsign.first && (expsign.second == cnt-1)){
                            cnt = exponent.second;
                        }
                        break;
                    }

                    // duplicate...nope
                    if(decimal.first)
                        break;

                    // record decimal
                    decimal  = { true, cnt };
                    continue;
                }
                
                //      alphabet?
                if(is_alpha(in[cnt])){

                    //  we're already in an exponent?
                    if(exponent.first){
                        //  already marked it exponent, abort
                        
                        if(exponent.second == cnt-1){ // immediately after exponent, scrub out exponent
                            cnt = exponent.second;
                        }
                            
                            //  there was a sign instead?  scrub
                        if(expsign.first && (expsign.second == cnt-1)){   // sign is bad too
                            cnt = exponent.second;
                        }
                        break;
                    }
                    
                    //  if it's exponent character, record
                    if((in[cnt] == 'e') || (in[cnt] == 'E')){
                        exponent    = { true, cnt };
                        continue;
                    }
                    
                    //  otherwise, it's not a value, break
                    break;
                }
                
                if(exponent.first && ((in[cnt] == '-') || (in[cnt] == '+'))){
                    if(expsign.first){
                        if(cnt-1 == expsign.second)
                            cnt = exponent.second;
                        break;
                    }
                    if(cnt-1 != exponent.second){
                        break;
                    }
                    
                    //  It's a sign!
                    expsign = { true, cnt };
                    continue;
                }
                
                //  ANY OTHER CHARACTER BREAKS THIS
                break;
            }
            
            return ret;
        }   // end of value test
        
        
        if(is_punct(ch)){
            ret.type    = SymType::Operator;
            
            for(cnt=1; cnt<in.size(); ++cnt){
                if(!is_punct(in[cnt]))  // non punctuation break
                    break;

                std::u32string_view part    = in.substr(0,cnt);
                if(!m_operators.contains(part))
                    break;
            }
            
            return ret;
        }
        
        
        return Token{
            .len    = 1,
            .type   = SymType::Error
        };
    }
}
