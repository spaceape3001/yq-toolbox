////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>
#include <string>

namespace yq::lua {
    std::pair<ModuleInfo*,bool>     reg_edit(global_k);
    std::pair<ModuleInfo*,bool>     reg_edit(module_k, const std::string&);
    std::pair<ObjectInfo*,bool>     reg_edit(const ObjectMeta&);
    std::pair<TypeInfo*,bool>       reg_edit(const TypeMeta&);
    
    ValueInfo*      reg(global_k, const std::string&, value_k);
    ValueInfo*      reg(global_k, const std::string&, bool);
    ValueInfo*      reg(global_k, const std::string&, double);
    ValueInfo*      reg(global_k, const std::string&, int);
    ValueInfo*      reg(global_k, const std::string&, std::string_view);
    ValueInfo*      reg(global_k, const std::string&, Object*);
    ValueInfo*      reg(global_k, const std::string&, const Object*);
    ValueInfo*      reg(global_k, const std::string&, raw_k, void*);

    FunctionInfo*   reg(global_k, const std::string&, function_k);
    FunctionInfo*   reg(global_k, const std::string&, FNLuaCallback);
    
    ModuleInfo*     reg(module_k, const std::string&);
    
}
