////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "FunctionInstruction.hpp"

#include <yq/errors.hpp>
#include <yq/container/Stack.hpp>

#include <yq/core/Any.hpp>
#include <yq/core/Logging.hpp>
//#include <0/basic/TextUtils.hpp>
//#include <0/basic/TextUtils32.hpp>
#include <yq/userexpr/Analysis.hpp>
#include <yq/userexpr/impl/Repo.hpp>
#include <yq/userexpr/impl/SymData.hpp>
#include <yq/meta/ArgInfo.hpp>
#include <yq/meta/ConstructorInfo.hpp>
#include <yq/meta/GlobalInfo.hpp>
#include <yq/meta/MethodInfo.hpp>
#include <yq/meta/OperatorInfo.hpp>
#include <yq/meta/TypeInfo.hpp>

namespace yq::expr {
        /*
        
            Functions....
            
            *)  Actual Functions (Type -- first arg, Globals, Repo)

            *)  Methods on Type (first arg)

            *)  Properties (getters)
            
                For instance, geodetic & latitude,
                
                    latitude(geo)
            
            *)  Construction
            
                degree(20)
                vec2d(x,y)
                
            *)  Conversions
            
            
            
        */

    using conditional_t     = std::variant<std::monostate, std::error_code>;
    using span_typeinfo_t   = std::span<const TypeInfo*>;

    struct converter_t {
        const TypeInfo* type    = nullptr;
    };

    struct default_t {
        const TypeInfo* type    = nullptr;
    };

    
    struct MethodScanner {
    
        using function_t            = std::variant<std::monostate, const MethodInfo*, const PropertyInfo*, converter_t, default_t>;
        using scored_function_t     = std::pair<function_t, int>;
    
        std::vector<scored_function_t>  scored;
        std::span<const TypeInfo*>      types;
        
        MethodScanner(std::span<const TypeInfo*> _types) :  types(_types) 
        {
        }

        void        sort()
        {
            std::stable_sort(scored.begin(), scored.end(), [](scored_function_t a, scored_function_t b) -> bool {
                return a.second < b.second;
            });
        }
        
        int         score(const MethodInfo* mi, bool dynamic_allowed=false) const
        {
            int     ret = -1;
            if(mi -> is_static()){
                ret = mi->type_match(types);
            } else if(dynamic_allowed){
                ret = mi->type_match(types.subspan(1));
            }
            return ret;
        }

        size_t        constructors(const TypeInfo& type)
        {
            size_t  start = scored.size();
            for(const ConstructorInfo* ci : type.constructors()){
                int     sc  = score(ci);
                if(sc >= 0){
                    scored.push_back({ (const MethodInfo*) ci, sc });
                }
            }
            return scored.size() - start;
        }

        bool         conversions(const TypeInfo& type, std::string_view k)
        {
            const TypeInfo*     ti  = TypeInfo::find(STEM, k);
            if(ti){
                scored.push_back({converter_t{ti}, 1});
                return true;
            } else {
                return false;
            }
        }

        size_t        functions(repo_t, string_view_t k)
        {
            static const Repo& _r  = Repo::instance();
            size_t  start = scored.size();
            _r.all_functions(k, [&](const MethodInfo* mi){
                int     sc  = score(mi);
                if(sc >= 0) {
                    scored.push_back({mi, sc});
                }
            });
            return scored.size() - start;
        }
        
        size_t        functions(global_t, std::string_view k)
        {
            static const GlobalInfo& _g = GlobalInfo::instance();
            size_t  start = scored.size();
            _g.all_functions(k, [&](const MethodInfo* mi){
                int sc  = score(mi);
                if(sc >= 0){
                    scored.push_back({mi, sc});
                }
            });
            return scored.size() - start;
        }
        
        size_t     methods(const TypeInfo& type, std::string_view k)
        {
            size_t  start = scored.size();
            type.all_functions(k, [&](const MethodInfo* mi){
                int sc  = score(mi, true);
                if(sc >= 0){
                    scored.push_back({mi, sc});
                }
            });
            return scored.size() - start;
        }
        
        bool      properties(const TypeInfo& type, std::string_view k)
        {
            const PropertyInfo* pi  = type.property(k);
            if(pi){
                scored.push_back({pi, 0});
                return true;
            } else
                return false;
        }
        
        
        bool        default_(const TypeInfo* type)
        {
            if(type){
                scored.push_back({default_t{type}, 0});
                return true;
            } else
                return false;
        }
    };
    
    std::vector<const TypeInfo*>    extract_types(std::span<const Any> anys)
    {
        std::vector<const TypeInfo*>    ret;
        ret.reserve(anys.size());
        for(const Any& a : anys)
            ret.push_back(&a.type());
        return ret;
    }
    
    FunctionInstruction::FunctionInstruction(const SymData& sd) : 
        Instruction(sd.text), m_text8(to_string(sd.text)), m_argcnt(sd.argcnt),
        m_type(TypeInfo::find(STEM, m_text8))
    {
    }

    std::error_code     FunctionInstruction::execute(any_stack_t&values, Context&) const 
    {
        std::span<const Any>            args    = values.top_cspan(m_argcnt);
        std::vector<const TypeInfo*>    types   = extract_types(args);
        const TypeInfo*                 type0   = nullptr;
        
        struct {
            size_t      repo            = 0;
            size_t      global          = 0;
            size_t      methods         = 0;
            size_t      constructors    = 0;
            bool        default_        = false;
            bool        property        = false;
            bool        conversion      = false;
        } stat;

        MethodScanner       scanner(types);

        stat.repo               = scanner.functions(REPO, m_text);
        stat.global             = scanner.functions(GLOBAL, m_text8);
        
        if(m_argcnt){
            type0               = &values.top().type();
            stat.methods        = scanner.methods(*type0, m_text8);
            stat.constructors   = scanner.constructors(*type0);
        }
        
        if((m_argcnt == 0) && m_type){
            stat.default_       = scanner.default_(m_type);
        }
        
        if(m_argcnt == 1){
            stat.property       = scanner.properties(*type0, m_text8);
            stat.conversion     = scanner.conversions(*type0, m_text8);
        }
        
        scanner.sort();
        
        any_x     x;
        for(auto& fn : scanner.scored){
            if(auto p = std::get_if<const MethodInfo*>(&fn.first)){
                const MethodInfo* mi = *p;
                if(!mi)
                    continue;
                if(mi->is_static()){
                    x   = mi->invoke(args);
                } else {
                    x   = mi->invoke(args[0].raw_ptr(), args.subspan(1));
                }
            }
            
            if(auto p = std::get_if<const PropertyInfo*>(&fn.first)){
                const PropertyInfo* pi = *p;
                if(!pi)
                    continue;
                x   = pi->get(args[0].raw_ptr());
            }
            
            if(auto p = std::get_if<converter_t>(&fn.first)){
                const TypeInfo* ti  = p->type;
                if(!ti)
                    continue;
                x   = args[0].convert(*ti);
            }
            
            if(auto p = std::get_if<default_t>(&fn.first)){
                const TypeInfo* ti  = p->type;
                if(!ti)
                    continue;
                x   = Any(*ti);
            }
            
            if(x){
                values.pop_last(m_argcnt);
                values << *x;
                return {};
            }
        }
        
        yInfo() << 
           "Function " << m_text8 << (std::span<const TypeInfo*>) types << " could not resolve/execute with " << scanner.scored.size() << " candidate(s)\n"
           "   repo functions:   " << stat.repo << '\n' <<
           "   global functions: " << stat.global << '\n' <<
           "   type methods:     " << stat.methods << '\n' <<
           "   constructors:     " << stat.constructors << '\n' <<
           "   default?:         " << (stat.default_?"yes":"no") << "\n" <<
           "   property?:        " << (stat.property?"yes":"no") << "\n" <<
           "   conversion?:      " << (stat.conversion?"yes":"no") << "\n"
        ;
        
        
        return errors::bad_function();
    }
}
