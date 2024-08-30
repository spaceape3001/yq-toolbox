////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <0/trait/not_moveable.hpp>
#include <0/trait/not_copyable.hpp>

namespace yq {

    /*! \brief Class for revision counting
    
        When an object needs a "revision counting", this is the object.  
        
        An optional setting is to specify a "master" so if tracking an invididual component, it'll also 
        trigger an update to the master's revision number too.
    */
    class Revision : not_copyable, not_moveable {
    public:
    
        //! Current revision number.
        uint64_t    revision() const { return m_revision; }
        
    protected:
        /*! \brief Constructor
        
            \param[in] m    optional master
        */
        Revision(Revision* m=nullptr);
        
        //! Call this when something's changed, so that way the revision number is incremented.
        void        changed();
        
        void        set_master(Revision* m);
        
    private:
        uint64_t    m_revision;
        Revision*   m_master;
    };
}
