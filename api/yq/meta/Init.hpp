////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <yq/meta/CompoundMetaDynamic.hpp>
#include <yq/meta/CompoundMetaStatic.hpp>
#include <yq/meta/EnumMeta.hpp>
#include <yq/meta/GlobalMeta.hpp>
#include <yq/meta/GlobalMetaWriter.hpp>
#include <yq/meta/MetaWriter.hpp>
#include <yq/meta/MethodMetaWriter.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>
#include <yq/meta/PropertyMetaWriter.hpp>
#include <yq/meta/TypeMetaWriter.hpp>
#include <yq/meta/UntypeMetaWriter.hpp>

#include <yq/core/Logging.hpp>


#define YQ_TYPE_IMPLEMENT( ... )                                                                            \
    namespace yq {                                                                                          \
        TypeMeta&   MetaBinder<__VA_ARGS__>::edit() {                                                       \
            static auto* s_ret   = new TypeMeta::Final<__VA_ARGS__>(#__VA_ARGS__);                          \
            return *s_ret;                                                                                  \
        }                                                                                                   \
        template <> TypeMeta& TypeMeta::Final<__VA_ARGS__>::s_save  = MetaBinder<__VA_ARGS__>::edit();      \
    }

#define YQ_TYPE_FIXED( ii, ... )                                                                            \
    namespace yq {                                                                                          \
        TypeMeta&   MetaBinder<__VA_ARGS__>::edit() {                                           \
            static auto* s_ret   = new TypeMeta::Final<__VA_ARGS__>(#__VA_ARGS__, ii);                      \
            return *s_ret;                                                                                  \
        }                                                                                                   \
        template <> TypeMeta& TypeMeta::Final<__VA_ARGS__>::s_save  = MetaBinder<__VA_ARGS__>::edit();      \
    }
    
namespace yq {

    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  MISC WRAPPER
    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template <std::string_view (*FN)()>
    std::string    string_view_proxy()
    {
        return std::string(FN());
    }
}
