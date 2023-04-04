////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <meta/PropertyInfo.hpp>
#include <meta/MetaWriter.hpp>
#include <meta/DynamicPropSetter.hpp>
#include <meta/StaticPropSetter.hpp>

namespace yq {

    /*! \brief Initialization writer for a property info
    
        This is a writer for property information.
    */
    template <typename T>
    class PropertyInfo::Writer : public Meta::Writer {
    public:
    
        /*! \brief Sets the default value
            
            This sets the default value for the property.
            
            \param[in] value to set
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer&  def_value(const T& val)
        {
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());
            if(Meta::Writer::m_meta && thread_safe_write()){
                static_cast<PropertyInfo*>(Meta::Writer::m_meta) -> m_default.reference<T>() = val;
            }
            return *this;
        }
        
        /*! \brief Sets the default value
            
            This sets the default value for the property.
            
            \param[in] value to set
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer&  def_value(T&& val)
        {
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());
            if(Meta::Writer::m_meta && thread_safe_write()){
                static_cast<PropertyInfo*>(Meta::Writer::m_meta) -> m_default.reference<T>() = std::move(val);
            }
            return *this;
        }

        /*! \brief Constructor
        
            \note While public for implementation reasons, it's intended for most sitautions
            to use the ".property" methods on the type/object informations.
        */
        Writer(PropertyInfo* pi) : Meta::Writer(pi) {}
    };
    
 //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    /*! \brief Writer for a global property
    
        A global property is a property associated with the class but not actually attached
        to any object... ie, it's a global configuration variable for the class.
    */
    template <typename T>
    class PropertyInfo::VarW : public Writer<T> {
    public:
    
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(void(*function)(T), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);

            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new XFV_PropSetter<T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
        
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(void(*function)(const T&), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());

            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new XFR_PropSetter<T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
        
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(bool(*function)(T), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());

            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new XFBV_PropSetter<T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
        
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(bool(*function)(const T&), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());
            
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new XFBR_PropSetter<T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
        
        /*! \brief Constructor
        
            \note public for implementation reasons, most callers are better suited to using the other
            provided methods.
        */
        VarW(PropertyInfo* pi) : Writer<T>(pi) {}
    };

    /*! \brief Writer for a member variable property
    
        This creates a writer for a member variable property, attached to an instance of the property.
    */
    template <typename C, typename T>
    class PropertyInfo::PropW : public Writer<T> {
    public:
    
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(void (C::*function)(T), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());

            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new IFV_PropSetter<C,T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
        
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(void (C::*function)(const T&), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());

            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new IFR_PropSetter<C,T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
        
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(bool (C::*function)(T), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());

            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new IFBV_PropSetter<C,T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
        
        /*! \brief Attach a setter so the property can be modified
        
            \param[in] function Function to associate
            \param[in] sl       Source location (auto-deduced by default-initialization)
            \return Reference to this writer to allow for daisy chaining.
        */
        Writer<T>&     setter(bool (C::*function)(const T&), const std::source_location& sl = std::source_location::current())
        {
            assert(function);
            assert(Meta::Writer::m_meta);
            assert(thread_safe_write());

            if(function && Meta::Writer::m_meta && thread_safe_write()){
                new IFBR_PropSetter<C,T>(static_cast<PropertyInfo*>(Meta::Writer::m_meta), sl, function);
            }
            return *this;
        }
    
        /*! \brief Constructor
        
            \note public for implementation reasons, most callers are better suited to using the other
            provided methods.
        */
        PropW(PropertyInfo* pi) : Writer<T>(pi) {}
    };
}
