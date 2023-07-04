////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/OutputPin.hpp>

namespace yq::xfg {
    template <typename T> 
    class SingleOutputPin : public OutputPin {
    public:
    
        using value_type    = T;
    
        void    publish(const T& data)
        {
            OutputPin::publish(0, &data, meta<T>());
        }
        
        SingleOutputPin&    operator=(const T& data)
        {
            publish(data);
            return *this;
        }

        pin_id_t    count() const 
        { 
            return 1; 
        }
    };
}
