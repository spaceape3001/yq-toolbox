////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/CompoundInfo.hpp>

namespace yq {

    class Object;

    /*! \brief Represents info for an object thats intrusively bound
    */
    class ObjectInfo : public CompoundInfo {
        template <typename> friend struct InfoBinder;
        friend class Object;
    public:
    
        const ObjectInfo*   base() const { return m_base; }
    
        template <typename C> class Writer;

        ObjectInfo(std::string_view zName, const ObjectInfo& base, const std::source_location& sl=std::source_location::current());
        
        virtual Object* create() const { return nullptr; }
        bool            is_abstract() const { return static_cast<bool>(flags()&ABSTRACT); }
    
        static const Vector<const ObjectInfo*>&   all();
        static const ObjectInfo*        find(std::string_view);
        static const ObjectInfo*        find(id_t);
        
        bool    is_base(const ObjectInfo&) const;
        bool    is_derived(const ObjectInfo&) const;
        
        virtual size_t          size() const;
        
        const LUC<ObjectInfo>&    deriveds(bool all=false) const;
        const LUC<ObjectInfo>&    bases(bool all=false) const;
        const LUC<PropertyInfo>&  properties(bool all=false) const;
        const LUC<MethodInfo>&    methods(bool all=false) const;
        
    
    protected:
        friend class PropertyInfo;
        friend class MethodInfo;
        
        ObjectInfo(std::string_view zName, const std::source_location& sl=std::source_location::current());
        
        virtual void                    sweep_impl() override;

        ObjectInfo*     m_base; // defined/declared base
        
        struct D {
            LUC<ObjectInfo>     bases;
            LUC<ObjectInfo>     derived;
            LUC<PropertyInfo>   properties;
            LUC<MethodInfo>     methods;
        };
        
        D               m_local, m_all;
        
        const D& def(bool all) const { return all ? m_all : m_local; }
    
    private:
        ObjectInfo(std::string_view zName, ObjectInfo* base, const std::source_location& sl);
    };


    /*! \brief Converts meta to object, if it's valid
    
        \return ObjectInfo pointer, if valid, NULL otherwise
    */
    inline const ObjectInfo* to_object(const Meta* m)
    {
        return (m && (m->flags() & OBJECT)) ? static_cast<const ObjectInfo*>(m) : nullptr;
    }
    
    inline ObjectInfo* to_object(Meta* m)
    {
        return (m && (m->flags() & OBJECT)) ? static_cast<ObjectInfo*>(m) : nullptr;
    }
}
