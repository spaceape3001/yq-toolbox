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
            
        /*! \brief Returns all current type infos
            \note WARNING Unsafe in unlocked multithreaded mode (as this isn't a copy, 
                    its the actual list that could be changing.)
        */
        static const Vector<const TypeInfo*>&   all();
        
        //! Finds the type info by ID
        static const TypeInfo*                  find(id_t);

        //! Finds the type info by name
        static const TypeInfo*                  find(std::string_view);
        
        //! Finds the type info of a set
        //! \param[in] Noisy    TRUE will dump failures-to-find to the log
        static Vector<const TypeInfo*>          find_all(const string_set_t&, bool noisy=false);
    
        //! All aliases for this type info
        const Vector<std::string_view>&         aliases() const { return m_aliases; }
    
        //! TRUE if this type has a string parser defined for it
        bool        can_parse() const { return m_parse != nullptr; }
        
        //! TRUE if this type has a write function defined for it
        bool        can_write() const { return m_write != nullptr; }
        
        //! TRUE if this type has a print function defined for it
        bool        can_print() const { return m_print != nullptr; }

        //! The "generic" classification for this meta which is type.
        virtual const char*     generic() const override { return "Type"; }

        //! TRUE if this type is marked as small (ie, a datablock in size or smaller)
        bool        is_small() const { return static_cast<bool>(flags() & SMALL); }

        //! Byte size of the type represented by this info
        size_t      size() const { return m_size; }
    
        //! Helper for registering type information
        template <typename T> class Writer;
        
        template <typename T> class Typed;      //  Base type
        template <typename T> class Special;    //  Allows for specialization
        template <typename T> class Final;      //  Final one for storing the type info

        //! Number of methods for this type
        size_t                              method_count() const;
        
        //! List of methods for this type
        const Vector<const MethodInfo*>&    methods() const;

        //! Number of properties for this type
        size_t                              property_count() const;
        
        //! List of properties for this type
        const Vector<const PropertyInfo*>&  properties() const;

        /*! \brief Parsing helper
        
            This will parse the string view into the type using the registered parser function.
            
            \tparam Type of the data being parse (inferred)
            \param[out] data    Data goes here
            \param[in]  str     String view to be parsed
            \return TRUE  if successful (both in type info lookup and actual parsing), FALSE if not
            
        */
        template <typename T>
        static bool parse(T&data, std::string_view str);
        
        /*! \brief Writing helper
        
            This will write the data to the stream using the registered formatting function.
            
            \param[in] data Data goes here
            \param[out] str Stream goes here
            
            \return TRUE if successful (ie, type is registered with formatting function.
        */
        template <typename T>
        static bool write(const T&data, Stream&str);
        
        /*! \brief Printing helper
        
            THis will print the data to the stream using the registered function.

            \param[in] data Data goes here
            \param[out] str Stream goes here
            
            \return TRUE if successful (ie, type is registered with formatting function.
        */
        template <typename T>
        static bool print(const T&data, Stream&str);
        
    protected:
    
        /*! \brief Constructor 
        
            \note Only used this if you know what you're up to
            
            \param[in] zName        the type's name [note this is NOT copied, so needs to remain valid]
            \param[in] sl           Source location it's being done
            \param[in] i            Any assigned ID override
        */
        TypeInfo(std::string_view zName, const std::source_location& sl, id_t i=AUTO_ID);
        
        //! Destructor that should never fire
        virtual ~TypeInfo();

        //! Adds an alias to the type (note view is NOT copied, so should come from program strings "" )
        void            add_alias(std::string_view);

        //! Sweeps on the type (ie gathers properties/methdos)
        virtual void    sweep_impl() override;

        //! Function to convert between types
        typedef void        (*FNConvert)(void*, const void*);
        
        //! Function to copy the data, block to block
        typedef void        (*FNCopyBlkBlk)(DataBlock&, const DataBlock&);

        //! Function to copy the data, raw to block
        typedef void        (*FNCopyRawBlk)(DataBlock&, const void*);

            //  COPY CONSTRUCTORS
        //! Function to construct the data into a block from a raw pointer
        typedef void        (*FNCtorCopyRawBlk)(DataBlock&, const void*);
        //! Function to construct the data into a block from another data block
        typedef void        (*FNCtorCopyBlkBlk)(DataBlock&, const DataBlock&);

            //  MOVE CONSTRUCTORS
        //! Function to move the data (as a move constructor) from block to block
        typedef void        (*FNCtorMove)(DataBlock&, DataBlock&&);

            //  DESTRUCTOR
        //! Function to delete from a data block
        typedef void        (*FNDtor)(DataBlock&);

        //! Function to compare two data blocks
        typedef bool        (*FNCompare)(const DataBlock&, const DataBlock&);
        //! Function to move between data blocks
        typedef void        (*FNMoveBlkBlk)(DataBlock&, DataBlock&&);
        //! Function to format to stream
        typedef void        (*FNFormat)(Stream&, const void*);
        //! Function to parse from string
        typedef bool        (*FNParse)(void*, const std::string_view&);

        //! Function to write to XML
        typedef void        (*FNXmlBaseWrite)(XmlBase*, const void*);
        
        //! Function to read from XML
        typedef bool        (*FNXmlBaseRead)(void*, const XmlBase*);

        //! Function to write to XML Node
        typedef void        (*FNXmlNodeWrite)(XmlNode*, const void*);
        
        //! Function to read from XML Node
        typedef bool        (*FNXmlNodeRead)(void*, const XmlNode*);

        //! Converter hash
        using ConvertHash   = Hash<const TypeInfo*, FNConvert>;
        friend class PropertyInfo;
        friend class MethodInfo;
        
        //! Properties for this type
        LUC<PropertyInfo>           m_properties;
        
        //! Method for this type
        LUC<MethodInfo>             m_methods;
        
        //! Default for this type
        DataBlock                   m_default;
        
        //! Aliases for this type
        Vector<std::string_view>        m_aliases;
        
        struct {
            //! Template arguments for this type
            Vector<const TypeInfo*> args;
            
            //!  total number of parameters (typed or not)
            unsigned                params          = 0;
        }                           m_template;

        //! Size of this type
        size_t                  m_size              = 0;
        
        //! Converters for this type
        ConvertHash             m_convert;
        
        //! Our block=>block copy operator
        FNCopyBlkBlk            m_copyB         = nullptr;

        //! Our raw=>block copy operator
        FNCopyRawBlk            m_copyR         = nullptr;
        
        //! Our copy constructor (from raw pointer)
        FNCtorCopyRawBlk        m_ctorCopyR     = nullptr;

        //! Our copy constructor (from another block)
        FNCtorCopyBlkBlk        m_ctorCopyB     = nullptr;
        
        //! Our move constructor (from another block)
        FNCtorMove              m_ctorMove      = nullptr;
        
        //! Destructor from block
        FNDtor                  m_dtor          = nullptr;
        
        //! Equality comparison
        FNCompare               m_equal         = nullptr;
        
        //! Less than comparison
        FNCompare               m_less          = nullptr;
        
        //! Move operator (block to block)
        FNMoveBlkBlk            m_moveB         = nullptr;
        
        //! Text formatting for human eyes
        FNFormat                m_print         = nullptr;

        //! Text formatting for data storage
        FNFormat                m_write         = nullptr;
        
        //! Text parsing for data storage
        FNParse                 m_parse         = nullptr;
        
        //! XML writing to base as value
        FNXmlBaseWrite          m_xbwrite       = nullptr;
        
        //! XML reading from base as value
        FNXmlBaseRead           m_xbread        = nullptr;
        
        //! XML writing to node as value
        FNXmlNodeWrite          m_xnwrite       = nullptr;

        //! XML reading from node as value
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
