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
#include <yq/basic/Logging.hpp>

namespace yq {
    struct GeneratorInfo::Repo {
        std::string                                                 name;
        std::vector<const GeneratorInfo*>                           all;
        std::map<std::string_view, const GeneratorInfo*, IgCase>    byName;
        Repo*                                                       next    = nullptr;
    };

    GeneratorInfo::Repo*    GeneratorInfo::addRepo(Repo* r)
    {
        static Repo*        s_top   = nullptr;
        if(r){
            r->next = s_top;
            s_top   = r;
        }
        return s_top;
    }
    
    GeneratorInfo::Repo*    GeneratorInfo::newRepo(const char* name)
    {
        Repo*r  = new Repo;
        r->name = name;
        addRepo(r);
        return r;
    }

    
    const std::vector<const GeneratorInfo*>&     GeneratorInfo::all(const Repo& r)
    {
        return r.all;
    }
    
    const GeneratorInfo*                         GeneratorInfo::find(const Repo&r, std::string_view k)
    {
        auto i = r.byName.find(k);
        if(i != r.byName.end())
            return i->second;
        return nullptr;
    }

    std::vector<std::string_view> GeneratorInfo::generator_types()
    {
        std::vector<std::string_view>    ret;
        for(Repo* r = addRepo(nullptr);r; r = r -> next)
            ret.push_back(r->name);
        return ret;
    }
    
    void                                         GeneratorInfo::register_me(Repo&r, const GeneratorInfo*gi)
    {
        r.all.push_back(gi);
        auto [i,f]  = r.byName.try_emplace(gi->name(), gi);
        if(!f){
            yCritical() << "Duplicate generators named: " << gi->name();
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////////

    GeneratorInfo::GeneratorInfo(std::string_view zName, const std::source_location& sl) : Meta(zName, sl)
    {
        set(Flag::GENERATOR);
    }

    std::error_code         GeneratorInfo::create(void*ret, std::span<const Any> args) const
    {
        if(args.size() < m_arguments.size())
            return errors::insufficient_arguments();
        
        AnyArgHelper    aaa;
        std::error_code ec  = aaa.construct(span(m_arguments), args);
        if(ec)
            return ec;
        
        return _create(ret, aaa);
    }

    void    GeneratorInfo::fill_argument_info(size_t n, std::string_view zName, std::string_view zDescription)
    {
        if(n < m_arguments.size()){
            ArgInfo*    ai  = const_cast<ArgInfo*>(m_arguments[n]);
            Meta::Writer w{ ai };
            if( ai->name().empty() && !zName.empty())
                w.name(zName);
            if( ai->description().empty() && !zDescription.empty())
                w.description(zDescription);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    GeneratorInfo::Writer::Writer(GeneratorInfo* obj) : Meta::Writer(obj) 
    {
        assert(obj);
    }
    
    GeneratorInfo::Writer::Writer(GeneratorInfo& obj) : Writer(&obj)
    {
    }

    GeneratorInfo::Writer  GeneratorInfo::Writer::argument(std::string_view zName, std::string_view zDescription)
    {
        if(Meta::Writer::m_meta){
            static_cast<GeneratorInfo*>(Meta::Writer::m_meta) -> fill_argument_info(m_arg, zName, zDescription);
            ++m_arg;
        }
        return *this;
    }
    
}
