////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>

namespace yq::lua {
    std::pair<ModuleInfo*,bool>     reg_edit(global_k);
    std::pair<ModuleInfo*,bool>     reg_edit(module_k, const char*);
    std::pair<ObjectInfo*,bool>     reg_edit(const ObjectMeta&);
    std::pair<TypeInfo*,bool>       reg_edit(const TypeMeta&);
    
    ValueInfo*      reg(global_k, const char*, value_k);
    ValueInfo*      reg(global_k, const char*, bool);
    ValueInfo*      reg(global_k, const char*, double);
    ValueInfo*      reg(global_k, const char*, int);
    ValueInfo*      reg(global_k, const char*, std::string_view);
    ValueInfo*      reg(global_k, const char*, Object*);
    ValueInfo*      reg(global_k, const char*, const Object*);
    ValueInfo*      reg(global_k, const char*, raw_k, void*);

    FunctionInfo*   reg(global_k, const char*, function_k);
    FunctionInfo*   reg(global_k, const char*, FNLuaCallback);
    
}
