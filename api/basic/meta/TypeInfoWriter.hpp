////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/TypeInfo.hpp>
#include <basic/meta/InfoBinder.hpp>
#include <basic/meta/CompoundInfoDynamic.hpp>
#include <basic/trait/has_less.hpp>
#include <basic/trait/is_template.hpp>
#include <basic/List.hpp>
#include <basic/Hash.hpp>
#include <basic/Map.hpp>
#include <basic/MultiMap.hpp>
#include <basic/Set.hpp>
#include <basic/Vector.hpp>
#include <basic/StreamOps.hpp>

namespace yq {

    
    template <typename T>
    struct TypeInfoFor {
        using Type  = TypeInfo;
    };
    
    template <typename T>
    using type_info_t  = TypeInfoFor<T>::Type;
    
    #if 0
    /*! \brief Gathers Types
        
        This gathers the template parameter type as a type info into the vector, IF meta type aware.
        \return One always one for this specialization of the function.
    */
    template <typename T>
    unsigned    gather_types(Vector<const TypeInfo*>& ret)
    {
        if constexpr (is_type_v<T>){
            ret << &meta<T>();
        } 
        // TODO pointers, references, shared_ptrs, etc to known types.
        return 1;
    }
    
    /*! \brief Gathers types from parameter pack
    
        This breaks down a template parameter pack for its type infos
    */
    template <typename T, typename... Args>
    unsigned gather_types(Vector<const TypeInfo*>& ret)
    {
        gather_types<T>(ret);
        return 1 + gather_types<Args...>(ret);
    }
    
    template <typename> struct GatherTemplateArgs { 
        unsigned operator()(Vector<const TypeInfo*>& ret)
        {
            return 0;
        }
    };
    

    template <template <typename...> class Tmpl, typename ...Args> 
    struct GatherTemplateArgs<Tmpl<Args...>> {
        static unsigned   gather(Vector<const TypeInfo*>& ret) 
        {
            return gather_types<Args...>(ret);
        }
    };
    #endif

    template <typename T>
    class TypeInfo::Typed : public type_info_t<T> {
    protected:
        Typed(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : type_info_t<T>(zName, sl, i)
        {
            options_t   opts    = 0;
        
            TypeInfo::m_default.ctorCopy(T{});
            TypeInfo::m_copyB         = [](DataBlock& dst, const DataBlock&src){
                dst.reference<T>() = src.reference<T>();
            };
            TypeInfo::m_copyR        = [](DataBlock& dst, const void* src){
                dst.reference<T>() = *(const T*) src;
            };
            TypeInfo::m_ctorCopyR     = [](DataBlock& dst, const void* src){ 
                dst.ctorCopy(*(const T*) src); 
            };
            TypeInfo::m_ctorCopyB     = [](DataBlock& dst, const DataBlock& src){ 
                dst.ctorCopy( src.reference<T>());
            };
            TypeInfo::m_ctorMove      = [](DataBlock& dst, DataBlock&& src){
                if constexpr (sizeof(T) <= sizeof(DataBlock))
                    dst.ctorMove( std::move(src.reference<T>()));
                else
                    dst.Pointer = src.Pointer;
            };
            TypeInfo::m_dtor          = [](DataBlock& tgt)
            {
                tgt.dtor<T>();
            };
            TypeInfo::m_equal         = [](const DataBlock& a, const DataBlock& b) -> bool 
            {
                return a.reference<T>() == b.reference<T>();
            };
            
            if constexpr (trait::has_less_v<T>){
                TypeInfo::m_less      = [](const DataBlock& a, const DataBlock& b) -> bool 
                {
                    return a.reference<T>() < b.reference<T>();
                };
                opts |= LESS;
            }
            
            TypeInfo::m_moveB         = [](DataBlock& a, DataBlock&&b) 
            {
                a.reference<T>() = std::move( b.reference<T>());
            };
            
            TypeInfo::m_size          = sizeof(T);
            
            if constexpr ( trait::is_template_v<T>) {
            #if 0
                TypeInfo::m_template.params     = GatherTemplateArgs<T>()(TypeInfo::m_template.args);
                if(!TypeInfo::m_template.args.empty())  // only flag it as a template if any parameters trigger
                    opts |= TEMPLATE;
            #endif
            }
            
            if constexpr ( has_stream_v<T>) {
                TypeInfo::m_print   = TypeInfo::m_write = [](Stream& dst, const void* src){
                    dst << *(const T*) src;
                };
            }
            
            if(is_small_v<T>)
                opts |= SMALL;
            if(opts)
                Meta::set_options(opts);
        }
    };
    
    template <typename T>
    class TypeInfo::Special : public Typed<T> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<T>(zName, sl, i) {}
    };
    
    template <typename K, typename V>
    class TypeInfo::Special<Hash<K,V>> : public Typed<Hash<K,V>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<Hash<K,V>>(zName, sl, i)
        {
            Meta::set_option(COLLECTION);
        }
    };

    template <typename T>
    class TypeInfo::Special<List<T>> : public Typed<List<T>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<List<T>>(zName, sl, i) 
        {
            Meta::set_option(COLLECTION);
        }
    };
    
    template <typename K, typename V, typename C>
    class TypeInfo::Special<Map<K,V,C>> : public Typed<Map<K,V,C>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<Map<K,V,C>>(zName, sl, i)
        {
            Meta::set_option(COLLECTION);
        }
    };

    template <typename K, typename V, typename C>
    class TypeInfo::Special<MultiMap<K,V,C>> : public Typed<MultiMap<K,V,C>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<MultiMap<K,V,C>>(zName, sl, i)
        {
            Meta::set_option(COLLECTION);
        }
    };

    template <typename T, typename C>
    class TypeInfo::Special<Set<T,C>> : public Typed<Set<T,C>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<Set<T,C>>(zName, sl, i) 
        {
            Meta::set_option(COLLECTION);
        }
    };

    template <typename T>
    class TypeInfo::Special<Vector<T>> : public Typed<Vector<T>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<Vector<T>>(zName, sl, i) 
        {
            Meta::set_option(COLLECTION);
        }
    };
    

    //! The FINAL storage class, the one that's generic
    template <typename T>
    class TypeInfo::Final : public Special<T> {
    private:
        friend class InfoBinder<T>;
        Final(std::string_view zName, id_t i=AUTO_ID, const std::source_location& sl=std::source_location::current()) : Special<T>(zName, sl, i) {}
        static TypeInfo&       s_save;
    };


    template <typename T>
    using TypeInfoWriterBase    = std::conditional<std::is_class_v<T>, CompoundInfo::Dynamic<T>, Meta::Writer>::type;

    template <typename T>
    class TypeInfo::Writer : public TypeInfoWriterBase<T> {
    public:
        static_assert( InfoBinder<T>::IsType, "T must be meta-type declared!");
    
    
        void    alias(std::string_view a)
        {
            static_cast<TypeInfo*>(Meta::Writer::m_meta) -> add_alias(a);
        }
    
        template <typename U>
        requires std::is_nothrow_convertible_v<U,T>
        void casts()
        {
            static_assert( is_type_v<U>, "U must be meta-type declared!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src){
                    *(U*) dst = U( *(const T*) src);
                };
            }
        }
        
        template <typename U, U(*FN)(T)>
        void converts()
        {
            static_assert(is_type_v<U>, "U must be meta-type decalred!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src){
                    *(U*) dst = FN( *(const T*) src);
                };
            }
        }
        
        template <typename U, U(*FN)(const T&)>
        void converts()
        {
            static_assert(is_type_v<U>, "U must be meta-type decalred!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src){
                    *(U*) dst = FN( *(const T*) src);
                };
            }
        }

        template <typename U, void (*FN)(U&, const T&)>
        void converts()
        {
            static_assert(is_type_v<U>, "U must be meta-type decalred!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src){
                    FN(*(U*) dst,  *(const T*) src);
                };
            }
        }
        
        template <std::string(*FN)(T)>
        void    format()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_write   = [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                };
            }
        }
        
        template <std::string(*FN)(const T&)>
        void    format()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_write   = [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                };
            }
        }
        
        
        template <bool (*FN)(T&, const std::string_view&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> bool {
                    return FN(*(T*) dst, src);
                };
            }
        }

        template <bool (*FN)(const std::string_view&, T&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> bool {
                    return FN(src, *(T*) dst);
                };
            }
        }

        template <Result<T> (*FN)(const std::string_view&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> bool {
                    Result<T>   r   = FN(src);
                    *(T*) dst = std::move(r.value);
                    return r.good;
                };
            }
        }

        template <std::string(*FN)(T)>
        void    print()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_print   = [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                };
            }
        }
        
        template <std::string(*FN)(const T&)>
        void    print()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_print   = [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                };
            }
        }

        template <void(*FN)(Stream&, const T&)>
        void    print()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_print   = [](Stream& dst, const void* src)  {
                    FN(dst, *(const T*) src);
                };
            }
        }

        template <void(*FN)(Stream&, T)>
        void    print()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_print   = [](Stream& dst, const void* src)  {
                    FN(dst, *(const T*) src);
                };
            }
        }

        Writer(TypeInfo* ti) : TypeInfoWriterBase<T>(ti) {}
        Writer(TypeInfo& ti) : TypeInfoWriterBase<T>(&ti) {}
    };
}
