////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>
#include <basic/trait/not_moveable.hpp>
#include <basic/trait/not_copyable.hpp>

namespace yq {

    /*! \brief Class for a unique ID
    
        For those situations where a unique ID is required (but the actual order unimportant),
        this is that class!
    */
    class UniqueID : not_copyable, not_moveable {
    public:
    
        //! This instance's unique ID
        uint64_t    id() const { return m_id; }
        
    protected:
    
        //! Default constructor (that auto-generates a new ID)
        UniqueID();
    private:
        uint64_t    m_id;
    };
}
