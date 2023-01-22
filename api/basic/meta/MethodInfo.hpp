////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/meta/Meta.hpp>
#include <basic/meta/ArgInfo.hpp>

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
        //virtual bool            invoke(Any& res, void* obj, const std::vector<Any>&args) const = 0;
    
    private:
        const ArgInfo*              m_result;
        std::vector<const ArgInfo*> m_args;
        MethodInfo(std::string_view zName, const std::source_location& sl, Meta*, options_t opts=0);

        /*! Invoke with the exact types
        
            Invoke the method, assuming the provided arguments are *CORRECT*
            
            \param[in,out]  res     Pointer to the result location
            \param[in]      obj     Pointer to the object
            \param[in]      args    Pointer to the arguments
        */
        virtual bool            _invoke(void* res, void* obj, const void** args) const = 0;
        
        template <typename...> struct DefineArg;
        template <typename R, typename...> void define_signature(options_t options=0);
        
        void    fill_argument_info(size_t, std::string_view zName, std::string_view zDescription, options_t extraOptions);
        void    fill_result_info(std::string_view zName, std::string_view zDescription, options_t extraOptions);
    };
}
