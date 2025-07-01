////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/OperatorMeta.hpp>
#include <yq/meta/MethodMetaImpl.hpp>

namespace yq {
    template <typename R, typename... Args>
    class OperatorMeta::Static : public OperatorMeta {
    public:
    
        typedef R (*FN)(Args...);
        static constexpr const size_t   ARG_COUNT   = sizeof...(Args);
        
        /*! \brief Constructor 
            \note   Only use directly this if you know what you're doing, otherwise, stay away
            \param[in] function Function pointer
            \param[in] opId     Operator of the operator
            \param[in] sl       Source location of the definition (usually auto-picked up by the meta declare helpers
            \param[in] parent   Parent object this is apart of
        */
        Static(FN function, Operator opId, const std::source_location& sl, Meta* parent) : 
            OperatorMeta(opId, sl, parent), m_function(function)
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
