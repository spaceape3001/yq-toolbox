////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "Streamline.hpp"
#include <yq-toolbox/userexpr/impl/Repo.hpp>
#include <yq-toolbox/userexpr/impl/Symbol.hpp>

namespace yq::expr {

    std::error_code      s_constants(SymVector&syms)
    {
        static const Repo& _r = repo();
        for(Symbol& sym : syms){
            if(sym.category != SymCategory::Text)
                continue;
            if(sym.kind != SymKind::None)
                continue;
            if(_r.has_constant(sym.text)){
                sym.kind    = SymKind::Constant;
            } else {
                sym.kind    = SymKind::Variable;
            }
        }
        return {};
    }

    std::error_code s_functions(SymVector&syms)
    {
        Symbol* last    = nullptr;
		for(auto itr = syms.begin(); itr != syms.end(); last=&*itr, ++itr){
            if( itr -> category != SymCategory::Open)
                continue;
            if(!last)
                continue;
            if(last -> category != SymCategory::Text)
                continue;

            switch(itr->kind){
            case SymKind::Generic:
                last -> kind = SymKind::Function;
                break;
                
            //  folding it into the function
            //case SymKind::Tuple:
                //last -> kind = SymKind::Constructor;
                //break;
            default:
                break;
            }
		}
        return {};
    }

    std::error_code s_signs(SymVector&syms)
    {
		SymCode		last	= {};
		for(auto itr = syms.begin(); itr != syms.end(); last=*itr, ++itr){
			if((itr -> text != U"-") && (itr->text != U"+"))
				continue;
			// This symbol is "-" negative
			if(!expr::is_starting_term(last))
				continue;
			auto jtr = itr + 1;
			if(jtr == syms.end())
				continue;
			if(jtr -> category != SymCategory::Value)
				continue;
			if(!((jtr -> kind == SymKind::Integer) ||  (jtr -> kind == SymKind::Float))){
                if(itr->text == U"-"){
                    jtr -> kind = SymKind::Negate;
                    jtr -> text = U"negate";
                } else {
                    jtr -> kind = SymKind::Affirm;
                    jtr -> text = U"affirm";
                }
				continue;
			}
			
			jtr -> text	= itr->text + jtr->text;
			itr = syms.erase(itr);
		}
        return {};
    }


    std::error_code  streamline(SymVector& syms)
    {
        std::error_code ec;

        ec = s_signs(syms);
        if(ec != std::error_code())
            return ec;

        ec = s_functions(syms);
        if(ec != std::error_code())
            return ec;

        ec = s_constants(syms);
        if(ec != std::error_code())
            return ec;

        return {};
    }
}
