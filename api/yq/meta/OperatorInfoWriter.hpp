////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MethodInfoWriter.hpp"
#include <yq/meta/OperatorInfo.hpp>

namespace yq {
    template <typename R, typename... Args> 
    class OperatorInfo::Writer : public MethodInfo::Writer<R, Args...> {
    public:
        Writer(OperatorInfo* m, size_t z) : MethodInfo::Writer<R, Args...>(m, z) {}
        Writer() : MethodInfo::Writer<R, Args...>() {}
    };
}

