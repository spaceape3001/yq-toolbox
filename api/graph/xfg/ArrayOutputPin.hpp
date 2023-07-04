////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/OutputPin.hpp>
#include <span>

namespace yq::xfg {
    template <typename T, size_t N>
    class ArrayOutputPin : public OutputPin {
    public:
    
        using value_type    = T;

        pin_id_t          count() const { return m_count; }
    
        constexpr ArrayOutputPin() noexcept = default;
        
        void        publish(pin_id_t n, const T& data)
        {
            if(n < m_count)
                OutputPin::publish(n, data, meta<T>());
        }
        
        void        publish(std::span<const T> data)
        {
            pin_id_t        mx  = std::min<pin_id_t>(N, data.size());
            for(pin_id_t i=0;i<mx;++i)
                OutputPin::publish(i, data[i], meta<T>());
        }

        void        publish(std::initializer_list<const T> data)
        {
            publish(span(data));
        }
        
        struct Setter {
            ArrayOutputPin&    me;
            pin_id_t            i;
            
            Setter(ArrayOutputPin& _me, pin_id_t _i) : me(me), i(_i) {}
            
            void    operator=(const T& data)
            {
                me.publish(i, data);
            }
        };
        
        Setter  operator[](pin_id_t n)
        {
            return Setter{*this, n};
        }
    
    private:
        size_t      m_count = 0;
    
    };

}

