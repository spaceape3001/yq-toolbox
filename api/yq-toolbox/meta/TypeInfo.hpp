////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/meta/CompoundInfo.hpp>
#include <yq-toolbox/meta/MetaLookup.hpp>
#include <yq-toolbox/meta/OperatorInfo.hpp>
#include <yq-toolbox/errors.hpp>
#include <yq/typedef/string_initlists.hpp>
#include <yq/typedef/xml.hpp>
#include <unordered_map>
#include <span>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /* \brief Declares a type that can be stored unobtrusively
    */
    class TypeInfo : public CompoundInfo {
        friend class Any;
    public:
        using MethodLUC     = MetaLookup<MethodInfo>;
        using OperatorLUC   = MetaLookup2<OperatorInfo,Operator,&OperatorInfo::code>;
        using PropertyLUC   = MetaLookup<PropertyInfo>;
        using TypeInfoLUC   = MetaLookup<TypeInfo>;
    
            // WARNING UNSAFE IN UNLOCKED MULTITHREADED MODE!
            
        /*! \brief Returns all current type infos
            \note WARNING Unsafe in unlocked multithreaded mode (as this isn't a copy, 
                    its the actual list that could be changing.)
        */
        static const std::vector<const TypeInfo*>&   all();
        
        //! Finds the type info by ID
        static const TypeInfo*                  find(id_t);

        //! Finds the type info by name
        static const TypeInfo*                  find(std::string_view);
        
        //! Finds the type info of a set
        //! \param[in] Noisy    TRUE will dump failures-to-find to the log
        static std::vector<const TypeInfo*>     find_all(const string_set_t&, bool noisy=false);
        
        //! Returns the *FIRST* match
        static const TypeInfo*                  find(stem_t, std::string_view);
    
        //! All aliases for this type info
        //const std::vector<std::string_view>&    aliases() const { return m_aliases; }
        
        //! TRUE if this type has a string parser defined for it
        bool        can_parse() const { return m_parse != nullptr; }
        
        //! TRUE if this type has a write function defined for it
        bool        can_write() const { return m_write != nullptr; }
        
        //! TRUE if this type has a print function defined for it
        bool        can_print() const { return m_print != nullptr; }
        
        bool        can_convert_to(const TypeInfo& otherType) const;

        const std::vector<const ConstructorInfo*>& constructors() const { return m_constructors; }

        //! Copy (trusting)
        std::error_code copy(void*dst, const void*src) const;
        
        //! Copy (checking src type)
        std::error_code copy(void*dst, const void*src, const TypeInfo& srcType) const;
        
        template <typename T>
        std::error_code copy(void* dst, const T&src) const
        {
            return copy(dst, &src, meta<T>());
        }
    
        //! The "generic" classification for this meta which is type.
        virtual const char*     generic() const override { return "Type"; }


        //! Byte size of the type represented by this info
        size_t      size() const { return m_size; }
    
        //! Helper for registering type information
        template <typename T> class Writer;
        
        template <typename T> class Typed;      //  Base type
        template <typename T> class Special;    //  Allows for specialization
        template <typename T> class Final;      //  Final one for storing the type info

        //! Number of methods for this type
        size_t                                  method_count() const;
        
        //! List of methods for this type
        const std::vector<const MethodInfo*>&   methods() const;

        //! List of operators for this type
        const std::vector<const OperatorInfo*>& operators() const;
        
        //! All operators for the specified operator
        const OperatorLUC::equal_range_t        operators(Operator) const;

        size_t                                  operators_count() const;
        

        const PropertyInfo*                     property(std::string_view) const;

        //! Number of properties for this type
        size_t                                  property_count() const;
        
        //! List of properties for this type
        const std::vector<const PropertyInfo*>&  properties() const;

        PropertyLUC::equal_range_t              properties(std::string_view) const;

        /*! \brief Parsing helper
        
            This will parse the string view into the type using the registered parser function.
            
            \tparam Type of the data being parse (inferred)
            \param[out] data    Data goes here
            \param[in]  str     String view to be parsed
            \return TRUE  if successful (both in type info lookup and actual parsing), FALSE if not
            
        */
        template <typename T>
        static std::error_code parse(T&data, std::string_view str);
        
        /*! \brief Writing helper
        
            This will write the data to the stream using the registered formatting function.
            
            \param[in] data Data goes here
            \param[out] str Stream goes here
            
            \return TRUE if successful (ie, type is registered with formatting function.
        */
        template <typename T>
        static std::error_code write(const T&data, Stream&str);
        
        /*! \brief Printing helper
        
            THis will print the data to the stream using the registered function.

            \param[in] data Data goes here
            \param[out] str Stream goes here
            
            \return TRUE if successful (ie, type is registered with formatting function.
        */
        template <typename T>
        static std::error_code print(const T&data, Stream&str);
        
        template <typename Pred>
        auto            all_functions(std::string_view k, Pred pred) const;

        //! Function to convert between types
        typedef std::error_code  (*FNConvert)(void*, const void*);
        
        //! Function to copy the data, block to block
        typedef void        (*FNCopyBlkBlk)(DataBlock&, const DataBlock&);

        //! Function to copy the data, raw to block
        typedef void        (*FNCopyRawBlk)(DataBlock&, const void*);

        //! Function to copy the data, raw to block
        typedef void        (*FNCopyRawRaw)(void*, const void*);

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
        typedef std::error_code  (*FNParse)(void*, const std::string_view&);

        //! Function to write to XML
        typedef void        (*FNXmlBaseWrite)(XmlBase*, const void*);
        
        //! Function to read from XML
        typedef std::error_code  (*FNXmlBaseRead)(void*, const XmlBase*);

        //! Function to write to XML Node
        typedef void        (*FNXmlNodeWrite)(XmlNode*, const void*);
        
        //! Function to read from XML Node
        typedef std::error_code (*FNXmlNodeRead)(void*, const XmlNode*);

        
        FNConvert           converter(const TypeInfo&) const;


    protected:
    
        friend class PropertyInfo;
        friend class MethodInfo;
        friend class OperatorInfo;
        friend class ConstructorInfo;

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
        virtual void    add_alias(std::string_view) override;

        //! Sweeps on the type (ie gathers properties/methdos)
        virtual void    sweep_impl() override;


        //! Converter hash
        using ConvertHash   = Hash<const TypeInfo*, FNConvert>;
        
        //! Method for this type
        std::vector<const ConstructorInfo*> m_constructors;

        //! Default for this type
        DataBlock                   m_default;
        
        //! Method for this type
        MethodLUC                   m_methods;

        OperatorLUC                 m_operators;
        
        //! Properties for this type
        PropertyLUC                 m_properties;
        
        //! Aliases for this type
        //std::vector<std::string_view>   m_aliases;
        
        struct {
            //! Template arguments for this type
            std::vector<const TypeInfo*> args;
            
            //!  total number of parameters (typed or not)
            unsigned                params          = 0;
        }                       m_template;

        //! Size of this type
        size_t                  m_size              = 0;
        
        //! Converters for this type
        ConvertHash             m_convert;
        
        //! Our block=>block copy operator
        FNCopyBlkBlk            m_copyB         = nullptr;

        //! Our raw=>block copy operator
        FNCopyRawBlk            m_copyR         = nullptr;
        
        //! Our raw=>raw copy operator
        FNCopyRawRaw            m_copyRR        = nullptr;
        
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

        //! Map of "slot" to formatters
        std::map<std::string_view,FNFormat,IgCase>  m_printers;

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
        
        FNFormat        printer(std::string_view) const;
        
        FNFormat        printer(string_view_initializer_list_t) const;
        
        void            add_printer(std::string_view, FNFormat);
    };
    
    /*! \brief Converts meta to type, if it's valid
    
        \return TypeInfo pointer, if valid, NULL otherwise
    */
    const TypeInfo* to_type(const Meta* m);

    const TypeInfo* to_type(const Meta& m);
    
    /*! \brief Converts meta to type, if it's valid
    
        \return TypeInfo pointer, if valid, NULL otherwise
    */
    TypeInfo* to_type(Meta* m);

    template <typename T>
    std::error_code TypeInfo::parse(T&value, std::string_view sv)
    {
        static_assert( is_defined_v<T>, "T must be meta-type capable!");
        const TypeInfo& ti  = meta<T>();
        if(!ti.m_parse)
            return errors::no_handler();
        return ti.m_parse(&value, sv);
    }

    template <typename T>
    std::error_code TypeInfo::print(const T&value, Stream&str)
    {
        static_assert( is_defined_v<T>, "T must be meta-type capable!");
        const TypeInfo& ti  = meta<T>();
        if(!ti.m_print)
            return errors::no_handler();
        ti.m_print(str, &value);
        return {};
    }

    template <typename T>
    std::error_code TypeInfo::write(const T&value, Stream&str)
    {
        static_assert( is_defined_v<T>, "T must be meta-type capable!");
        const TypeInfo& ti  = meta<T>();
        if(!ti.m_write)
            return errors::no_handler();
        ti.m_write(str, &value);
        return {};
    }
    
    template <typename Pred>
    auto            TypeInfo::all_functions(std::string_view k, Pred pred) const
    {
        using pred_result_t = decltype(pred((const MethodInfo*) nullptr));
        if constexpr (!std::is_same_v<pred_result_t, void>){
            auto R  = m_methods.lut.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                if(!r->second)
                    continue;
                pred_result_t   tmp = pred(r->second);
                if(tmp != pred_result_t{})
                    return tmp;
            }
            return pred_result_t{};
        } else if constexpr (std::is_same_v<pred_result_t, void>){
            auto R  = m_methods.lut.equal_range(k);
            for(auto r = R.first; r!=R.second; ++r){
                if(!r->second)
                    continue;
                pred(r->second);
            }
            return;
        }
    }    

    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, std::span<const TypeInfo*>);
}
