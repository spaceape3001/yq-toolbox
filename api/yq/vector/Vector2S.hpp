////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/InfoBinder.hpp>
#include <string>

namespace yq {
    struct Vector2S {
        std::string x;
        std::string y;
        
        bool operator==(const Vector2S&) const;
    };
}

YQ_TYPE_DECLARE(yq::Vector2S)

