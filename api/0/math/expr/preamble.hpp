////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <0/basic/preamble.hpp>
#include <map>
#include <unordered_set>

namespace yq::expr {
    struct Instruction;
    struct Symbol;
    struct Token;
    
    using InsVector = std::vector<Instruction>;
    using SymVector = std::vector<Symbol>;

//    struct Function;

    
    using VarMap        = std::map<std::u32string,Any,IgCase>;
    using ConMap        = std::map<std::u32string,Any,IgCase>;
//    using FnMap         = std::map<std::u32string_view, const Function*, IgCase>;

}
