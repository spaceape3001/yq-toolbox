////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/GlobalInfo.hpp>
#include <yq/meta/CompoundMetaStatic.hpp>

namespace yq {
    template <typename T>
    class GlobalInfo::Writer : public CompoundMeta::Static {
    public:
    
        Writer(GlobalInfo& p) : CompoundMeta::Static(&p) 
        {
        }
    };
}
