////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/forward.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/meta/MetaLookup.hpp>
#include <yq/container/Vector.hpp>

namespace yq {
    struct Meta::Repo {
        bool                    openReg     = true;
        Vector<const Meta*>     all;
        Vector<const Meta*>     metas;
        MetaLookup<ObjectMeta>  objects;
        MetaLookup<TypeMeta>    types;
        MetaLookup<UntypeMeta>  untypes;
                
        Repo();
        ~Repo();
    };
}
