////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/MethodInfo.hpp>
#include <basic/meta/TypedArgInfo.hpp>
#include <basic/trait/indices.hpp>
#include <basic/Errors.hpp>
#include <type_traits>

namespace yq {

    namespace trait {
        template <typename T>
        static constexpr bool is_returnable_v   = !(std::is_same_v<T,void> || std::is_same_v<T,std::error_code>);
    }

    template <typename...> 
    struct MethodInfo::DefineArg {
        static void    define(const std::source_location&, Meta*, options_t options)
        {
        }
    };
    
    template <typename T, typename... Args> 
    struct MethodInfo::DefineArg<T, Args...> {
        static void    define(const std::source_location&sl, Meta*parent, options_t options)
        {
            using act_type  = std::remove_cvref_t<T>;
            static_cast<MethodInfo*>(parent)->m_args.push_back( new ArgInfo::Typed<act_type>(sl, parent, options));
            DefineArg<Args...>::define(sl, parent, options);
        }
    };

    template <typename R, typename...Args> 
    void MethodInfo::define_signature(options_t opts)
    {
        if constexpr (trait::is_returnable_v<R>){
            m_result    = new ArgInfo::Typed<R>(source(), this);
        }
    
        DefineArg<Args...>::define(source(), this, opts);
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    namespace impl {
        template <typename R, typename Obj, typename... Args, unsigned... Is>
        std::error_code    invokeConst(R* res, const Obj*obj, R(Obj::*fn)(Args...) const, const void** args, trait::indices<Is...>)
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
    class MethodInfo::Const : public MethodInfo {
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
        Const(FN function, std::string_view zName, const std::source_location& sl, Meta* parent, options_t opts=0) : 
            MethodInfo(zName, sl, parent, opts|CONST), m_function(function)
        {
            define_signature<std::remove_cvref_t<R>,Args...>();
        }

        std::error_code  _invoke(void* res, void* obj, const void** args) const override final
        {
            if(!obj)
                return errors::null_object();
                
            if constexpr (trait::is_returnable_v<R>){
                if(!res)
                    return errors::null_result();
            }

            return impl::invokeConst((R*) res, (const Obj*) obj, m_function, args, trait::indices_gen<ARG_COUNT>() );
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
        std::error_code    invokeDynamic(R* res, Obj*obj, R(Obj::*fn)(Args...) const, const void** args, trait::indices<Is...>)
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
    class MethodInfo::Dynamic : public MethodInfo {
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
        Dynamic(FN function, std::string_view zName, const std::source_location& sl, Meta* parent, options_t opts=0) : 
            MethodInfo(zName, sl, parent, opts), m_function(function)
        {
            define_signature<std::remove_cvref_t<R>,Args...>();
        }

        std::error_code   _invoke(void* res, void* obj, const void** args) const override final
        {
            if(!obj)
                return errors::null_object();

            if constexpr (trait::is_returnable_v<R>){
                if(!res)
                    return errors::null_result();
            }
        
            return impl::invokeDynamic((R*) res, (Obj*) obj, m_function, args, trait::indices_gen<ARG_COUNT>() );
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
        std::error_code    invokeStatic(R* res, R(*fn)(Args...), const void** args, trait::indices<Is...>)
        {
            if constexpr (std::is_same_v<R, std::error_code>){
                return (*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
            } else  if constexpr (!std::is_same_v<R,void>){
                *(R*) res = (*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            } else {
                (*fn)(*(const std::remove_cvref_t<Args>*) args[Is]...);
                return std::error_code();
            }
        }
    }
    
    template <typename R, typename... Args>
    class MethodInfo::Static : public MethodInfo {
    public:
    
        typedef R (*FN)(Args...);
        static constexpr const size_t   ARG_COUNT   = sizeof...(Args);
        
        /*! \brief Constructor 
            \note   Only use directly this if you know what you're doing, otherwise, stay away
            \param[in] function Function pointer
            \param[in] zName    name of the property
            \param[in] sl       Source location of the definition (usually auto-picked up by the meta declare helpers
            \param[in] parent   Parent object this is apart of
            \param[in] opts     Options
        */
        Static(FN function, std::string_view zName, const std::source_location& sl, Meta* parent, options_t opts=0) : 
            MethodInfo(zName, sl, parent, opts|STATIC), m_function(function)
        {
            define_signature<std::remove_cvref_t<R>,Args...>();
        }

        std::error_code            _invoke(void* res, void* obj, const void** args) const override final
        {
            if constexpr (trait::is_returnable_v<R>){
                if(!res)
                    return errors::null_result();
            }
            return impl::invokeStatic((R*) res, m_function, args, trait::indices_gen<ARG_COUNT>() );
        }

        virtual size_t          arg_count() const noexcept override final
        {
            return ARG_COUNT;
        }

    private:
        FN      m_function;
    };
    

}
