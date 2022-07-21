////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>
#include <utility>
#include <type_traits>

namespace yq {
    union DataBlock {
        uint64_t    Data[1];        //  data access if it's small
        double      Double;         //  size assurance
        uint64_t    Unsigned;       //  size assurance
        int64_t     Integer;        //  size assurance
        void*       Pointer;        //  pointer if it's big
        char*       String;         //  pointer to string (for debugging if it's a string)

        template <typename T>
        void        ctorDefault()
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                new ((T*) Data) T;
            else 
                Pointer     = new T;
        }

        template <typename T>
        void        ctorCopy(const T& cp)
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                new ((T*) Data) T(cp);
            else
                Pointer     = new T(cp);
        }
        
        template <typename T>
        void        ctorMove(T&& mv)
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                new ((T*) Data) T(std::move(mv));
            else
                Pointer     = new T(std::move(mv));
        }
        
        template <typename T>
        void        dtor()
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                ((T*) Data) -> ~T();
            else
                delete (T*) Pointer;
        }
        
        template <typename T>
        T*          pointer()
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                return (T*) Data;
            else
                return (T*) Pointer;
        }
        
        template <typename T>
        const T*    pointer() const
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                return (const T*) Data;
            else
                return (const T*) Pointer;
        }

        template <typename T>
        T&          reference()
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                return *(T*) Data;
            else
                return *(T*) Pointer;
        }

        template <typename T>
        const T&    reference() const
        {
            if constexpr (sizeof(T) <= sizeof(DataBlock))
                return *(const T*) Data;
            else
                return *(const T*) Pointer;
        }
    };
    
    template <typename T>
    static constexpr const bool is_small_v    = sizeof(T) <= sizeof(DataBlock);
}
