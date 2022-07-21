////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/ObjectInfo.hpp>
#include <basic/meta/CompoundInfoDynamic.hpp>

namespace yq {
    template <typename C>
    class ObjectInfo::Writer : public CompoundInfo::Dynamic<C> {
    public:
    
        /*! \brief Sets the base object (if not already set)
        */
        template <typename B>
        Writer&     base()
        {
            static_assert( std::is_base_of_v<B, C>, "T must derive from B!" );
            ObjectInfo*     obj = static_cast<ObjectInfo*>(Meta::Writer::m_meta);
            assert(!obj->m_base);
            obj->m_base = &meta<B>();
            return *this; 
        }
        
        Writer&     abstract()
        {
            if(Meta::Writer::m_meta)
                Meta::Writer::m_meta -> set_option(ABSTRACT);
            return *this;
        }
        
        Writer(ObjectInfo* obj) : CompoundInfo::Dynamic<C>(obj) 
        {
            assert(obj);
            if constexpr ( std::is_abstract_v<C> ){
                Meta::Writer::m_meta -> set_option(ABSTRACT);
            }
            
        }
        
        Writer(ObjectInfo& obj) : Writer(&obj)
        {
        }
    };
}


