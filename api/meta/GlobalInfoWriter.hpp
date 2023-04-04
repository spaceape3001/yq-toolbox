////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <meta/GlobalInfo.hpp>
#include <meta/CompoundInfoStatic.hpp>

namespace yq {
    template <typename T>
    class GlobalInfo::Writer : public CompoundInfo::Static {
    public:
    
        Writer(GlobalInfo& p) : CompoundInfo::Static(&p) 
        {
        }
    };
}
