////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/Meta.hpp>
#include <0/meta/MetaLookup.hpp>
#include <yq/container/Vector.hpp>

namespace yq {
    struct Meta::Repo {
        bool                    openReg     = true;
        Vector<const Meta*>     all;
        Vector<const Meta*>     metas;
        MetaLookup<ObjectInfo>  objects;
        MetaLookup<TypeInfo>    types;
                
        Repo();
    };
}
