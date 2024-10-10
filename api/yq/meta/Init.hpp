////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/meta/CompoundInfoDynamic.hpp>
#include <yq-toolbox/meta/CompoundInfoStatic.hpp>
#include <yq-toolbox/meta/GlobalInfo.hpp>
#include <yq-toolbox/meta/GlobalInfoWriter.hpp>
#include <yq-toolbox/meta/MetaWriter.hpp>
#include <yq-toolbox/meta/MethodInfoWriter.hpp>
#include <yq-toolbox/meta/ObjectInfoWriter.hpp>
#include <yq-toolbox/meta/PropertyInfoWriter.hpp>
#include <yq-toolbox/meta/TypeInfoWriter.hpp>

#include <yq-toolbox/basic/Logging.hpp>


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
