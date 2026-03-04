////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/xg/XGElement.hpp>

namespace yq {
    class XGLogic : public XGElement {
        YQ_OBJECT_DECLARE(XGLogic, XGElement)
    public:
    
        static void init_meta();
        
        const auto& logic() const { return m_logic; }

    protected:
        friend class XGRuntime;
        
        XGLogic();
        ~XGLogic();
        
        std::vector<xg_next_t>      m_logic;        
    };
}
