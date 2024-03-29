////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/Meta.hpp>
#include <0/basic/Vector.hpp>

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
