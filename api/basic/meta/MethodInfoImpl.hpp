////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/MethodInfo.hpp>
#include <basic/meta/TypedArgInfo.hpp>
#include <type_traits>

namespace yq {

    template <typename...> 
    struct MethodInfo::DefineArg {
        void    define(const std::source_location&, Meta*, options_t options)
        {
        }
    };
    
    template <typename T, typename... Args> 
    struct MethodInfo::DefineArg<T, Args...> {
        void    define(const std::source_location&sl, Meta*parent, options_t options)
        {
            m_args.push_back( new ArgInfo::Typed<T>(sl, parent, options));
            DefineArg<Args...>::define(sl, parent, options);
        }
    };

    template <typename R, typename...Args> 
    void MethodInfo::define_signature(options_t opts)
    {
        if constexpr (!std::is_same_v<R,void>){
            m_result    = new ArgInfo::Typed<R>(source(), this);
        }
    
        DefineArg<Args...>::define(source(), this, opts);
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename R, typename Obj, typename... Args>
    class MethodInfo::Const : public MethodInfo {
    public:

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
            MethodInfo(zName, sl, parent, opts), m_function(function)
        {
            define_signature<R,Args...>();
        }

        void            _invoke(void* res, void* obj, const void** args) const override final
        {
            // TODO
        }

    private:
        FN      m_function;
    };

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename R, typename Obj, typename... Args>
    class MethodInfo::Dynamic : public MethodInfo {
    public:

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
            define_signature<R,Args...>();
        }

        void            _invoke(void* res, void* obj, const void** args) const override final
        {
            // TODO
        }

    private:
        FN      m_function;
    };


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    template <typename R, typename... Args>
    class MethodInfo::Static : public MethodInfo {
    public:
    
        typedef R (*FN)(Args...);
        
        /*! \brief Constructor 
            \note   Only use directly this if you know what you're doing, otherwise, stay away
            \param[in] function Function pointer
            \param[in] zName    name of the property
            \param[in] sl       Source location of the definition (usually auto-picked up by the meta declare helpers
            \param[in] parent   Parent object this is apart of
            \param[in] opts     Options
        */
        Static(FN function, std::string_view zName, const std::source_location& sl, Meta* parent, options_t opts=0) : 
            MethodInfo(zName, sl, parent, opts), m_function(function)
        {
            define_signature<R,Args...>();
        }

        void            _invoke(void* res, void* obj, const void** args) const override final
        {
            // TODO
        }

    private:
        FN      m_function;
    };
    

}
