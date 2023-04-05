////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename T>
    class AutoReset {
    public:
        AutoReset(T& location) : m_pointer(&location), m_value(location) 
        {
        }
        
        AutoReset(T& location, const T& newValue) : AutoReset(location)
        {
            location = newValue;
        }

        AutoReset(T& location, T&& newValue) : AutoReset(location)
        {
            location = std::move(newValue);
        }

        ~AutoReset()
        {
            if(m_pointer){
                *m_pointer  = std::move(m_value);
                m_pointer   = nullptr;
            }
        }
        
        AutoReset(AutoReset&& mv)
        {
            m_pointer       = mv.m_pointer;
            m_value         = std::move(mv.m_value);
            mv.m_pointer    = nullptr;
        }
        
        AutoReset&  operator=(AutoReset&&mv)
        {
            if(this != &mv){
                m_pointer       = mv.m_pointer;
                m_value         = std::move(mv.m_value);
                mv.m_pointer    = nullptr;
                return nullptr;
            }
        }
        
        AutoReset(const AutoReset&) = delete;
        AutoReset& operator=(const AutoReset&) = delete;
        
    private:
        T*      m_pointer   = nullptr;
        T       m_value;
    };
    
    template <typename T>
    AutoReset<T>  auto_reset(T& spot)
    {
        return AutoReset<T>(spot);
    }

    template <typename T>
    AutoReset<T>  auto_reset(T& spot, const T& value)
    {
        return AutoReset<T>(spot, value);
    }

    template <typename T>
    AutoReset<T>  auto_reset(T& spot, T&& value)
    {
        return AutoReset<T>(spot, std::move(value));
    }
}
