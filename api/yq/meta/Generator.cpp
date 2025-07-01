////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Generator.hpp"
#include "GeneratorImpl.hpp"
#include "AnyArgHelper.hpp"
#include <yq/container/vector_utils.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/core/Logging.hpp>

namespace yq {
    struct GeneratorMeta::Repo {
        std::string                                                 name;
        std::vector<const GeneratorMeta*>                           all;
        std::map<std::string_view, const GeneratorMeta*, IgCase>    byName;
        Repo*                                                       next    = nullptr;
    };

    GeneratorMeta::Repo*    GeneratorMeta::addRepo(Repo* r)
    {
        static Repo*        s_top   = nullptr;
        if(r){
            r->next = s_top;
            s_top   = r;
        }
        return s_top;
    }
    
    GeneratorMeta::Repo*    GeneratorMeta::newRepo(const char* name)
    {
        Repo*r  = new Repo;
        r->name = name;
        addRepo(r);
        return r;
    }

    
    const std::vector<const GeneratorMeta*>&     GeneratorMeta::all(const Repo& r)
    {
        return r.all;
    }
    
    const GeneratorMeta*                         GeneratorMeta::find(const Repo&r, std::string_view k)
    {
        auto i = r.byName.find(k);
        if(i != r.byName.end())
            return i->second;
        return nullptr;
    }

    std::vector<std::string_view> GeneratorMeta::generator_types()
    {
        std::vector<std::string_view>    ret;
        for(Repo* r = addRepo(nullptr);r; r = r -> next)
            ret.push_back(r->name);
        return ret;
    }
    
    void                                         GeneratorMeta::register_me(Repo&r, const GeneratorMeta*gi)
    {
        r.all.push_back(gi);
        auto [i,f]  = r.byName.try_emplace(gi->name(), gi);
        if(!f){
            yCritical() << "Duplicate generators named: " << gi->name();
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////

    GeneratorMeta::GeneratorMeta(std::string_view zName, const std::source_location& sl) : Meta(zName, sl)
    {
        set(Flag::GENERATOR);
    }

    std::error_code         GeneratorMeta::create(void*ret, std::span<const Any> args) const
    {
        if(args.size() < m_arguments.size())
            return errors::insufficient_arguments();
        
        AnyArgHelper    aaa;
        std::error_code ec  = aaa.construct(span(m_arguments), args);
        if(ec)
            return ec;
        
        return _create(ret, aaa);
    }

    void    GeneratorMeta::fill_argument_info(size_t n, std::string_view zName, std::string_view zDescription)
    {
        if(n < m_arguments.size()){
            ArgMeta*    ai  = const_cast<ArgMeta*>(m_arguments[n]);
            Meta::Writer w{ ai };
            if( ai->name().empty() && !zName.empty())
                w.name(zName);
            if( ai->description().empty() && !zDescription.empty())
                w.description(zDescription);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    GeneratorMeta::Writer::Writer(GeneratorMeta* obj) : Meta::Writer(obj) 
    {
        assert(obj);
    }
    
    GeneratorMeta::Writer::Writer(GeneratorMeta& obj) : Writer(&obj)
    {
    }

    GeneratorMeta::Writer  GeneratorMeta::Writer::argument(std::string_view zName, std::string_view zDescription)
    {
        if(Meta::Writer::m_meta){
            static_cast<GeneratorMeta*>(Meta::Writer::m_meta) -> fill_argument_info(m_arg, zName, zDescription);
            ++m_arg;
        }
        return *this;
    }
    
}
