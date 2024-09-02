////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/InfoBinder.hpp>
#include <yq/meta/CompoundInfoDynamic.hpp>
#include <yq/meta/CompoundInfoStatic.hpp>
#include <yq/meta/GlobalInfo.hpp>
#include <yq/meta/GlobalInfoWriter.hpp>
#include <yq/meta/MetaWriter.hpp>
#include <yq/meta/MethodInfoWriter.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>
#include <yq/meta/PropertyInfoWriter.hpp>
#include <yq/meta/TypeInfoWriter.hpp>

#include <yq/basic/Logging.hpp>


#define YQ_TYPE_IMPLEMENT( ... )                                                                            \
    namespace yq {                                                                                          \
        TypeInfo&   InfoBinder<__VA_ARGS__>::edit() {                                                       \
            static auto* s_ret   = new TypeInfo::Final<__VA_ARGS__>(#__VA_ARGS__);                          \
            return *s_ret;                                                                                  \
        }                                                                                                   \
        template <> TypeInfo& TypeInfo::Final<__VA_ARGS__>::s_save  = InfoBinder<__VA_ARGS__>::edit();      \
    }

#define YQ_TYPE_FIXED( ii, ... )                                                                            \
    namespace yq {                                                                                          \
        TypeInfo&   InfoBinder<__VA_ARGS__>::edit() {                                           \
            static auto* s_ret   = new TypeInfo::Final<__VA_ARGS__>(#__VA_ARGS__, ii);                      \
            return *s_ret;                                                                                  \
        }                                                                                                   \
        template <> TypeInfo& TypeInfo::Final<__VA_ARGS__>::s_save  = InfoBinder<__VA_ARGS__>::edit();      \
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
