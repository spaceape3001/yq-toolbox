////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <string>

namespace yq {
    struct Vector4S {
        std::string x;
        std::string y;
        std::string z;
        std::string w;
        
        bool operator==(const Vector4S&) const;
    };
}

YQ_TYPE_DECLARE(yq::Vector4S)

