////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/ObjectInfo.hpp>

namespace yq::lua {
    template <typename T>
    class TypedObjectInfo : public ObjectInfo {
    public:
        //  To avoid nasty things... NEVER DO MEMBERS/VIRTUAL OVERRIDES IN HERE!
        //  It needs to work with a type info being allocated (& casted into a typed type).
    
        TypedObjectInfo() : ObjectInfo(::yq::meta<T>()){}
    };
}
