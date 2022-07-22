////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/Meta.hpp>
#include <basic/Vector.hpp>

namespace yq {
    struct Meta::Repo {
        bool                    openReg     = true;
        Vector<const Meta*>     all;
        Vector<const Meta*>     metas;
        LUC<ObjectInfo>         objects;
        LUC<TypeInfo>           types;
        
        Repo();
    };
}
