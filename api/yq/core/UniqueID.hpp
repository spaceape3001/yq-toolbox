////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>

namespace yq {

    /*! \brief Class for a unique ID
    
        For those situations where a unique ID is required (but the actual order unimportant),
        this is that class!
    */
    class UniqueID {
    public:
    
        //! This instance's unique ID
        constexpr uint64_t    id() const { return m_id; }
        
    protected:
    
        //! Default constructor (that auto-generates a new ID)
        UniqueID();
    private:
        const uint64_t    m_id;

        UniqueID(const UniqueID&) = delete;
        UniqueID(UniqueID&&) = delete;
        UniqueID& operator=(const UniqueID&) = delete;
        UniqueID& operator=(UniqueID&&) = delete;
    };
}
