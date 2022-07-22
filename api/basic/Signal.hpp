////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <vector>

namespace yq {
    
    template <typename ...Args>
    using Delegate = std::function<void(Args...)>;


    /*! \brief Simple signal
    */// http://quinnftw.com/c++-signals-and-slots/
    template <typename ...Args>
    class Signal {
    public:
        using FN  = Delegate<Args...>;
    
        void    connect(FN f)
        {
            m_slots.push_back(f);
        }
        
        void    operator()(Args...a)
        {
            for(auto& i : m_slots)
                i(a...);
        }
        
    private:
        std::vector<FN>     m_slots;
    };
}
