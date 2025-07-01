////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MethodMetaWriter.hpp"
#include <yq/meta/OperatorMeta.hpp>

namespace yq {
    template <typename R, typename... Args> 
    class OperatorMeta::Writer : public MethodMeta::Writer<R, Args...> {
    public:
        Writer(OperatorMeta* m, size_t z) : MethodMeta::Writer<R, Args...>(m, z) {}
        Writer() : MethodMeta::Writer<R, Args...>() {}
    };
}

