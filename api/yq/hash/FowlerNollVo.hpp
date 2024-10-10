////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <cstddef>
#include <yq/hash/128-bit.hpp>
#include <string_view>

namespace yq {
    //  https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    
    template <typename I, I prime, I offset>
    constexpr I fowler_noll_vo_1a_hash(const char* z, size_t cnt) noexcept
    {
        I   ret = offset;
        for(size_t j = 0; j<cnt; ++j)
            ret = (ret ^ (I) z[j]) * prime;
        return ret;
    }
    
    inline constexpr uint32_t fnv1a_32(const char* z, size_t cnt) noexcept
    {
        return fowler_noll_vo_1a_hash<uint32_t, 16777619, 2166136261>(z, cnt);
    }
    
    inline constexpr uint32_t fnv1a_32(std::string_view s) noexcept
    {
        return fnv1a_32(s.data(), s.size());
    }

    inline constexpr uint64_t fnv1a_64(const char* z, size_t cnt) noexcept
    {
        return fowler_noll_vo_1a_hash<uint64_t, 1099511628211ULL, 14695981039346656037ULL>(z, cnt);
    }
    
    inline constexpr uint64_t fnv1a_64(std::string_view s) noexcept
    {
        return fnv1a_64(s.data(), s.size());
    }

    inline constexpr uint128_t fnv1a_128(const char* z, size_t cnt) noexcept
    {
        //0x0000'0000'0100'0000'0000'0000'0000'013B
        //0x6c62'272e'07bb'0142'62b8'2175'6295'c58d
        return fowler_noll_vo_1a_hash<uint128_t, u128(0x0000000001000000ULL, 0x000000000000013BULL), 
            u128(0x6c62272e07bb0142ULL, 0x62b821756295c58dULL)>(z, cnt);
    }
    
    inline constexpr uint128_t fnv1a_128(std::string_view s) noexcept
    {
        return fnv1a_128(s.data(), s.size());
    }
}
