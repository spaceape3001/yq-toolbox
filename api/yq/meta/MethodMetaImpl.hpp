////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MethodMeta.hpp>
#include <yq/meta/TypedArgMeta.hpp>
#include <yq/trait/indices.hpp>
#include <yq/errors.hpp>
#include <type_traits>

namespace yq {

    template <typename T>
    static constexpr bool is_returnable_v   = !(std::is_same_v<T,void> || std::is_same_v<T,std::error_code>);

    template <typename...> 
    struct MethodMeta::DefineArg {
        static void    define(const std::source_location&, Meta*)
        {
        }
    };
    
    template <typename T, typename... Args> 
    struct MethodMeta::DefineArg<T, Args...> {
        static void    define(const std::source_location&sl, Meta*parent)
        {
            using act_type  = std::remove_cvref_t<T>;
            static_cast<MethodMeta*>(parent)->m_args.push_back( new ArgMeta::Typed<act_type>(sl, parent));
            DefineArg<Args...>::define(sl, parent);
        }
    };

    template <typename R, typename...Args> 
    void MethodMeta::define_signature()
    {
        if constexpr (is_returnable_v<R>){
            m_result    = new ArgMeta::Typed<R>(source(), this);
        }
    
        DefineArg<Args...>::define(source(), this);
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    namespace impl {
        template <typename R, typename Obj, typename... Args, unsigned... Is>
        std::error_code    invokeConst(R* res, const Obj*obj, R(Obj::*fn)(Args...) const, const void* const* args, indices<Is...>)
        {
            if constexpr (std::is_same_v<R, std::error_code>){
                return (obj->*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
            } else  if constexpr (!std::is_same_v<R,void>){
                *(R*) res = (obj->*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            } else {
                (obj->*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            }
        }
    }

    template <typename R, typename Obj, typename... Args>
    class MethodMeta::Const : public MethodMeta {
    public:

        static constexpr const size_t   ARG_COUNT   = sizeof...(Args);

        typedef R (Obj::*FN)(Args...) const;
    
        /*! \brief Constructor 
            \note   Only use directly this if you know what you're doing, otherwise, stay away
            \param[in] function Function pointer
            \param[in] zName    name of the property
            \param[in] sl       Source location of the definition (usually auto-picked up by the meta declare helpers
            \param[in] parent   Parent object this is apart of
            \param[in] opts     Options
        */
        Const(FN function, std::string_view zName, const std::source_location& sl, Meta* parent) : 
            MethodMeta(zName, sl, parent), m_function(function)
        {
            set(Flag::CONST);
            define_signature<std::remove_cvref_t<R>,Args...>();
        }

        std::error_code  _invoke(void* res, void* obj, const void* const* args) const override final
        {
            if(!obj)
                return errors::null_object();
                
            if constexpr (is_returnable_v<R>){
                if(!res)
                    return errors::null_result();
            }

            return impl::invokeConst((R*) res, (const Obj*) obj, m_function, args, indices_gen<ARG_COUNT>() );
        }

        virtual size_t          arg_count() const noexcept override final
        {
            return ARG_COUNT;
        }

    private:
        FN      m_function;
    };

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    namespace impl {
        template <typename R, typename Obj, typename... Args, unsigned... Is>
        std::error_code    invokeDynamic(R* res, Obj*obj, R(Obj::*fn)(Args...) const, const void* const* args, indices<Is...>)
        {
            if constexpr (std::is_same_v<R, std::error_code>){
                return (obj->*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
            } else  if constexpr (!std::is_same_v<R,void>){
                *(R*) res = (obj->*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            } else {
                (obj->*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            }
        }
    }

    template <typename R, typename Obj, typename... Args>
    class MethodMeta::Dynamic : public MethodMeta {
    public:

        static constexpr const size_t   ARG_COUNT   = sizeof...(Args);
        typedef R (Obj::*FN)(Args...);
    
        /*! \brief Constructor 
            \note   Only use directly this if you know what you're doing, otherwise, stay away
            \param[in] function Function pointer
            \param[in] zName    name of the property
            \param[in] sl       Source location of the definition (usually auto-picked up by the meta declare helpers
            \param[in] parent   Parent object this is apart of
            \param[in] opts     Options
        */
        Dynamic(FN function, std::string_view zName, const std::source_location& sl, Meta* parent) : 
            MethodMeta(zName, sl, parent), m_function(function)
        {
            define_signature<std::remove_cvref_t<R>,Args...>();
        }

        std::error_code   _invoke(void* res, void* obj, const void* const* args) const override final
        {
            if(!obj)
                return errors::null_object();

            if constexpr (is_returnable_v<R>){
                if(!res)
                    return errors::null_result();
            }
        
            return impl::invokeDynamic((R*) res, (Obj*) obj, m_function, args, indices_gen<ARG_COUNT>() );
        }

        virtual size_t          arg_count() const noexcept override final
        {
            return ARG_COUNT;
        }

    private:
        FN      m_function;
    };


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    namespace impl {
        template <typename R, typename... Args, unsigned... Is>
        std::error_code    invokeStatic(R* res, R(*fn)(Args...), const void* const* args, indices<Is...>)
        {
            if constexpr (std::is_same_v<R, std::error_code>){
                return (*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
            } else  if constexpr (!std::is_same_v<R,void>){
                *res = (*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            } else {
                (*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            }
        }
    }
    
    template <typename R, typename... Args>
    class MethodMeta::Static : public MethodMeta {
    public:
    
        typedef R (*FN)(Args...);
        static constexpr const size_t   ARG_COUNT   = sizeof...(Args);
        
        /*! \brief Constructor 
            \note   Only use directly this if you know what you're doing, otherwise, stay away
            \param[in] function Function pointer
            \param[in] zName    name of the method
            \param[in] sl       Source location of the definition (usually auto-picked up by the meta declare helpers
            \param[in] parent   Parent object this is apart of
        */
        Static(FN function, std::string_view zName, const std::source_location& sl, Meta* parent) : 
            MethodMeta(zName, sl, parent), m_function(function)
        {
            set(Flag::STATIC);
            define_signature<std::remove_cvref_t<R>,Args...>();
        }

        std::error_code            _invoke(void* res, void*, const void* const* args) const override final
        {
            if constexpr (is_returnable_v<R>){
                if(!res)
                    return errors::null_result();
            }
            return impl::invokeStatic((R*) res, m_function, args, indices_gen<ARG_COUNT>() );
        }

        virtual size_t          arg_count() const noexcept override final
        {
            return ARG_COUNT;
        }

    private:
        FN      m_function;
    };
    

}
