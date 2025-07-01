////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/Any.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/core/Logging.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/meta/ConstructorInfo.hpp>
#include <yq/meta/MetaRepo.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <yq/meta/ReservedIDs.hpp>
#include <yq/container/initlist_utils.hpp>
#include <cassert>

namespace yq {


    struct EmptyType : public TypeMeta {
    
        EmptyType(id_t i, const std::source_location& sl = std::source_location::current()) : TypeMeta( i ? "Any" : "Void", sl, i) 
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
        
    const TypeMeta&        invalid()
    {
        static EmptyType*  s_ret = new EmptyType(MT_Invalid);
        return *s_ret;
    }
    
    const TypeMeta&        any()
    {
        static EmptyType*  s_ret = new EmptyType(MT_Any);
        return *s_ret;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    const std::vector<const TypeMeta*>&   TypeMeta::all()
    {
        assert(thread_safe_read());
        return repo().types.all;
    }
    
    const TypeMeta*                  TypeMeta::find(id_t i)
    {
        assert(thread_safe_read());
        const Meta* m   = repo().all.value(i, nullptr);
        return (m && m->is_type()) ? static_cast<const TypeMeta*>(m) : nullptr;
    }
    
    const TypeMeta*                  TypeMeta::find(std::string_view sv)
    {
        assert(thread_safe_read());
        return repo().types.lut.first(sv, nullptr);
    }

    const TypeMeta*                  TypeMeta::find(stem_k, std::string_view sv)
    {
        assert(thread_safe_read());
        return repo().types.stem.first(sv, nullptr);
    }

    std::vector<const TypeMeta*>          TypeMeta::find_all(const string_set_t& types, bool noisy)
    {
        std::vector<const TypeMeta*> ret;
        auto&   r   = repo().types.lut;
        for(const std::string& s : types){
            if(s.empty())
                continue;
                
            const TypeMeta* ti  = r.first(s);
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

    TypeMeta::TypeMeta(std::string_view zName, const std::source_location& sl, id_t i) : CompoundMeta(zName, sl, nullptr, i)
    {
        set(Flag::TYPE);
        
        Repo&   r  = repo();
        assert("no duplicate typenames!" && !r.types.lut.has(name())); 
        
        r.types << this;
    }

    TypeMeta::~TypeMeta()
    {
        //  should never be used....
    }

    void            TypeMeta::add_alias(std::string_view sz)
    {
        Meta::add_alias(sz);
        repo().types.add_mapping(sz, this);
    }
    
    void            TypeMeta::add_printer(std::string_view k, FNFormat fn)
    {
        if(fn){
            if(k.empty()){
                m_print     = fn;
            } else {
                m_printers[k]   = fn;
            }
        }
    }

    bool        TypeMeta::can_convert_to(const TypeMeta& otherType) const
    {
        return static_cast<bool>(m_convert.get(&otherType, nullptr));
    }

    any_x       TypeMeta::contruct_impl(std::initializer_list<const TypeMeta*> types, std::initializer_list<const void*> values) const
    {
        const ConstructorInfo*      best    = nullptr;
        int                         score   = 0;
        
        for(const ConstructorInfo* ci : m_constructors){
            int r   = ci -> type_match(span(types));
            if(r < 0)
                continue;
            
            if((r<score) || !best){
                best    = ci;
                score   = r;
            }
        }
        if(!best)
            return errors::bad_argument();
        
        return best->invoke(nullptr, span(types), span(values), false);
    }
    
    TypeMeta::FNConvert           TypeMeta::converter(const TypeMeta& otherType) const
    {
        return m_convert.get(&otherType, nullptr);
    }

    std::error_code        TypeMeta::copy(void*dst, const void*src) const
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
    
    std::error_code        TypeMeta::copy(void*dst, const void*src, const TypeMeta& srcType) const
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

    size_t                              TypeMeta::method_count() const
    {
        return m_methods.all.size();
    }

    const std::vector<const MethodInfo*>&    TypeMeta::methods() const
    {
        return m_methods.all;
    }

    //! List of operators for this type
    const std::vector<const OperatorInfo*>& TypeMeta::operators() const
    {
        return m_operators.all;
    }
    
    //! All operators for the specified operator
    const TypeMeta::OperatorLUC::equal_range_t  TypeMeta::operators(Operator opt) const
    {
        return m_operators.lut.equal_range(opt);
    }

    size_t  TypeMeta::operators_count() const
    {
        return m_operators.all.size();
    }

    TypeMeta::FNFormat  TypeMeta::printer(std::string_view k) const
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

    TypeMeta::FNFormat  TypeMeta::printer(string_view_initializer_list_t keys) const
    {
        for(std::string_view k : keys){
            if(k.empty())
                continue;
            auto i = m_printers.find(k);
            if((i != m_printers.end()) && i->second) 
                return i->second;
        }
        
        if(m_print)
            return m_print;
        return m_write;
    }

    const PropertyInfo*  TypeMeta::property(std::string_view k) const
    {
        return m_properties.lut.first(k, nullptr);
    }

    
    const std::vector<const PropertyInfo*>&  TypeMeta::properties() const
    {
        return m_properties.all;
    }

    TypeMeta::PropertyLUC::equal_range_t TypeMeta::properties(std::string_view k) const
    {
        return m_properties.lut.equal_range(k);
    }

    size_t  TypeMeta::property_count() const
    {
        return m_properties.all.size();
    }

    void    TypeMeta::sweep_impl() 
    {
        CompoundMeta::sweep_impl();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    /*! \brief Converts meta to type, if it's valid
    
        \return TypeMeta pointer, if valid, NULL otherwise
    */
    const TypeMeta* to_type(const Meta* m)
    {
        return (m && m->is_type()) ? static_cast<const TypeMeta*>(m) : nullptr;
    }
    
    const TypeMeta* to_type(const Meta& m)
    {
        return m.is_type() ? static_cast<const TypeMeta*>(&m) : nullptr;
    }

    /*! \brief Converts meta to type, if it's valid
    
        \return TypeMeta pointer, if valid, NULL otherwise
    */
    TypeMeta* to_type(Meta* m)
    {
        return (m && m->is_type()) ? static_cast<TypeMeta*>(m) : nullptr;
    }

    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& str, std::span<const TypeMeta*> types)
    {
        bool    f = true;
        str << "{";
        for(const TypeMeta* ti : types){
            if(f){
                f   = false;
            } else {
                str << ", ";
            }
            str << ti->name();
        }
        str << "}";
        return str;
    }
}

YQ_INVOKE(
    yq::any();
    yq::invalid();
)


