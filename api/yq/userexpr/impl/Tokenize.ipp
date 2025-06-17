////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tokenize.hpp"

#include <yq/text/chars.hpp>
#include <yq/text/format32.hpp>

//#include <0/basic/TextUtils.hpp>
//#include <0/basic/TextUtils32.hpp>
#include <yq/userexpr/impl/OpData.hpp>
#include <yq/userexpr/impl/Repo.hpp>
#include <yq/userexpr/impl/Symbol.hpp>
#include <yq/userexpr/impl/Token.hpp>


namespace yq::expr {

    Token   token(std::u32string_view in)
    {
        static const Repo& _r = repo();
        
        Token         ret{};
        if(in.empty())
            return ret;
            
        size_t&     cnt = ret.length;
        char32_t    ch  = in[0];
        
        //  white space
        if(is_space(ch)){
            ret.category	= SymCategory::Space;
            ret.kind		= SymKind::None;
            for(cnt = 1; cnt<in.size(); ++cnt){
                if(!is_space(in[cnt]))
                    break;
            }
            return ret;
        }
        
        //  text identifier
        if(is_alpha(ch) || (_r.punctuation_can_start_text() && _r.is_punct_text(ch))){
            ret.category	= SymCategory::Text;
            ret.kind		= SymKind::None;
            for(cnt=1; cnt<in.size(); ++cnt){
                if(is_alpha(in[cnt]))
                    continue;
                if(_r.digits_in_text() && is_digit(in[cnt]))
                    continue;
                if(_r.is_punct_text(in[cnt]))
                    continue;
                if((in[cnt] == '.') && (cnt+1<in.size()) && is_alpha(in[cnt+1])) // allow for a.x syntax
                    continue;
                break;
            }
            return ret;
        } //    end of alpha

        char32_t    nx  = (in.size() > 1) ? in[1] : '\0';
        
        //  It's a NUMBER
        if(is_digit(ch) || ((ch == '.') && is_digit(nx))){
        
            if( (ch == '0') && ((nx == 'x') || (nx == 'X'))){
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Hexadecimal;
                //  it's a hex constant
                for(cnt=2; cnt<in.size(); ++cnt){
                    if(!is_xdigit(in[cnt]))
                        break;
                }
                return ret;
            }
            
            if((ch == '0') && is_digit(nx)){
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Octal;
                
                //  it's an octal constant
                for(cnt=2; cnt<in.size(); ++cnt){
                    if(!is_digit(in[cnt]))
                        break;
                }
                
                return ret;
            }
            
            
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
            
            if(decimal.first || exponent.first){
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Float;
            } else {
                ret.category	= SymCategory::Value;
                ret.kind		= SymKind::Integer;
            }
            
            return ret;
        }   // end of value test
        
        
        if(is_punct(ch)){
            ret.category	= SymCategory::Operator;
            
            size_t cc = 1;
            for(; cc<in.size(); ++cc)
                if(!is_punct(in[cc]))
                    break;
            
            size_t  lc = 0;
            for(; lc<cc; ++lc){
                std::u32string_view part    = in.substr(0,lc+1);
                if(!_r.has_operator(part))
                    break;
            }

			const OpData* op = _r.operator_(in.substr(0, lc));
			if(op){
                ret.category    = op->category;
                ret.kind        = op->kind;
            }

            cnt     = lc ? lc : 1;
            return ret;
        }
        
        return Token{ .category=SymCategory::Error, .length=1 };
    }


    Expect<SymVector>   tokenize(std::string_view input)
    {
        std::u32string  u32 = to_u32string(input);
        return tokenize(u32);
    }
    
    Expect<SymVector>   tokenize(std::u32string_view input)
    {
        SymVector   ret;
        std::error_code ec  = tokenize(input, ret);
        if(ec != std::error_code())
            return unexpected(ec);
        return ret;
    }

    std::error_code  tokenize(std::u32string_view input, SymVector& tokens)
    {
        return tokenize(input, [&](SymCode c, std::u32string_view s) -> std::error_code {
            tokens.push_back(Symbol{ 
                    .text = std::u32string(s),
					.category = c.category,
					.kind = c.kind
				});
            return std::error_code();
        });
    }
    
    std::error_code  tokenize(std::string_view input, SymVector& tokens)
    {
        std::u32string  u32 = to_u32string(input);
        return tokenize(u32, tokens);
    }
        
    std::error_code  tokenize(std::u32string_view input, TokenFN&&fn)
    {
        if(!fn){
            return errors::bad_argument();
        }
        
        for(std::u32string_view i=input; !i.empty(); ){
            Token   t   = token(i);
            if((t.category == SymCategory::Error) || (t.length == 0)){
                return errors::bad_argument();
            }
            
            fn({.category=t.category, .kind = t.kind}, i.substr(0, t.length));
            i = i.substr(t.length);
        }
        return std::error_code();
    }
    
    std::error_code  tokenize(std::string_view input, TokenFN&& fn)
    {
        std::u32string      u32 = to_u32string(input);
        return tokenize(u32, std::move(fn));
    }
}
