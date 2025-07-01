////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MethodMetaWriter.hpp"
#include <yq/meta/ConstructorMeta.hpp>

namespace yq {
    template <typename R, typename... Args> 
    class ConstructorMeta::Writer : public MethodMeta::Writer<R, Args...> {
    public:
        Writer(ConstructorMeta* m, size_t z) : MethodMeta::Writer<R, Args...>(m, z) {}
        Writer() : MethodMeta::Writer<R, Args...>() {}
    };
}

