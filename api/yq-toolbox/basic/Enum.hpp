////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/container/Map.hpp>
#include <yq-toolbox/container/Vector.hpp>
#include <yq/macro/cppstring.hpp>
#include <yq-toolbox/text/IgCase.hpp>

/*
    JAVA has a really nice enumeration technique that C++ unfortunately lacks.  
    In Java we automatically have reflection, however, that's not the case
    for C++.  Therefore, we create this C++ to mimick it, giving us the ability
    to introspect, see the key/value mappings.  A bit klunky, and hopefully
    the C++ standard will evolve to have something automatec, but until then
    we'll do it this way.  (You know... maybe the compiler internals have 
    something...?  That's a TODO.)
*/


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //      MACROS
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*! \brief Declares an enumeration

    This declares an enumeration to use the Enum in this class.  This
    enumeration type provides the benefit of an automatic string/value 
    lookup because your definition gets captured by the macro.  It also 
    automatically encapsulates yoru enumeration values in a name scoped
    fashion, so it becomes YourEnum::YourValue syntax to the rest of the 
    code (ie, Java fashion, which helps avoid those name collisions between
    enumerations).
    
    The restriction is in the enumeration values, because the parser has
    to evaluate them (just once).  While the parser can understand "=number" 
    and "=OtherValue", it does not understand fancier expressions, so no math!
    
    
    \note 1: This macro will *also* create a class (cls)_base to be the 
    definition for the templated class to use.
    
    \note 2: This macro will paste the contents of your enumeration into 
             an enum {} declaration, so C rules for enums apply.  
    
    \param cls      Classname to be used.
    \param expimp   Any DLL import/exprt macro that applies (can be left blank)
    \param ...      The enumeration, C style
*/
#define YQ_ENUM(cls, expimp, ...)                                               \
    class expimp cls##_base {                                                   \
    public:                                                                     \
        enum { isEnum = 1 };                                                    \
        enum enum_t { __VA_ARGS__ };                                            \
        static const char* definition() { return YQ_CPPSTRING(__VA_ARGS__); }   \
        static const char* name() { return #cls; }                              \
        static const EnumDef*  staticEnumInfo()                                 \
        {                                                                       \
            static const EnumDef*     def = new EnumDef(name(), definition());  \
            return def;                                                         \
        }                                                                       \
        auto operator<=>(const cls##_base&) const = default;                    \
    protected:                                                                  \
        constexpr cls##_base(enum_t v) : m_value(v) {}                          \
        enum_t      m_value;                                                    \
    };                                                                          \
    typedef ::yq::EnumImpl<cls##_base> cls;

        //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

namespace yq {

    class EnumDef; 
    template <class> class EnumImpl;

    /*! \brief Generic enumerated value
    
        This is used for generic enumerated value contexts
    */
    class Enum {
    public:

        //! Null constructor
        constexpr Enum() : m_def(nullptr), m_value(-1) {}
            
        //! Value of the enumeration
        int                 value() const { return m_value; }
        
        //! Key for the current value
        std::string_view    key() const;
        
        //! \brief Assignment
        //!
        //! \note this routine will reject values not defined by the enumeration
        Enum&               operator=(int value);

        //! Equality comparison
        bool                operator==(const Enum&b) const;

        //! In equality comparison
        bool                operator!=(const Enum&b) const;

        //! Definition for the enumeration
        const   EnumDef*    definition() const { return m_def; }

        //! \brief Assignment of the enumeration
        //! \note Invalid values will be replaced by the default-value
        Enum(const EnumDef *def, int value);

    protected:
        template <class E> friend class EnumImpl;
        friend class EnumDef;

    private:
        const EnumDef*  m_def;
        int             m_value;
    };

    /*! \brief Enumeration definition
    
        This holds the mapping of value to string for the enumeration, as parsed from the
        original definition.
    */
    class EnumDef {
    public:
    
        //! Name of the enumeration
        std::string_view  name() const { return m_name; }

        //! Default value for the enumeration
        int                         default_value() const { return m_defValue; }
        
        //! Minimum value for the enumerfation
        int                         minimum_value() const;
        
        //! Maximum value for the enumeration
        int                         maximum_value() const;

        //! Value for the specified key
        Expect<int>                 value_of(std::string_view  key) const;

        //! Key for the specified value
        std::string_view            key_of(int value) const;
        
        //! Tests to see if value is present
        bool                        has_value(int value) const;
        
        //! Tests to see if key is present
        bool                        has_key(std::string_view ) const;

        //! Vector of all defined keys
        const Vector<std::string_view>&   all_keys() const { return m_keys; }
        
        //! Vector of all defined values
        Vector<int>             all_values() const;

        //! Parses comma separated key list into values
        Vector<int>             parse_comma_list(std::string_view )  const;
        
        //! Makes a comma separated key list
        std::string             make_comma_list(const Vector<int>&) const;

        //! Makes an enumeration. 
        //! \note an invalid value will return default-value
        Enum                    make_enum(int) const;
        
        //! All keys, sorted alphabetically
        const Vector<std::string_view>& sorted_keys() const { return m_sorted; }
        
        //! All keys, sorted by their underlying value
        const Vector<std::string_view>& ordered_keys() const { return m_ordered; }


        /*! Constructor
        
            WARNING, this can't be private due to constructors, don't touch it
            
            \param[in] name     STRING that'll have to persist the whole program execution
            \param[in] def      STRING that'll have to persist the whole program execution
        */
        EnumDef(const char* name, const char* def);

        using Name2Val          = Map<std::string_view,int,IgCase>;
        using Val2Name          = Map<int,std::string_view>;
        
        //! The value to name map
        const Val2Name&         val2name() const { return m_value2name; }

    protected:

    private:
        template <class> friend class EnumImpl;


        std::string_view            m_name;
        Name2Val                    m_name2value;
        Val2Name                    m_value2name;
        Vector<std::string_view>    m_keys;         //!< Keys (as parsed)
        Vector<std::string_view>    m_ordered;      //!< Keys ordered by value
        Vector<std::string_view>    m_sorted;       //!< Keys in alphabetical order
        int                         m_defValue;
    };

    /*! \brief Implements the methods for the enumerated classes
    
        As C++ enumerations cannot have methods, we have to force it, and this is how. 
        We treat the C++ enumeration as a base class, and add values to it.  
        
        \note This will have the drawback that typeid<KEY> != typeid<EnumImpl> :(
    */
    template <class E>
    class EnumImpl : public E {
    public:
        static_assert(E::isEnum, "E MUST be YQ_ENUM declared!");
        
        using StringDesc        = std::pair<std::string, typename E::enum_t>;
        using StringDescVec     = Vector<StringDesc>;
        
        //! All keys of the enumeration
        static const Vector<std::string_view>&        all_keys();
        
        //! All values of the enumeration
        static Vector<EnumImpl>             all_values();
        
        //! Default value for the enumeration
        static typename E::enum_t           default_value();
        
        //! Checks for the existence of a KEY
        static bool                         has_key(std::string_view k);
        
        //! Checks for the existence of a value
        static bool                         has_value(int);
        
        //! All keys, in order of value
        static const Vector<std::string_view>&     ordered_keys();
        
        //! All keys, alphabetically
        static const Vector<std::string_view>&    sorted_keys();
        
        //! Value for key
        static Expect<typename E::enum_t>   value_for(std::string_view txt);
        
        //! Max value defined
        static int                          max_value();
        
        //! Min value defined
        static int                          min_value();
        
        // To, make this Vector
        
        //! Turns comma separated keys into vector of values
        static Vector<EnumImpl>             comma_string(std::string_view k);
        
        //! Turns a vector of values into comma separated string
        static std::string                  comma_string(const Vector<EnumImpl>& k);

        //! Default constructor, assigns the default value
        EnumImpl() : E(default_value()) {}
        
        //! Assignment constructor, by value
        constexpr EnumImpl(const E& base) : E(base) {}
        
        //! Assignment constructor, by value
        constexpr EnumImpl(typename E::enum_t value) : E(value) {}
        
        //! Assignment constructor, value is filtered to be valid or default is used
        EnumImpl(int value) : E( has_value(value) ? (typename E::enum_t) value : default_value()) {}
        
        //! Assignment constructor, by key or default value is used
        //! \param[out] ok  pointer to bool, set to TRUE if key was understood
        EnumImpl(std::string_view key, bool *ok=nullptr)  : E({})
        {
            auto e = value_for(key);
            E::m_value = e ? *e : default_value();
            if(ok)
                *ok  = e.has_value();
        }
        
        //! Copy constructor
        EnumImpl(const EnumImpl&) = default;
        
        //! Move constructor
        EnumImpl(EnumImpl&&) = default;

        //! Implicit conversion to underlying value
        operator typename E::enum_t () const { return E::m_value; }

        //! Accessor to the value
        typename E::enum_t  value() const { return E::m_value; }
        
        //! Key for this enumeration
        std::string_view    key() const;

        //! Copy operator
        EnumImpl&   operator=(const EnumImpl&b)
        {
            E::m_value = b.E::m_value;
            return *this;
        }
        
        //EnumImpl&   operator=(EnumImpl&&b) 
        //{
            //E::m_value = b.E::m_value;
            //return *this;
        //}

        //! Assignment operator
        EnumImpl&   operator=(typename E::enum_t v);

        //  Yes, wanted to use spaceship, but caused issues
        //  TODO is to fix this

        //auto        operator<=>(const EnumImpl&) const = default;
        //auto        operator<=>(typename E::enum_t v) const { return operator<=>(EnumImpl(v)); }
        //friend auto operator<=>(typename E::enum_t a, const EnumImpl&b){ return EnumImpl(a) <=> b; }

        //bool        operator==(typename E::enum_t rhs) const { return E::m_value == rhs; }
        //bool        operator!=(typename E::enum_t rhs) const { return E::m_value != rhs; }
        
        //! Equality operator
        constexpr bool        operator==(const EnumImpl& rhs) const noexcept { return E::m_value == rhs.E::m_value; }

        //! Inequality operator
        constexpr bool        operator!=(const EnumImpl& rhs) const noexcept { return E::m_value != rhs.E::m_value; }
        
        //! Comparison (used for maps)
        constexpr bool        operator<(const EnumImpl& rhs) const noexcept { return E::m_value < rhs.E::m_value; }

        //! Equality operator
        constexpr friend bool operator==(typename E::enum_t lhs, const EnumImpl& rhs) noexcept 
        {
           return lhs == rhs.E::m_value;
        }

        //! Inequality operator
        constexpr friend bool operator!=(typename E::enum_t lhs, const EnumImpl& rhs) noexcept 
        {
            return lhs != rhs.E::m_value;
        }
        
        //! Increments the enumeration, up to max
        EnumImpl    operator++() 
        {
            if(E::m_value < max_value())
                E::m_value = (typename E::enum_t)( 1 + (int) E::m_value);
            return *this;
        }

        //! Converts vector of integers to vector of enumerated values
        static Vector<EnumImpl>         to_values(const Vector<int>& vals);
        
        //! Converts vector of enumerated values to vector of ints
        static Vector<int>              to_ints(const Vector<EnumImpl>& vals);

    private:
        static Vector<EnumImpl>         calcAllValues();
    };
    
    template <typename>     struct is_template_enum : std::false_type {};
    template <typename E>   struct is_template_enum<EnumImpl<E>> : std::true_type {};
    template <typename T>   static constexpr const bool  is_template_enum_v   = is_template_enum<T>::value;
    
    

            //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //      IMPLEMENTATION
            //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    inline bool    Enum::operator==(const Enum&b) const
    {
        return (m_def == b.m_def) && (m_value == b.m_value);
    }

    inline bool    Enum::operator!=(const Enum&b) const
    {
        return !operator==(b);
    }


            //  -------------------------------------------------------------------

    template <typename E>
    const Vector<std::string_view>& EnumImpl<E>::all_keys()
    {
        return E::staticEnumInfo()->all_keys();
    }

    template <typename E>
    Vector<EnumImpl<E>>    EnumImpl<E>::all_values()
    {
        static Vector<EnumImpl>   result = calcAllValues();
        return result;
    }

    template <typename E>
    Vector<EnumImpl<E>> EnumImpl<E>::calcAllValues()
    {
        return to_values(E::staticEnumInfo()->all_values());
    }


    template <typename E>
    Vector<EnumImpl<E>>     EnumImpl<E>::comma_string(std::string_view  k)
    {
        return toValues(E::staticEnumInfo()->parse_comma_list(k));
    }

    template <typename E>
    std::string          EnumImpl<E>::comma_string(const Vector<EnumImpl>& k)
    {
        return E::staticEnumInfo()->make_comma_list( toInts(k));
    }

    template <typename E>
    typename E::enum_t   EnumImpl<E>::default_value()
    {
        static const typename E::enum_t   ret = (typename E::enum_t) E::staticEnumInfo() -> default_value();
        return ret;
    }

    template <typename E>
    bool         EnumImpl<E>::has_key(std::string_view  k)
    {
        return E::staticEnumInfo()->has_key(k);
    }

    template <typename E>
    bool         EnumImpl<E>::has_value(int v)
    {
        return E::staticEnumInfo()->has_value(v);
    }

    template <typename E>
    const Vector<std::string_view>& EnumImpl<E>::ordered_keys()
    {
        return E::staticEnumInfo() -> ordered_keys();
    }

    template <typename E>
    const Vector<std::string_view>& EnumImpl<E>::sorted_keys()
    {
        return E::staticEnumInfo() -> sorted_keys();
    }

    template <typename E>
    Vector<int> EnumImpl<E>::to_ints(const Vector<EnumImpl>& vals)
    {
        Vector<int>      ret;
        ret.reserve(vals.size());
        for(EnumImpl v : vals)
            ret << (typename E::enum_t) v;
        return ret;
    }

    template <typename E>
    Vector<EnumImpl<E>>  EnumImpl<E>::to_values(const Vector<int>& vals)
    {
        Vector<EnumImpl>     ret;
        ret.reserve(vals.size());
        for(int v : vals){
            if(E::staticEnumInfo()->has_value(v))
                ret << EnumImpl((typename E::enum_t) v);
        }
        return ret;
    }

    template <typename E>
    Expect<typename E::enum_t>   EnumImpl<E>::value_for(std::string_view  txt)
    {
        Expect<int>   vi  =  E::staticEnumInfo()->value_of(txt);
        if(vi)
            return (typename E::enum_t) *vi;
        return std::unexpected(vi.error());
    }

    template <typename E>
    int     EnumImpl<E>::max_value()
    {
        return E::staticEnumInfo() -> maximum_value();
    }

    template <typename E>
    int     EnumImpl<E>::min_value()
    {
        return E::staticEnumInfo() -> minimum_value();
    }

        //  -------------------------------------------------------------------

    template <typename E>
    std::string_view     EnumImpl<E>::key() const
    {
        return E::staticEnumInfo()->key_of(E::m_value);
    }

    template <typename E>
    EnumImpl<E>&   EnumImpl<E>::operator=(typename E::enum_t v)
    {
        E::m_value     = v;
        return *this;
    }

    template <typename E>
    bool    is_in(EnumImpl<E> val, std::initializer_list<typename E::enum_t> vals)
    {
        for(auto& t : vals)
            if(val == t)
                return true;
        return false;
    }


    template <typename E>
    std::string_view    key(EnumImpl<E> e)
    {
        return e.key();
    }

    //template <typename E>
    //bool    EnumImpl<E>::operator==(typename E::enum_t rhs) const
    //{
        //return E::m_value == rhs;
    //}

    //template <typename E>
    //bool    EnumImpl<E>::operator!=(typename E::enum_t rhs) const
    //{
        //return E::m_value != rhs;
    //}

    template <typename E>
    std::string_view    to_string_view(EnumImpl<E> e)
    {
        return e.key();
    }

    template <typename E>
    std::string_view    to_string_view(typename E::enum_t e)
    {
        return EnumImpl<E>(e).key();
    }
}
