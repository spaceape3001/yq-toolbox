////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/string.hpp>
#include <functional>
#include <map>
#include <vector>
#include <system_error>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> class Ref;
    template <typename> class Stack;
    class TypeMeta;
    struct IgCase;
    class UserExpr;
}

namespace yq::expr {
    class Instruction;
    struct OpData;
    struct Symbol;
    struct SymCode;
    struct SymData;
    struct Token;
    struct VirtualMachine;

    using SymVector             = std::vector<Symbol>;
    using TokenFN               = std::function<std::error_code(SymCode,std::u32string_view)>;
    using InstructionCPtr       = Ref<const Instruction>;
    
    using u32string_type_map_t  = std::map<string_t, const TypeMeta*,IgCase>;
    using string_type_map_t     = std::map<string_t, const TypeMeta*,IgCase>;
    
    struct Context;
    struct Analysis;
    using SymDataStack  = Stack<SymData>;
    using feature_t = std::pair<bool,size_t>;
}
