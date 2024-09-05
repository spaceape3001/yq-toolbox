////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/meta/forward.hpp>
#include <yq-toolbox/meta/Meta.hpp>
#include <yq-toolbox/meta/MetaLookup.hpp>
#include <yq-toolbox/container/Vector.hpp>

namespace yq {
    struct Meta::Repo {
        bool                    openReg     = true;
        Vector<const Meta*>     all;
        Vector<const Meta*>     metas;
        MetaLookup<ObjectInfo>  objects;
        MetaLookup<TypeInfo>    types;
                
        Repo();
        ~Repo();
    };
}
