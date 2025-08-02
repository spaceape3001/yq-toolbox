////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/UntypeMeta.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/meta/MetaWriter.hpp>

namespace yq {

    
    /*! \brief  Basic first level of type information
    
        Several derivations are being used to control how the meta type information is being generated.  
        The "Typed" is the first one, it provides the basics that everybody utilizes.
        
    */
    template <typename T>
    class UntypeMeta::Final : public UntypeMeta {
    public:
    
        /*! \brief Constructor, protected
        
            \param[in] zName    name of the type, should be from a char* in the program strings table, ie "" not dynamic.
            \param[in] sl       Source location to the instantiation (final uses default-parameter to get it)
            \param[in] i        ID to override, but most types will use AUTO
        */
        Final(std::string_view zName, const std::source_location&sl=std::source_location::current()) : UntypeMeta(zName, sl)
        {
        }

        static UntypeMeta&       s_save;
    };
 

    /*! \brief Basic type information writer
    
        This is what allows for the user-code to modify a type information. 
        
        \note it's STRONGLY advised to be in a thread-safe environment.  The `thread_safe_write()` is a sentienel
        but might not be perfect.
    */
    template <typename T>
    class UntypeMeta::Writer : public Meta::Writer {
    public:
        static_assert( MetaBinder<T>::IsDefined, "T must be meta-type declared!");
    
        //! Construct from pointer
        Writer(UntypeMeta* ti) : Meta::Writer(ti) {}
        
        //! Construct from reference (common)
        Writer(UntypeMeta& ti) : Writer(&ti) {}
    };
}

#define YQ_UNTYPE_IMPLEMENT( ... )                                                                            \
    namespace yq {                                                                                          \
        UntypeMeta&   MetaBinder<__VA_ARGS__>::edit() {                                                       \
            static auto* s_ret   = new UntypeMeta::Final<__VA_ARGS__>(#__VA_ARGS__);                          \
            return *s_ret;                                                                                  \
        }                                                                                                   \
        template <> UntypeMeta& UntypeMeta::Final<__VA_ARGS__>::s_save  = MetaBinder<__VA_ARGS__>::edit();      \
    }

