////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <0/meta/Meta.hpp>
#include <0/meta/ArgInfo.hpp>
#include <span>

namespace yq {
    class MethodInfo : public Meta {
    public:
    
        template <typename R, typename... Args> class Writer;
    
        template <typename R, typename Obj, typename... Args> class Const;
        template <typename R, typename Obj, typename... Args> class Dynamic;
        template <typename R, typename... Args> class Static;
    
        const std::vector<const ArgInfo*>&  args() const { return m_args; }
        
        //! Result (if any), otherwise null
        const ArgInfo*          result() const { return m_result; }
    
        //! Invoke with flexibility if the any can convert to the appropriate type
        Expect<Any>             invoke(void* obj, std::span<const Any> args) const;
        Expect<Any>             invoke(const void* obj, std::span<const Any> args) const;
        
        //! Invokes for a static function (will error if not)
        Expect<Any>             invoke(std::span<const Any> args) const;
    

        virtual size_t          arg_count() const noexcept = 0;
        
        //! Computes the type match
        //!
        //! If there's a total mismatch, -1 is returned, 0 is a perfect match, higher numbers indicate it's possible but some conversion is required
        int                     type_match(std::span<const Any> args) const;

    protected:
        const ArgInfo*              m_result;
        std::vector<const ArgInfo*> m_args;

        MethodInfo(std::string_view zName, const std::source_location& sl, Meta*);

        Expect<Any>            invoke(void* obj, std::span<const Any> args, bool constPtr) const;

        /*! Invoke with the exact types
        
            Invoke the method, assuming the provided arguments are *CORRECT*
            
            \param[in,out]  res     Pointer to the result location
            \param[in]      obj     Pointer to the object
            \param[in]      args    Pointer to the arguments
        */
        virtual std::error_code _invoke(void* res, void* obj, const void* const * args) const = 0;
        
        template <typename...> struct DefineArg;
        template <typename R, typename...> void define_signature();
        
        void    fill_argument_info(size_t, std::string_view zName, std::string_view zDescription);
        void    fill_result_info(std::string_view zName, std::string_view zDescription);
    };
}
