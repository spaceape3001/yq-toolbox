////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

    //  Separating the header files since there's some interdependency issues.


//#include <0/basic/preamble.hpp>
#include <yq/keywords.hpp>
#include <yq/meta/forward.hpp>
#include <yq/meta/DataBlock.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/typedef/any.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_initlists.hpp>

namespace yq {
    class Stream;
    template <typename> struct Result;

    /*! \brief Generic Data

        A Any is generic data, it's meant to be unobtrusive.  
    */
    class Any {
    public:

        static any_error_t      parse_me(const TypeInfo&, std::string_view);

        Any();
        Any(const Any&);
        Any(Any&&);
        
        //! Creates a defaulted Any to the specified meta-type
        explicit Any(const TypeInfo&);
        explicit Any(const TypeInfo*);
        
        explicit Any(char);
        explicit Any(char8_t);
        explicit Any(char32_t);
        explicit Any(char*);
        explicit Any(const char*);
        explicit Any(const char8_t*);
        explicit Any(const char32_t*);
        explicit Any(const std::u8string&);
        explicit Any(const std::u32string&);
        explicit Any(const std::wstring&);
    #ifdef ENABLE_QT
        explicit Any(const QString&);
    #endif
    
        Any(parse_k, const TypeInfo&, std::string_view);
        Any(parse_k, const TypeInfo&, std::string_view, throw_k);
        Any(parse_k, const TypeInfo&, std::string_view, no_throw_k);
        Any(parse_k, const TypeInfo&, std::string_view, std::error_code&);

        /*! \brief Direct construction constructor
        
            This directly creates a variant with the argument.
            
            \note EXPLICIT is required to keep the compiler from getting greedy.
        */
        template <typename T>
        requires (!std::is_same_v<T,Any>)
        explicit Any(T&&);

        ~Any();

        Any&        operator=(const Any&);
        Any&        operator=(Any&&);
        
        template <typename T>
        requires (is_type_v<std::decay_t<T>> && !std::is_same_v<T,Any>)
        Any&        operator=(T&&);
        
        bool            operator==(const Any&) const;
        
        template <typename T>
        requires (is_type_v<std::decay_t<T>> && !std::is_same_v<T,Any>)
        bool        operator==(const T&) const;
        //template <typename T>
        //bool        operator!=(const T&) const;
        
        bool        can_convert(const TypeInfo&) const;
        template <typename T>
        bool        can_convert() const;
        
        bool        can_print() const;

        bool        can_write() const;
        bool        can_write_and_parse() const;

        //! Returns a variant that's been converted
        any_x       convert(const TypeInfo&) const;

        template <typename T>
        any_x       convert() const;

        bool            is_valid() const;

        //Any         get_field(const std::string&) const;
        
        /*! \brief Parses into the any, overwriting
        */
        std::error_code     parse(const TypeInfo&, const std::string_view&);
        
        
        /*! \brief Parses into the variant, overwriting
        
            Type info is assumed to be STRING if variant is invalid.
        */
        std::error_code     parse(const std::string_view&);
        
        
        
        /*! \brief Debug writing to stream
        
            This is meant for printing casually to the screen for the user's benefit (debugging, alerts, etc),
            therefore, we'll opt for being concise over precision (ie. missing lesser bits is alright).
        */
        std::error_code     print(Stream&, std::string_view k={}) const;
        
        /*! \brief Debug writing to stream
        
            This is meant for printing casually to the screen for the user's benefit (debugging, alerts, etc),
            therefore, we'll opt for being concise over precision (ie. missing lesser bits is alright).
        */
        std::error_code     print(Stream&, string_view_initializer_list_t keys) const;

        /*! \brief Debug writing to stream
        
            This is meant for printing casually to the screen for the user's benefit (debugging, alerts, etc),
            therefore, we'll opt for being concise over precision (ie. missing lesser bits is alright).
        */
        std::error_code     print(cerr_t, std::string_view k={}) const;
        
        /*! \brief Debug writing to stream
        
            This is meant for printing casually to the screen for the user's benefit (debugging, alerts, etc),
            therefore, we'll opt for being concise over precision (ie. missing lesser bits is alright).
        */
        std::error_code     print(cerr_t, string_view_initializer_list_t keys) const;
        
        /*! \brief Debug writing to stream
        
            This is meant for printing casually to the screen for the user's benefit (debugging, alerts, etc),
            therefore, we'll opt for being concise over precision (ie. missing lesser bits is alright).
        */
        std::error_code     print(cout_k, std::string_view k={}) const;
        
        /*! \brief Debug writing to stream
        
            This is meant for printing casually to the screen for the user's benefit (debugging, alerts, etc),
            therefore, we'll opt for being concise over precision (ie. missing lesser bits is alright).
        */
        std::error_code     print(cout_k, string_view_initializer_list_t keys) const;

        /*! \brief "Printable" version for debugging/general-output
        
            \note There's no corresponding "parse" (deliberate), see the I/O helpers
        */
        std::string          printable(std::string_view k={}) const;
        
        /*! \brief Guarded pointer
            Returns the pointer *IF* it's feasible, otherwise null
        */
        template <typename T>
        T*              ptr();

        /*! \brief Guarded pointer
            Returns the pointer *IF* it's feasible, otherwise null
        */
        template <typename T>
        const T*        ptr() const;

        //! Returns pointer *REGARDLESS* of feasibility
        template <typename T>
        const T*        unsafe_ptr() const;
        
        //! Raw pointer to void
        const void*         raw_ptr() const;
        //! Raw pointer to void
        void*               raw_ptr();
        
        template <typename T>
        const T&            ref(const T& bad={}) const;
        

        //bool        set_field(const std::string&, const Any&);

        

        const TypeInfo& type() const { return *m_type; }

        bool                valid() const { return is_valid(); }

        template <typename T>
        Result<const T&>    value() const;
        
        /*! \brief IO Writing to stream
        
            This is meant to write the data out in a way that'll fully capture the input (ie better to have a thousand 
            decimals over missing a bit).  If not present and it's a compound object, then the algorithm driving this
            ought to delve deeper.
            
            \brief TRUE if properly delegated
        */
        std::error_code write(Stream&) const;

        std::string     writable() const;


        /*! \brief The "I-KNOW-WHAT-I'M-DOING" constructor
        
            This routine blindly assumes the caller knows what they're doing, so here's the type and here's a pointer
            to the data.  A null pointer will force a default construction.
        */
        Any(const TypeInfo&, const void*);

        const DataBlock&    data() const { return m_data; }

        template <typename T>
        static Any  from(T&&);

    private:
        Any(TypeInfo&&) = delete;   // prohibt temporary metatypes

        const TypeInfo*     m_type;
        DataBlock           m_data;
        
        Any(const TypeInfo&&) = delete;
        
        
        template <typename T>
        void    set(T&&val);
        
        void    set(std::string&&);
        void    set(std::string_view);
        
        void    set(const TypeInfo&, const void*);
        void    clear();
        
        //! Checks to make sure the type info is populated to the minimum specification
        static bool    good(const TypeInfo&);
        
    };
}


