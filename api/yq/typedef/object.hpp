////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <concepts>

namespace yq {
    class Object;
    class ObjectMeta;
    
    template <class Obj>
    concept SomeObject        = std::derived_from<Obj,Object>;
}
