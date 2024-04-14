////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/DelayInit.hpp>
#include <0/basic/Logging.hpp>
#include <0/io/StreamOps.hpp>
#include <0/meta/MetaRepo.hpp>
#include <0/meta/TypeInfo.hpp>
#include <0/meta/ReservedIDs.hpp>
#include <cassert>

namespace yq {


    struct EmptyType : public TypeInfo {
    
        EmptyType(id_t i, const std::source_location& sl = std::source_location::current()) : TypeInfo( i ? "Any" : "Void", sl, i) 
        {
            m_copyB     = [](DataBlock&, const DataBlock&) {};
            m_copyR     = [](DataBlock&, const void*) {};
            m_ctorCopyR = [](DataBlock&, const void*) {};
            m_ctorCopyB = [](DataBlock&, const DataBlock&) {};
            m_ctorMove  = [](DataBlock&, DataBlock&&) {};
            m_dtor      = [](DataBlock&) {};
            m_equal     = [](const DataBlock&, const DataBlock&) -> bool { return true; };
            m_moveB     = [](DataBlock&, DataBlock&&) {};
            if(i)
                m_print = [](Stream& s, const void*) { s << "(wildcard)"; };
            else
                m_print = [](Stream& s, const void*) { s << "(empty)"; };
        }
        
        ~EmptyType(){}
    };
        
    const TypeInfo&        invalid()
    {
        static EmptyType*  s_ret = new EmptyType(MT_Invalid);
        return *s_ret;
    }
    
    const TypeInfo&        any()
    {
        static EmptyType*  s_ret = new EmptyType(MT_Any);
        return *s_ret;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    const std::vector<const TypeInfo*>&   TypeInfo::all()
    {
        assert(thread_safe_read());
        return repo().types.all;
    }
    
    const TypeInfo*                  TypeInfo::find(id_t i)
    {
        assert(thread_safe_read());
        const Meta* m   = repo().all.value(i, nullptr);
        return (m && m->is_type()) ? static_cast<const TypeInfo*>(m) : nullptr;
    }
    
    const TypeInfo*                  TypeInfo::find(std::string_view sv)
    {
        assert(thread_safe_read());
        return repo().types.lut.first(sv, nullptr);
    }

    std::vector<const TypeInfo*>          TypeInfo::find_all(const string_set_t& types, bool noisy)
    {
        std::vector<const TypeInfo*> ret;
        auto&   r   = repo().types.lut;
        for(const std::string& s : types){
            if(s.empty())
                continue;
                
            const TypeInfo* ti  = r.first(s);
            if(!ti){
                if(noisy)
                    yWarning() << "Unable to find type info for: " << s;
                continue;
            }
            ret.push_back(ti);
        }
        return ret;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    TypeInfo::TypeInfo(std::string_view zName, const std::source_location& sl, id_t i) : CompoundInfo(zName, sl, nullptr, i)
    {
        set(Flag::TYPE);
        
        Repo&   r  = repo();
        assert("no duplicate typenames!" && !r.types.lut.has(name())); 
        
        r.types << this;
    }

    TypeInfo::~TypeInfo()
    {
        //  should never be used....
    }

    void            TypeInfo::add_alias(std::string_view sz)
    {
        Meta::add_alias(sz);
        repo().types.add_mapping(sz, this);
    }
    
    void            TypeInfo::add_printer(std::string_view k, FNFormat fn)
    {
        if(fn){
            if(k.empty() || !m_print)
                m_print   = fn;
            if(!k.empty())
                m_printers[k]   = fn;
        }
    }
    
    std::error_code        TypeInfo::copy(void*dst, const void*src) const
    {
        if(!m_copyRR)
            return errors::no_handler();
        if(!dst)
            return errors::null_destination();
        if(!src)
            return errors::null_source();
        m_copyRR(dst, src);
        return errors::none();
    }
    
    std::error_code        TypeInfo::copy(void*dst, const void*src, const TypeInfo& srcType) const
    {
        if(!dst)
            return errors::null_destination();
        if(!src)
            return errors::null_source();

        if(id() == srcType.id()){
            if(!m_copyRR)
                return errors::no_handler();
            m_copyRR(dst, src);
            return errors::none();
        }

        FNConvert   cvt = srcType.m_convert.get(this, nullptr);
        if(!cvt)
            return errors::no_conversion_handler();
        return cvt(dst, src);
    }

    size_t                              TypeInfo::method_count() const
    {
        return m_methods.all.size();
    }

    const std::vector<const MethodInfo*>&    TypeInfo::methods() const
    {
        return m_methods.all;
    }

    TypeInfo::FNFormat        TypeInfo::printer(std::string_view k) const
    {
        if(!k.empty()){
            auto i = m_printers.find(k);
            if((i != m_printers.end()) && i->second) 
                return i->second;
        }
        if(m_print)
            return m_print;
        return m_write;
    }
    
    const std::vector<const PropertyInfo*>&  TypeInfo::properties() const
    {
        return m_properties.all;
    }

    size_t                              TypeInfo::property_count() const
    {
        return m_properties.all.size();
    }

    void    TypeInfo::sweep_impl() 
    {
        CompoundInfo::sweep_impl();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    /*! \brief Converts meta to type, if it's valid
    
        \return TypeInfo pointer, if valid, NULL otherwise
    */
    const TypeInfo* to_type(const Meta* m)
    {
        return (m && m->is_type()) ? static_cast<const TypeInfo*>(m) : nullptr;
    }
    
    /*! \brief Converts meta to type, if it's valid
    
        \return TypeInfo pointer, if valid, NULL otherwise
    */
    TypeInfo* to_type(Meta* m)
    {
        return (m && m->is_type()) ? static_cast<TypeInfo*>(m) : nullptr;
    }
}

YQ_INVOKE(
    yq::any();
    yq::invalid();
)


