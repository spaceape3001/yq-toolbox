////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <vector>

namespace yq {
    
    //! Function declaration for below
    template <typename ...Args>
    using Delegate = std::function<void(Args...)>;


    /*! \brief Simple signal
    */// http://quinnftw.com/c++-signals-and-slots/
    template <typename ...Args>
    class Signal {
    public:
    
        //! Our function type
        using FN  = Delegate<Args...>;
    
        //! Connects to the signal
        void    connect(FN f)
        {
            m_slots.push_back(f);
        }
        
        //! Invokes the signal
        void    operator()(Args...a)
        {
            for(auto& i : m_slots)
                i(a...);
        }
        
        //! True if nobody has connected to the signal
        bool    empty() const 
        {
            return m_slots.empty();
        }
        
        //! Clears the signal of all callers
        void    clear()
        {
            m_slots.clear();
        }
        
    private:
        std::vector<FN>     m_slots;
    };
}
