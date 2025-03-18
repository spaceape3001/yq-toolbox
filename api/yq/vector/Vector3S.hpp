////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/InfoBinder.hpp>
#include <string>

namespace yq {
    struct Vector3S {
        std::string x;
        std::string y;
        std::string z;
        
        bool operator==(const Vector3S&) const;
    };
}

YQ_TYPE_DECLARE(yq::Vector3S)

