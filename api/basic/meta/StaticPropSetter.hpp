////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/PropSetter.hpp>
#include <basic/meta/TypeInfo.hpp>

namespace yq {

    /*! \brief Abstract static/global getter of type
    
        This is an abstract getter bound to a specific data type.  Derived getters from this class only
        need to implement the "SET" routine and the constructor.
        
        \tparam T   data type being bound to
    */
    template <typename T>
    class StaticPropSetter : public PropSetter {
    public:

        /*! \brief Data type for this setter
        */
        virtual const Meta&     data() const override
        {
            return meta<T>();
        }
        
        /*! \brief Invalid object type
        
            As there's no object for the data, it's always invalid.
        */
        virtual const Meta&     object() const override
        {
            return invalid();
        }

    protected:
        /*! \brief Constructor
        
            \param[in] propInfo Property information
            \param[in] sl       Source location
        */
        StaticPropSetter(PropertyInfo*propInfo, const std::source_location& sl) : PropSetter(propInfo, sl) 
        {
        }
    };
    
    /*! \brief Setter for an explicit pointer
    
        This maintains an explicit pointer to the global variable, 
        and binds it to the property setter.
    */
    template <typename T>
    class XPV_PropSetter : public StaticPropSetter<T> {
    public:
    
        //! Our pointer type
        typedef T* P;

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] pointer  Pointer to variable
        */
        XPV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : StaticPropSetter<T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }
        
    private:

        /*! \brief Sets the variable from the value
            \param[in] The value to set to (assumed to be of the correct type)
            \return TRUE
        */
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            *m_data = *(const T*) value;
            return true;
        }
        
        /*! \brief Sets the variable from the string value
            \param[in] The string value to set to
            \return TRUE if the parsing succeeds
        */
        virtual bool            set(void*, std::string_view value) const override
        {
            return TypeInfo::parse(*m_data, value);
        }

        P      m_data;
    };

    /*! \brief Setter using a function
    
        This uses the given function to "set" the variable.
    */
    template <typename T>
    class XFV_PropSetter : public StaticPropSetter<T> {
    public:
    
        //! Function pointer
        typedef void (*FN)(T);

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:
    
        /*! \brief Sets the variable from the value
            \param[in] The value to set to (assumed to be of the correct type)
            \return TRUE
        */
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            (*m_function)(*(const T*) value);
            return true;
        }
        
        /*! \brief Sets the variable from the string value
            \param[in] The string value to set to
            \return TRUE if the parsing succeeds
        */
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            (*m_function)(tmp);
            return true;
        }

        FN      m_function;
    };

    /*! \brief Setter using a function
    
        This uses the given function to "set" the variable.
    */
    template <typename T>
    class XFBV_PropSetter : public StaticPropSetter<T> {
    public:
        //! Function pointer
        typedef bool (*FN)(T);

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFBV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:

        /*! \brief Sets the variable from the value
            \param[in] The value to set to (assumed to be of the correct type)
            \return TRUE if the setter function returns true
        */
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            return (*m_function)(*(const T*) value);
        }
        
        /*! \brief Sets the variable from the string value
            \param[in] The string value to set to
            \return TRUE if the parsing and setter succeed
        */
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            return (*m_function)(tmp);
        }

        FN      m_function;
    };

    /*! \brief Setter using a function
    
        This uses the given function to "set" the variable.
    */
    template <typename T>
    class XFR_PropSetter : public StaticPropSetter<T> {
    public:
        //! Function pointer
        typedef void (*FN)(const T&);

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:
        /*! \brief Sets the variable from the value
            \param[in] The value to set to (assumed to be of the correct type)
            \return TRUE
        */
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            (*m_function)(*(const T*) value);
            return true;
        }
        
        /*! \brief Sets the variable from the string value
            \param[in] The string value to set to
            \return TRUE if the parsing succeeds
        */
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            (*m_function)(tmp);
            return true;
        }

        FN      m_function;
    };


    /*! \brief Setter using a function
    
        This uses the given function to "set" the variable.
    */
    template <typename T>
    class XFBR_PropSetter : public StaticPropSetter<T> {
    public:
    
        //! Function pointer
        typedef bool (*FN)(const T&);

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFBR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
    
    private:        
        /*! \brief Sets the variable from the value
            \param[in] The value to set to (assumed to be of the correct type)
            \return TRUE if the setter function returns true
        */
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            return (*m_function)(*(const T*) value);
        }
        
        /*! \brief Sets the variable from the string value
            \param[in] The string value to set to
            \return TRUE if the parsing and setter succeed
        */
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            return (*m_function)(tmp);
        }

        FN      m_function;
    };
}
