////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/repo.hpp>
#include <yq/lua/register.hpp>
#include <yq/lua/info/ObjectInfo.hxx>
#include <yq/lua/info/TypeInfo.hxx>
#include <yq/meta/MetaBinder.hpp>

namespace yq::lua {
    template <typename T>
    auto            reg()
    {
        if constexpr (is_object_v<T>){
            return Repo::instance().edit<T>(OBJECT).first;
        } else if constexpr (is_type_v<T>){
            return Repo::instance().edit<T>(TYPE).first;
        } else
            return (Info*) nullptr;
    }
}
