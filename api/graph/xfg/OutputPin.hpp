////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/preamble.hpp>

namespace yq::xfg {
    class OutputPin {
    protected:
    
        OutputPin();
        ~OutputPin();
    
        void        publish(pin_id_t offset, const void*, const TypeInfo&);
    
    private:
        Node*       m_node      = nullptr;
        pin_id_t    m_index     = 0;
        
        OutputPin(const OutputPin&) = delete;
        OutputPin(OutputPin&&) = delete;
        OutputPin& operator=(const OutputPin&) = delete;
        OutputPin& operator=(OutputPin&&) = delete;
    };

}

