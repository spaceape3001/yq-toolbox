////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Map.hpp>
#include <basic/Vector.hpp>


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
        static const char* definition() { return #__VA_ARGS__; }                \
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

    class Enum {
    public:

        constexpr Enum() : m_def(nullptr), m_value(-1) {}
            
        int                 value() const { return m_value; }
        std::string_view    key() const;
        Enum&               operator=(int value);

        bool                operator==(const Enum&b) const;
        bool                operator!=(const Enum&b) const;

        const   EnumDef*    definition() const { return m_def; }

        Enum(const EnumDef *def, int value);

    protected:
        template <class E> friend class EnumImpl;
        friend class EnumDef;

    private:
        const EnumDef*  m_def;
        int             m_value;
    };

    class EnumDef {
    public:


        std::string_view  name() const { return m_name; }

        int                     default_value() const { return m_defValue; }
        int                     minimum_value() const;
        int                     maximum_value() const;

        int_r                   value_of(std::string_view  key) const;

        string_view_r           key_of(int value) const;
        bool                    has_value(int value) const;
        bool                    has_key(std::string_view ) const;

        const Vector<std::string_view>&   all_keys() const { return m_keys; }
        Vector<int>             all_values() const;

        Vector<int>             parse_comma_list(std::string_view )  const;
        std::string             make_comma_list(const Vector<int>&) const;

        Enum                    make_enum(int) const;
        
        const Vector<std::string_view>& sorted_keys() const { return m_sorted; }
        const Vector<std::string_view>& ordered_keys() const { return m_ordered; }


        /*! Constructor
        
            WARNING, this can't be private due to constructos, don't touch it
            
            \param[in] name     STRING that'll have to persist the whole program execution
            \param[in] def      STRING that'll have to persist the whole program execution
        */
        EnumDef(const char* name, const char* def);

        using Name2Val          = Map<std::string_view,int,IgCase>;
        using Val2Name          = Map<int,std::string_view>;
        
        const Val2Name&         val2name() const { return m_value2name; }

    protected:

    private:
        template <class> friend class EnumImpl;


        std::string_view            m_name;
        Name2Val                    m_name2value;
        Val2Name                    m_value2name;
        Vector<std::string_view>    m_keys;
        Vector<std::string_view>    m_ordered;      //!< Keys ordered by value
        Vector<std::string_view>    m_sorted;       //!< Keys in alphabetical order
        int                         m_defValue;
    };

    template <class E>
    class EnumImpl : public E {
    public:
        static_assert(E::isEnum, "E MUST be YQ_ENUM declared!");
        
        using StringDesc        = std::pair<std::string, typename E::enum_t>;
        using StringDescVec     = Vector<StringDesc>;
        
        static const Vector<std::string_view>&        all_keys();
        static Vector<EnumImpl>             all_values();
        static typename E::enum_t           default_value();
        static bool                         has_key(std::string_view k);
        static bool                         has_value(int);
        static const Vector<std::string_view>&     ordered_keys();
        static const Vector<std::string_view>&    sorted_keys();
        static Result<typename E::enum_t>   value_for(std::string_view txt);
        static int                          max_value();
        static int                          min_value();
        
        // To, make this Vector
        static Vector<EnumImpl>             comma_string(std::string_view k);
        static std::string                  comma_string(const Vector<EnumImpl>& k);

        EnumImpl() : E(default_value()) {}
        EnumImpl(const E& base) : E(base) {}
        constexpr EnumImpl(typename E::enum_t value) : E(value) {}
        EnumImpl(int value) : E( has_value(value) ? (typename E::enum_t) value : default_value()) {}
        EnumImpl(std::string_view key, bool *ok=nullptr) : E(value_for(key))
        {
            auto e = value_for(key);
            E::m_value = e.good ? e.value : default_value();
            if(ok)
                *ok  = e.good;
        }
        EnumImpl(const EnumImpl&) = default;
        EnumImpl(EnumImpl&&) = default;

        operator typename E::enum_t () const { return E::m_value; }

        typename E::enum_t  value() const { return E::m_value; }
        
        std::string_view    key() const;

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

        EnumImpl&   operator=(typename E::enum_t v);

        //auto        operator<=>(const EnumImpl&) const = default;
        //auto        operator<=>(typename E::enum_t v) const { return operator<=>(EnumImpl(v)); }
        //friend auto operator<=>(typename E::enum_t a, const EnumImpl&b){ return EnumImpl(a) <=> b; }

        //bool        operator==(typename E::enum_t rhs) const { return E::m_value == rhs; }
        //bool        operator!=(typename E::enum_t rhs) const { return E::m_value != rhs; }
        
        constexpr bool        operator==(const EnumImpl& rhs) const noexcept { return E::m_value == rhs.E::m_value; }
        constexpr bool        operator!=(const EnumImpl& rhs) const noexcept { return E::m_value != rhs.E::m_value; }
        constexpr bool        operator<(const EnumImpl& rhs) const noexcept { return E::m_value < rhs.E::m_value; }

        constexpr friend bool operator==(typename E::enum_t lhs, const EnumImpl& rhs) noexcept 
        {
           return lhs == rhs.E::m_value;
        }

        constexpr friend bool operator!=(typename E::enum_t lhs, const EnumImpl& rhs) noexcept 
        {
            return lhs != rhs.E::m_value;
        }
        
        EnumImpl    operator++() 
        {
            if(E::m_value < max_value())
                E::m_value = (typename E::enum_t)( 1 + (int) E::m_value);
            return *this;
        }

        static Vector<EnumImpl>         to_values(const Vector<int>& vals);
        static Vector<int>              to_ints(const Vector<EnumImpl>& vals);

    private:
        static Vector<EnumImpl>         calcAllValues();
    };

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
    Result<typename E::enum_t>   EnumImpl<E>::value_for(std::string_view  txt)
    {
        int_r   vi  =  E::staticEnumInfo()->value_of(txt);
        return vi.cast_to<typename E::enum_t>();
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
