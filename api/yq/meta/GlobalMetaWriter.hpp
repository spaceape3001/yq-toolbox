////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/GlobalMeta.hpp>
#include <yq/meta/CompoundMetaStatic.hpp>

namespace yq {
    template <typename T>
    class GlobalMeta::Writer : public CompoundMeta::Static {
    public:
    
        Writer(GlobalMeta& p) : CompoundMeta::Static(&p) 
        {
        }
    };
}
