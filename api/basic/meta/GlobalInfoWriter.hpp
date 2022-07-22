////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/Global.hpp>
#include <basic/meta/CompoundInfoStatic.hpp>

namespace yq {
    template <typename T>
    class GlobalInfo::Writer : public CompoundInfo::Static {
    public:
    
        Writer(GlobalInfo& p) : CompoundInfo::Static(&p) 
        {
        }
    };
}
