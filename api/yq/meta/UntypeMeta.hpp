////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/errors.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /* \brief Declares a type that can be stored unobtrusively
    */
    class UntypeMeta : public Meta {
    public:
    
            // WARNING UNSAFE IN UNLOCKED MULTITHREADED MODE!
            
        /*! \brief Returns all current type infos
            \note WARNING Unsafe in unlocked multithreaded mode (as this isn't a copy, 
                    its the actual list that could be changing.)
        */
        static const std::vector<const UntypeMeta*>&   all();
        
        //! Finds the type info by ID
        static const UntypeMeta*                  find(id_t);

        //! Finds the type info by name
        static const UntypeMeta*                  find(std::string_view);
        
        //! Finds the type info of a set
        //! \param[in] Noisy    TRUE will dump failures-to-find to the log
        static std::vector<const UntypeMeta*>     find_all(const string_set_t&, bool noisy=false);
        
        //! Returns the *FIRST* match
        static const UntypeMeta*                  find(stem_k, std::string_view);
    
    
        //! The "generic" classification for this meta which is type.
        virtual const char*     generic() const override { return "Untype"; }


        //! Helper for registering type information
        template <typename T> class Writer;
        template <typename T> class Final;      //  Final one for storing the type info


    protected:
    

        /*! \brief Constructor 
        
            \note Only used this if you know what you're up to
            
            \param[in] zName        the type's name [note this is NOT copied, so needs to remain valid]
            \param[in] sl           Source location it's being done
            \param[in] i            Any assigned ID override
        */
        UntypeMeta(std::string_view zName, const std::source_location& sl);
        
        //! Destructor that should never fire
        virtual ~UntypeMeta();
    };
    
    /*! \brief Converts meta to type, if it's valid
    
        \return TypeMeta pointer, if valid, NULL otherwise
    */
    const UntypeMeta* to_untype(const Meta* m);

    const UntypeMeta* to_untype(const Meta& m);
    
    /*! \brief Converts meta to type, if it's valid
    
        \return TypeMeta pointer, if valid, NULL otherwise
    */
    UntypeMeta* to_untype(Meta* m);

    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, std::span<const UntypeMeta*>);
}
