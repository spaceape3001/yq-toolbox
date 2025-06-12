////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/Meta.hpp>

namespace yq {

    /*! \brief "Writes" to a meta
    
        This is the base for a writer to a meta.
    */
    class Meta::Writer {
    public:
    
        Writer&     _1d();
        Writer&     _2d();
        Writer&     _3d();
        Writer&     _4d();
        Writer&     _5d();
        Writer&     _6d();
    
    
        /*! \brief Sets an alias
        
            This defines an alias for the meta.  
            
            \note   Provided zAlias *MUST* remain valid throughout the program execution, so it's expected
                    to be a program string "char[]"
            \param[in] zAlias   Alias string
            \return Reference to this writer object
        */
        Writer&     alias(std::string_view zAlias);

        Writer&     alias(std::initializer_list<std::string_view> zAlias);

        /*! \brief Sets a description
        
            This defines a description for the meta.  
            
            \note   Provided zDescription *MUST* remain valid throughout the program execution, so it's expected
                    to be a program string "char[]"
            \param[in] zDescription   Description string
            \return Reference to this writer object
        */
        Writer&     description(std::string_view zDescription);
        
        Writer&     icon(icon_size_t, std::string_view zIcon);
        
        /*! \brief Sets a label
        
            This defines a label for the meta, ie the human friendly version
            
            \note   Provided zLabel *MUST* remain valid throughout the program execution, so it's expected
                    to be a program string "char[]"
            \param[in] zLabel   Label string
            \return Reference to this writer object
        */
        Writer&     label(std::string_view zLabel);
        
        /*! \brief Overrides the given name
        
            This overrides the given name from th econstructor
            
            \note   Provided zLabel *MUST* remain valid throughout the program execution, so it's expected
                    to be a program string "char[]"
            \param[in] zName   Name string
            \return Reference to this writer object
        */
        Writer&     name(std::string_view zName);
        
        /*! \brief Applies new options/flags
        */
        Writer&     options(options_t);

        /*! \brief Sets one flag
        */
        Writer&     set(Flag);
        
        /*! \brief Tags the meta
        
            This adds a tag to this meta, the value will be set to TRUE.
            
            \note   Provided zKey *MUST* remain valid throughout the program execution, so it's expected
                    to be a program string "char[]"
            \param[in] zKey   Description string
            \return Reference to this writer object
        */
        Writer&     tag(std::string_view zKey); // implies boolean TRUE

        /*! \brief Tags the meta
        
            This adds a tag to this meta
            
            \note   Provided zKey *MUST* remain valid throughout the program execution, so it's expected
                    to be a program string "char[]"
            \param[in] zKey   Description string
            \param[in] value    Value to set (this is a move-basis for temporaries)
            \return Reference to this writer object
        */
        Writer&     tag(std::string_view zKey, Any&& value);

        /*! \brief Tags the meta
        
            This adds a tag to this meta
            
            \note   Provided zKey *MUST* remain valid throughout the program execution, so it's expected
                    to be a program string "char[]"
            \param[in] zKey   Description string
            \param[in] value    Value to set (this one copies)
            \return Reference to this writer object
        */
        Writer&     tag(std::string_view zKey, const Any& value);
        
        Writer&     tag(int);
        Writer&     tag(int, Any&&value);
        Writer&     tag(int, const Any&);

        //! Tags the meta with the given tags
        Writer&     tag(std::initializer_list<int>);
        
        /*! \brief Mark the static global as being static thread_local instead
        */
        Writer&     tls();  //!< Marks the TLS flag ... only meaningful on static variables, still
        
        /*! \brief Mark the feature as still in progress/needs-to-be-done
        */
        Writer&     todo(); //!< Marks this as needing TODO work
        
        Writer&     verbose();
    
        //! Constructor from proper meta
        //! \note Only use if you KNOW what you're up to
        Writer(Meta* myMeta);

    protected:
            //  In proper usage, should never be null, however, guard!
        Meta* const m_meta = nullptr;
    };
}
