////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/LuaVM.hpp>

namespace yq {
#if 0
    struct LuaVM::MetaTable {
        Meta::id_t          id;
        std::string         key;    // LUA side...
    };
    
    struct LuaVM::MetaType : public MetaTable {
    };
    
    struct LuaVM::MetaObjectConst : public MetaTable {
    };

    struct LuaVM::MetaObject : public MetaTable {
    };
#endif
}
