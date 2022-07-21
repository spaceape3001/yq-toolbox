////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/meta/InfoBinder.hpp>
#include <basic/meta/CompoundInfo.hpp>
#include <basic/preamble.hpp>
#include <unordered_map>

namespace yq {
    /* \brief Declares a type that can be stored unobtrusively
    */
    class TypeInfo : public CompoundInfo {
        friend class Any;
    public:
    
            // WARNING UNSAFE IN UNLOCKED MULTITHREADED MODE!
        static const Vector<const TypeInfo*>&   all();
        static const TypeInfo*                  find(id_t);
        static const TypeInfo*                  find(std::string_view);
        static Vector<const TypeInfo*>          find_all(const string_set_t&, bool noisy=false);
    
        const Vector<std::string_view>&         aliases() const { return m_aliases; }
    
        bool        can_parse() const { return m_parse ? true : false; }
        bool        can_write() const { return m_write ? true : false; }
        bool        can_print() const { return m_print ? true : false; }

        virtual const char*     generic() const override { return "Type"; }

        bool        is_small() const { return static_cast<bool>(flags() & SMALL); }

        size_t      size() const { return m_size; }
    
        
        template <typename T> class Writer;
        template <typename T> class Typed;      //  base type
        template <typename T> class Special;    //  allows for specialization
        template <typename T> class Final;      //  Final one for storing


        size_t                              method_count() const;
        const Vector<const MethodInfo*>&    methods() const;

        size_t                              property_count() const;
        const Vector<const PropertyInfo*>&  properties() const;

        template <typename T>
        static bool parse(T&, std::string_view);
        template <typename T>
        static bool write(const T&, Stream&);
        template <typename T>
        static bool print(const T&, Stream&);
        
    protected:
        TypeInfo(std::string_view zName, const std::source_location& sl, id_t i=AUTO_ID);
        virtual ~TypeInfo();

        void            add_alias(std::string_view);

        virtual void    sweep_impl() override;

        typedef void        (*FNConvert)(void*, const void*);
        typedef void        (*FNCopyBlkBlk)(DataBlock&, const DataBlock&);
        typedef void        (*FNCopyRawBlk)(DataBlock&, const void*);

            //  COPY CONSTRUCTORS
        typedef void        (*FNCtorCopyRawBlk)(DataBlock&, const void*);
        typedef void        (*FNCtorCopyBlkBlk)(DataBlock&, const DataBlock&);

            //  MOVE CONSTRUCTORS
        typedef void        (*FNCtorMove)(DataBlock&, DataBlock&&);

            //  DESTRUCTOR
        typedef void        (*FNDtor)(DataBlock&);

        typedef bool        (*FNCompare)(const DataBlock&, const DataBlock&);
        typedef void        (*FNMoveBlkBlk)(DataBlock&, DataBlock&&);
        typedef void        (*FNFormat)(Stream&, const void*);
        typedef bool        (*FNParse)(void*, const std::string_view&);

        typedef void        (*FNXmlBaseWrite)(XmlBase*, const void*);
        typedef bool        (*FNXmlBaseRead)(void*, const XmlBase*);
        typedef void        (*FNXmlNodeWrite)(XmlNode*, const void*);
        typedef bool        (*FNXmlNodeRead)(void*, const XmlNode*);

    
        using ConvertHash   = Hash<const TypeInfo*, FNConvert>;
        friend class PropertyInfo;
        friend class MethodInfo;
        
    
        LUC<PropertyInfo>           m_properties;
        LUC<MethodInfo>             m_methods;
        DataBlock                   m_default;
        
        Vector<std::string_view>        m_aliases;
        
        struct {
            Vector<const TypeInfo*> args;
            
            //!  total number of parameters (typed or not)
            unsigned                params          = 0;
        }                           m_template;

        size_t                  m_size              = 0;
        ConvertHash             m_convert;
        
        FNCopyBlkBlk            m_copyB         = nullptr;
        FNCopyRawBlk            m_copyR         = nullptr;
        FNCtorCopyRawBlk        m_ctorCopyR     = nullptr;
        FNCtorCopyBlkBlk        m_ctorCopyB     = nullptr;
        FNCtorMove              m_ctorMove      = nullptr;
        FNDtor                  m_dtor          = nullptr;
        FNCompare               m_equal         = nullptr;
        FNCompare               m_less          = nullptr;
        FNMoveBlkBlk            m_moveB         = nullptr;
            // Print is for user eyes
        FNFormat                m_print         = nullptr;
            // Format is for data storage
        FNFormat                m_write         = nullptr;
        FNParse                 m_parse         = nullptr;
        
        FNXmlBaseWrite          m_xbwrite       = nullptr;
        FNXmlBaseRead           m_xbread        = nullptr;
        FNXmlNodeWrite          m_xnwrite       = nullptr;
        FNXmlNodeRead           m_xnread        = nullptr;
    };
    
    /*! \brief Converts meta to type, if it's valid
    
        \return TypeInfo pointer, if valid, NULL otherwise
    */
    inline const TypeInfo* to_type(const Meta* m)
    {
        return (m && (m->flags() & TYPE)) ? static_cast<const TypeInfo*>(m) : nullptr;
    }
    
    /*! \brief Converts meta to type, if it's valid
    
        \return TypeInfo pointer, if valid, NULL otherwise
    */
    inline TypeInfo* to_type(Meta* m)
    {
        return (m && (m->flags() & TYPE)) ? static_cast<TypeInfo*>(m) : nullptr;
    }

    template <typename T>
    bool TypeInfo::parse(T&value, std::string_view sv)
    {
        static_assert( is_defined_v<T>, "T must be meta-type capable!");
        const TypeInfo& ti  = meta<T>();
        if(ti.m_parse)
            return ti.m_parse(&value, sv);
        return false;
    }

    template <typename T>
    bool TypeInfo::print(const T&value, Stream&str)
    {
        static_assert( is_defined_v<T>, "T must be meta-type capable!");
        const TypeInfo& ti  = meta<T>();
        if(!ti.m_print)
            return false;
        ti.m_print(str, &value);
        return true;
    }

    template <typename T>
    bool TypeInfo::write(const T&value, Stream&str)
    {
        static_assert( is_defined_v<T>, "T must be meta-type capable!");
        const TypeInfo& ti  = meta<T>();
        if(!ti.m_write)
            return false;
        ti.m_write(str, &value);
        return true;
    }
    
    
}
