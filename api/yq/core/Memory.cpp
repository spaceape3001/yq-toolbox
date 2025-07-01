////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Memory.hpp"
#include <yq/hash/MD5.hpp>

namespace yq {

    Memory::Memory() 
    {
        _zap();
    }

    Memory::Memory(Memory&& mv)
    {
        _move(std::move(mv));
        mv._zap();
    }

    Memory::Memory(set_k, const void* pData, size_t byteCount) : Memory()
    {
        set(pData, byteCount);
    }

    Memory::Memory(set_k, const void* pData, size_t byteCount, size_t stride) : Memory()
    {
        set(pData, byteCount, stride);
    }

    Memory::Memory(set_k, const void* pData, size_t byteCount, const TypeMeta& type) : Memory()
    {
        set(pData, byteCount, type);
    }

    Memory::Memory(set_k, const void* pData, size_t byteCount, Free&& free) : Memory()
    {
        set(pData, byteCount, std::move(free));
    }

    Memory::Memory(set_k, const void* pData, size_t byteCount, size_t stride, Free&& free) : Memory()
    {
        set(pData, byteCount, stride, std::move(free));
    }

    Memory::Memory(set_k, const void* pData, size_t byteCount, const TypeMeta& type, Free&&free) : Memory()
    {
        set(pData, byteCount, type, std::move(free));
    }


    Memory::~Memory()
    {
        clear();
    }

    Memory& Memory::operator=(Memory&& mv)
    {
        if(&mv != this){
            clear();
            _move(std::move(mv));
            mv._zap();
        }
        return *this;
    }

    void            Memory::_free()
    {
        if(m_free)
            m_free(m_data, m_bytes);
    }

    void            Memory::_move(Memory&& mv)
    {
        m_data      = mv.m_data;
        m_bytes     = mv.m_bytes;
        m_type      = mv.m_type;
        m_stride    = mv.m_stride;
        m_free      = std::move(mv.m_free);
    }

    void    Memory::_set(const void* p, size_t n, const TypeMeta* type, size_t s, Free&& free)
    {
        clear();
        if(p && n){
            m_free      = std::move(free);
            m_data      = p;
            m_bytes     = n;
            m_stride    = s;
            m_type      = type;
        }
    }

    void            Memory::_zap()
    {
        m_free      = {};
        m_data      = nullptr;
        m_bytes     = 0ULL;
        m_type      = nullptr;
        m_stride    = 0ULL;
    }


    void Memory::clear()
    {
        if(m_data){
            _free();
            _zap();
        }
    }

    size_t  Memory::count() const
    {
        if(m_stride)
            return m_bytes / m_stride;
        return 0ULL;
    }

    //! Computes MD5 checksum (or zero if empty)
    uint128_t       Memory::md5() const
    {
        if(empty())
            return uint128_t(0);
        return md5_checksum(m_data, m_bytes);
    }

    void    Memory::set(const void* pData, size_t byteCount)
    {
        _set(pData, byteCount, nullptr, 0, {});
    }

    void    Memory::set(const void* pData, size_t byteCount, size_t s)
    {
        _set(pData, byteCount, nullptr, s, {});
    }

    void    Memory::set(const void* pData, size_t byteCount, const TypeMeta& type)
    {
        _set(pData, byteCount, &type, type.size(), {});
    }
    
    void    Memory::set(const void* pData, size_t byteCount, Free&&free)
    {
        _set(pData, byteCount, nullptr, 0, std::move(free));
    }
    
    void    Memory::set(const void* pData, size_t byteCount, size_t stride, Free&&free)
    {
        _set(pData, byteCount, nullptr, stride, std::move(free));
    }
    
    void    Memory::set(const void* pData, size_t byteCount, const TypeMeta& type, Free&& free)
    {
        _set(pData, byteCount, &type, type.size(), std::move(free));
    }

}
        
