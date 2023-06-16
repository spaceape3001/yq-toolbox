////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Generator.hpp"
#include "GeneratorImpl.hpp"
#include "AnyArgHelper.hpp"
#include <basic/IgCase.hpp>
#include <basic/Logging.hpp>

namespace yq {
    struct GeneratorInfo::Repo {
        std::vector<const GeneratorInfo*>                           all;
        std::map<std::string_view, const GeneratorInfo*, IgCase>    byName;
    };
    
    GeneratorInfo::Repo*    GeneratorInfo::newRepo()
    {
        return new Repo;
    }

    
    const std::vector<const GeneratorInfo*>&     GeneratorInfo::all(Repo& r)
    {
        return r.all;
    }
    
    const GeneratorInfo*                         GeneratorInfo::find(Repo&r, std::string_view k)
    {
        auto i = r.byName.find(k);
        if(i != r.byName.end())
            return i->second;
        return nullptr;
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

    GeneratorInfo::GeneratorInfo(std::string_view zName, const std::source_location& sl, options_t opts) : Meta(zName, sl)
    {
        set_options(opts | GENERATOR);
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

    void    GeneratorInfo::fill_argument_info(size_t n, std::string_view zName, std::string_view zDescription, options_t opts)
    {
        if(n < m_arguments.size()){
            ArgInfo*    ai  = const_cast<ArgInfo*>(m_arguments[n]);
            Meta::Writer w{ ai };
            if( ai->name().empty() && !zName.empty())
                w.name(zName);
            if( ai->description().empty() && !zDescription.empty())
                w.description(zDescription);
            if(opts)
                w.options(opts);
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

    GeneratorInfo::Writer  GeneratorInfo::Writer::argument(std::string_view zName, std::string_view zDescription, options_t opts)
    {
        if(Meta::Writer::m_meta){
            static_cast<GeneratorInfo*>(Meta::Writer::m_meta) -> fill_argument_info(m_arg, zName, zDescription, opts);
            ++m_arg;
        }
        return *this;
    }
    
}
