////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <map>

namespace yq {

    enum class LODStatus : uint8_t {
        Unknown
    };
    
    enum class LODAct : uint8_t {
        
    };
    

    template <typename Key>
    class LODCalculator {
    public:
        using key_t = K;
        
        
        virtual std::vector<key_t>  children(const key_t&) const = 0;
        virtual key_t               parent(const key_t&) const = 0;
        
        constexpr uint8_t     min_lod() const noexcept { return m_minLOD; }
        constexpr uint8_t     max_lod() const noexcept { return m_maxLOD; }


        void    set_lod(uint8_t minLOD, uint8_t maxLOD)
        {
            assert(minLOD <= maxLOD);
            m_minLOD    = minLOD;
            m_maxLOD    = maxLOD;
        }

    private:
        uint8_t     m_minLOD    = 0;
        uint8_t     m_maxLOD    = 30;
    };


    //! This is an LOD map, the assumption that there's levels of detail
    //! More refined and... it's more refined
    //!
    //! \tparam K   key type, zero initialized is the root key
    //! \tparam V   value type
    //!
    
    template <typename Key>
    class LODSet  {
    public:
    
        LODSet();
    
    
        using key_t     = K;
        using map_t     = std::map<key_t, LODStatus>;
        
        
        void    clear()
        {
            m_data.clear();
        }
        
        bool empty() const
        {
            return m_data.empty();
        }
        
        LODStatus   status(const Key& k) const
        {
            auto x = m_data.find(k);
            if(x == m_data.end())
                return LODStatus::Unknown;
            
            // TODO...
        }
        
        void    sweep(const LODCalculator& lods)
        {
        }
        
    private:
        map_t                       m_data;
    };
    

}
