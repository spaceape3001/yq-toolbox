////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MethodInfoWriter.hpp"
#include <0/meta/ConstructorInfo.hpp>

namespace yq {
    template <typename R, typename... Args> 
    class ConstructorInfo::Writer : public MethodInfo::Writer<R, Args...> {
    public:
        Writer(ConstructorInfo* m, size_t z) : MethodInfo::Writer<R, Args...>(m, z) {}
        Writer() : MethodInfo::Writer<R, Args...>() {}
    };
}

