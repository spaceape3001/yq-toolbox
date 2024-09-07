////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/OutputPin.hpp>
#include <span>

namespace yq::xfg {
    template <typename T>
    class VectorOutputPin : public OutputPin {
    public:
    
        using value_type    = T;

        pin_id_t          count() const { return m_count; }
    
        constexpr VectorOutputPin() noexcept = default;
        
        void        publish(pin_id_t n, const T& data)
        {
            if(n < m_count)
                OutputPin::publish(n, data, meta<T>());
        }
        
        void        publish(std::span<const T> data)
        {
            pin_id_t        mx  = std::min<pin_id_t>(m_count, data.size());
            for(pin_id_t i=0;i<mx;++i)
                OutputPin::publish(i, data[i], meta<T>());
        }
        
        void        publish(std::initializer_list<const T> data)
        {
            publish(span(data));
        }
        
        struct Setter {
            VectorOutputPin&    me;
            pin_id_t            i;
            
            Setter(VectorOutputPin& _me, pin_id_t _i) : me(me), i(_i) {}
            
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
        pin_id_t            m_count = 0;
    };

}

