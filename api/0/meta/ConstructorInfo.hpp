////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <0/meta/MethodInfo.hpp>

namespace yq {
    class ConstructorInfo : public MethodInfo {
    public:
    
        template <typename R, typename... Args> class Writer;

        //template <typename R, typename Obj, typename... Args> class Const;
        //template <typename R, typename Obj, typename... Args> class Dynamic;
        template <typename R, typename... Args> class Static;

    private:
    
        ConstructorInfo(const std::source_location&sl, Meta*);
    };
}

