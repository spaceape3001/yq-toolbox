////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Result.hpp>
#include <yq-toolbox/meta/TypeInfo.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/meta/CompoundInfoDynamic.hpp>
#include <yq-toolbox/meta/ConstructorInfoImpl.hpp>
#include <yq-toolbox/meta/ConstructorInfoWriter.hpp>
#include <yq-toolbox/meta/OperatorInfoImpl.hpp>
#include <yq-toolbox/meta/OperatorInfoWriter.hpp>
#include <yq-toolbox/trait/can_add.hpp>
#include <yq-toolbox/trait/can_affirm.hpp>
#include <yq-toolbox/trait/can_divide.hpp>
#include <yq-toolbox/trait/can_multiply.hpp>
#include <yq-toolbox/trait/can_negate.hpp>
#include <yq-toolbox/trait/can_subtract.hpp>
#include <yq-toolbox/trait/can_two_add.hpp>
#include <yq-toolbox/trait/can_two_divide.hpp>
#include <yq-toolbox/trait/can_two_multiply.hpp>
#include <yq-toolbox/trait/can_two_subtract.hpp>
#include <yq-toolbox/trait/has_less.hpp>
#include <yq-toolbox/trait/is_template.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/io/StreamOps.hpp>
#include <expected>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <unordered_map>

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
    
    /*! \brief  Basic first level of type information
    
        Several derivations are being used to control how the meta type information is being generated.  
        The "Typed" is the first one, it provides the basics that everybody utilizes.
        
    */
    template <typename T>
    class TypeInfo::Typed : public type_info_t<T> {
    protected:
    
        /*! \brief Constructor, protected
        
            \param[in] zName    name of the type, should be from a char* in the program strings table, ie "" not dynamic.
            \param[in] sl       Source location to the instantiation (final uses default-parameter to get it)
            \param[in] i        ID to override, but most types will use AUTO
        */
        Typed(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : type_info_t<T>(zName, sl, i)
        {
            TypeInfo::m_default.ctorCopy(T{});
            TypeInfo::m_copyB         = [](DataBlock& dst, const DataBlock&src){
                dst.reference<T>()  = src.reference<T>();
            };
            TypeInfo::m_copyR        = [](DataBlock& dst, const void* src){
                dst.reference<T>()  = *(const T*) src;
            };
            TypeInfo::m_copyRR      = [](void* dst, const void* src){
                *(T*) dst           = *(const T*) src;
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
            
            if constexpr (has_less_v<T>){
                TypeInfo::m_less      = [](const DataBlock& a, const DataBlock& b) -> bool 
                {
                    return a.reference<T>() < b.reference<T>();
                };
                Meta::set(Flag::LESS);
            }
            
            TypeInfo::m_moveB         = [](DataBlock& a, DataBlock&&b) 
            {
                a.reference<T>() = std::move( b.reference<T>());
            };
            
            TypeInfo::m_size          = sizeof(T);
            
            if constexpr ( is_template_v<T>) {
            #if 0
                TypeInfo::m_template.params     = GatherTemplateArgs<T>()(TypeInfo::m_template.args);
                if(!TypeInfo::m_template.args.empty())  // only flag it as a template if any parameters trigger
                    Meta::set(Flag::TEMPLATE);
            #endif
            }
            
            if constexpr ( has_stream_v<T>) {
                TypeInfo::m_print   = TypeInfo::m_write = [](Stream& dst, const void* src){
                    dst << *(const T*) src;
                };
            }
            
            if(is_small_v<T>)
                Meta::set(Flag::SMALL);
        }
    };
    
    /*! \brief Specialization meta
    
        This is the auto-deduction specialization derivation for the type.  It'll set options based
        on the template type, like hashes, lists, etc
    */
    template <typename T>
    class TypeInfo::Special : public Typed<T> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<T>(zName, sl, i) {}
    };
    
    template <typename K, typename V, typename H, class KQ, class A>
    class TypeInfo::Special<std::unordered_map<K,V,H,KQ,A>> : public Typed<std::unordered_map<K,V,H,KQ,A>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<Hash<K,V>>(zName, sl, i)
        {
            Meta::set(Flag::COLLECTION);
        }
    };

    template <typename T, typename A>
    class TypeInfo::Special<std::list<T,A>> : public Typed<std::list<T,A>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<std::list<T,A>>(zName, sl, i) 
        {
            Meta::set(Flag::COLLECTION);
        }
    };
    
    template <typename K, typename V, typename C, typename A>
    class TypeInfo::Special<std::map<K,V,C,A>> : public Typed<std::map<K,V,C,A>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<std::map<K,V,C,A>>(zName, sl, i)
        {
            Meta::set(Flag::COLLECTION);
        }
    };

    template <typename K, typename V, typename C, typename A>
    class TypeInfo::Special<std::multimap<K,V,C,A>> : public Typed<std::multimap<K,V,C,A>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<std::multimap<K,V,C,A>>(zName, sl, i)
        {
            Meta::set(Flag::COLLECTION);
        }
    };

    template <typename T, typename C, typename A>
    class TypeInfo::Special<std::set<T,C,A>> : public Typed<std::set<T,C,A>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<std::set<T,C,A>>(zName, sl, i) 
        {
            Meta::set(Flag::COLLECTION);
        }
    };

    template <typename T, typename A>
    class TypeInfo::Special<std::vector<T,A>> : public Typed<std::vector<T,A>> {
    protected:
        Special(std::string_view zName, const std::source_location&sl, id_t i=AUTO_ID) : Typed<std::vector<T,A>>(zName, sl, i) 
        {
            Meta::set(Flag::COLLECTION);
        }
    };
    

    /*! The FINAL storage class, the one that's generic
    
        This is the class that does the actual storage for type information as a private static member, but allows
        the infobinder to access it.
    */
    template <typename T>
    class TypeInfo::Final : public Special<T> {
    private:
        friend class InfoBinder<T>;
        Final(std::string_view zName, id_t i=AUTO_ID, const std::source_location& sl=std::source_location::current()) : Special<T>(zName, sl, i) {}
        static TypeInfo&       s_save;
    };

    /*! \brief Conditional writer base
    
        Trying to do class operations on a simple type causes problems, so we have this alias used for the 
        base type, allows for the rest of the code to be the same.
    */
    template <typename T>
    using TypeInfoWriterBase    = std::conditional<std::is_class_v<T>, CompoundInfo::Dynamic<T>, Meta::Writer>::type;


    /*! \brief Basic type information writer
    
        This is what allows for the user-code to modify a type information. 
        
        \note it's STRONGLY advised to be in a thread-safe environment.  The `thread_safe_write()` is a sentienel
        but might not be perfect.
    */
    template <typename T>
    class TypeInfo::Writer : public TypeInfoWriterBase<T> {
    public:
        static_assert( InfoBinder<T>::IsType, "T must be meta-type declared!");
    
        using type_t    = T;
    
        //! Adds an alias to the type
        //! \note the provided parameter is expected to be from the program strings table
        void    alias(std::string_view a)
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta) -> add_alias(a);
            }
        }
    
        //! Allows for an any conversion by cast
        //! \tparam[U] other type
        template <typename U>
        requires std::is_nothrow_convertible_v<U,T>
        void casts()
        {
            static_assert( is_type_v<U>, "U must be meta-type declared!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src) -> std::error_code {
                    *(U*) dst = U( *(const T*) src);
                    return std::error_code();
                };
            }
        }
        
        template <typename ... Args>
        ConstructorInfo::Writer<T, Args...> constructor(T(*function)(Args...), const std::source_location& sl=std::source_location::current())
        {
            if(function && thread_safe_write()){
                ConstructorInfo* ret = new OperatorInfo::Static<T, Args...>(function, sl, Meta::Writer::m_meta);
                return ConstructorInfo::Writer<T, Args...>(ret, 0ULL);
            }
            
            return ConstructorInfo::Writer<T, Args...>();
        }
        
        /*! \brief Conversion with routine
            This registers a conversion via function to another type
        */
        template <typename U, U(*FN)(T)>
        void converts()
        {
            static_assert(is_type_v<U>, "U must be meta-type declared!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src) -> std::error_code {
                    *(U*) dst = FN( *(const T*) src);
                    return std::error_code();
                };
            }
        }
        
        
        /*! \brief Conversion with routine
            This registers a conversion via function to another type
        */
        template <typename U, U(*FN)(const T&)>
        void converts()
        {
            static_assert(is_type_v<U>, "U must be meta-type declared!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src) -> std::error_code {
                    *(U*) dst = FN( *(const T*) src);
                    return std::error_code();
                };
            }
        }

        
        /*! \brief Conversion with routine
            This registers a conversion via function to another type
        */
        template <typename U, void (*FN)(U&, const T&)>
        void converts()
        {
            static_assert(is_type_v<U>, "U must be meta-type declared!");
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_convert[ &InfoBinder<U>::bind()] = [](void* dst, const void* src)  -> std::error_code {
                    FN(*(U*) dst,  *(const T*) src);
                    return std::error_code();
                };
            }
        }
        
        /*! \brief Registers IO text stream formatting handler
        */
        template <std::string(*FN)(T)>
        void    format()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_write   = [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                };
            }
        }
        
        /*! \brief Registers IO text stream formatting handler
        */
        template <std::string(*FN)(const T&)>
        void    format()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_write   = [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                };
            }
        }
        
        
        /*
        void operate()
        {
        }
        */
        
        /*! \brief Define operators
        
            \note, the name is "operate" rather than "operator" due to naming conflicts with C++ keyword "operator"
        */
        template <typename R, typename ... Args>
        OperatorInfo::Writer<R, const T&, Args...>  operate(Operator opId, R (*function)(const T&, Args...), const std::source_location& sl=std::source_location::current())
        {
            if(function && thread_safe_write()){
                OperatorInfo* ret = new OperatorInfo::Static<R,const T&, Args...>(function, opId, sl, Meta::Writer::m_meta);
                return OperatorInfo::Writer<R,const T&, Args...>(ret, 0ULL);
            }
            
            return OperatorInfo::Writer<R,const T&, Args...>();
        }
        
        template <typename R, typename ... Args>
        OperatorInfo::Writer<R, T, Args...>  operate(Operator opId, R (*function)(T, Args...), const std::source_location& sl=std::source_location::current())
        {
            if(function && thread_safe_write()){
                OperatorInfo* ret = new OperatorInfo::Static<R,T,Args...>(function, opId, sl, Meta::Writer::m_meta);
                return OperatorInfo::Writer<R,T,Args...>(ret, 0ULL);
            }
            
            return OperatorInfo::Writer<R,T,Args...>();
        }
        
        /*! \brief Convenience methods for defining common binary operations with right term
        */
        template <typename U>
        void    operate_with(OperatorFlags enabled=ALL, const std::source_location& sl=std::source_location::current())
        {
            if constexpr (can_two_add_v<T,U>){
                if(enabled(Operator::Add)){
                    operate(Operator::Add, generic_two_add<T,U>, sl);
                }
            }
            if constexpr (can_two_subtract_v<T,U>){
                if(enabled(Operator::Subtract)){
                    operate(Operator::Subtract, generic_two_subtract<T,U>, sl);
                }
            }
            if constexpr (can_two_multiply_v<T,U>){
                if constexpr (is_type_v<product_t<T,U>>){
                    if(enabled(Operator::Multiply)){
                        operate(Operator::Multiply, generic_two_multiply<T,U>, sl);
                    }
                }
            }
            if constexpr (can_two_divide_v<T,U>){
                if constexpr (is_type_v<quotient_t<T,U>>){
                    if(enabled(Operator::Divide)){
                        operate(Operator::Divide, generic_two_divide<T,U>, sl);
                    }
                }
            }
        }
        
        void    operate_self(OperatorFlags enabled=ALL, const std::source_location& sl=std::source_location::current())
        {
            if constexpr ( can_add_v<T> && !is_template_enum_v<T>){
                if(enabled(Operator::Add)){
                    operate(Operator::Add, generic_add<T>, sl );
                }
            }
            if constexpr ( can_affirm_v<T> && !is_template_enum_v<T> ){
                if(enabled(Operator::Affirm)){
                    operate(Operator::Affirm, generic_affirm<T>, sl );
                }
            }
            if constexpr ( can_divide_v<T> && !is_template_enum_v<T>){
                if constexpr (is_type_v<quotient_t<T,T>>){
                    if(enabled(Operator::Divide)){
                        operate(Operator::Divide, generic_divide<T>, sl );
                    }
                }
            }
            if constexpr ( can_multiply_v<T> && !is_template_enum_v<T>){
                if constexpr (is_type_v<product_t<T,T>> ){
                    if(enabled(Operator::Multiply)){
                        operate(Operator::Multiply, generic_multiply<T>, sl );
                    }
                }
            }
            if constexpr ( can_negate_v<T> && !is_template_enum_v<T> ){
                if(enabled(Operator::Negate)){
                    operate(Operator::Negate, generic_negate<T>, sl );
                }
            }
            if constexpr ( can_subtract_v<T> && !is_template_enum_v<T> ){
                if(enabled(Operator::Subtract)){
                    operate(Operator::Subtract, generic_subtract<T>, sl );
                }
            }
        }

        
        /*! \brief Registers IO stream parsing handler
        */
        template <bool (*FN)(T&, const std::string_view&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    if(! FN(*(T*) dst, src))
                        return errors::parser_failed();
                    return std::error_code();
                };
            }
        }

        /*! \brief Registers IO stream parsing handler
        */
        template <std::error_code (*FN)(T&, const std::string_view&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    return FN(*(T*) dst, src);
                };
            }
        }

        /*! \brief Registers IO string parsing handler
        */
        template <bool (*FN)(const std::string_view&, T&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    return FN(src, *(T*) dst) ? std::error_code() : errors::parser_failed();
                };
            }
        }

        /*! \brief Registers IO string parsing handler
        */
        template <std::error_code (*FN)(const std::string_view&, T&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    return FN(src, *(T*) dst);
                };
            }
        }

        /*! \brief Registers IO string parsing handler
        */
        template <Result<T> (*FN)(const std::string_view&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    Result<T>   r   = FN(src);
                    *(T*) dst = std::move(r.value);
                    return r.good ? std::error_code() : errors::parser_failed();
                };
            }
        }

        /*! \brief Registers IO string parsing handler
        */
        template <std::pair<T,std::error_code> (*FN)(const std::string_view&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    auto [ data, ec ] = FN(src);
                    *(T*) dst = std::move(data);
                    return ec;
                };
            }
        }

        /*! \brief Registers IO string parsing handler
        */
        template <Expect<T> (*FN)(const std::string_view&)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    auto data = FN(src);
                    if(!data)
                        return data.error();
                    *(T*) dst = std::move(*data);
                    return std::error_code();
                };
            }
        }

        /*! \brief Registers IO string parsing handler
        */
        template <Expect<T> (*FN)(std::string_view)>
        void    parse()
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->m_parse     = [](void* dst, const std::string_view&src) -> std::error_code {
                    auto data = FN(src);
                    if(!data)
                        return data.error();
                    *(T*) dst = std::move(*data);
                    return std::error_code();
                };
            }
        }

        /*! \brief Registers debug string formatting handler.
        */
        template <std::string(*FN)(T)>
        void    print(std::string_view sv={})
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->add_printer(sv, [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                });
            }
        }
        
        /*! \brief Registers debug string formatting handler.
        */
        template <std::string(*FN)(const T&)>
        void    print(std::string_view sv={})
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->add_printer(sv, [](Stream& dst, const void* src)  {
                    dst << FN(*(const T*) src);
                });
            }
        }

        /*! \brief Registers debug stream formatting handler.
        
            The stream based ones are preferred
        */
        template <void(*FN)(Stream&, const T&)>
        void    print(std::string_view sv={})
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->add_printer(sv, [](Stream& dst, const void* src)  {
                    FN(dst, *(const T*) src);
                });
            }
        }

        /*! \brief Registers debug stream formatting handler.
        
            The stream based ones are preferred
        */
        template <void(*FN)(Stream&, T)>
        void    print(std::string_view sv={})
        {
            if(thread_safe_write()){
                static_cast<TypeInfo*>(Meta::Writer::m_meta)->add_printer(sv, [](Stream& dst, const void* src)  {
                    FN(dst, *(const T*) src);
                });
            }
        }
        

        //! Construct from pointer
        Writer(TypeInfo* ti) : TypeInfoWriterBase<T>(ti) {}
        
        //! Construct from reference (common)
        Writer(TypeInfo& ti) : TypeInfoWriterBase<T>(&ti) {}
    };
}
