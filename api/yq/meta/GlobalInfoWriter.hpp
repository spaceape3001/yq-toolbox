////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/meta/GlobalInfo.hpp>
#include <yq-toolbox/meta/CompoundInfoStatic.hpp>

namespace yq {
    template <typename T>
    class GlobalInfo::Writer : public CompoundInfo::Static {
    public:
    
        Writer(GlobalInfo& p) : CompoundInfo::Static(&p) 
        {
        }
    };
}
