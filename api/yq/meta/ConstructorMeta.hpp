////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/meta/MethodMeta.hpp>

namespace yq {
    class ConstructorMeta : public MethodMeta {
    public:
    
        template <typename R, typename... Args> class Writer;

        //template <typename R, typename Obj, typename... Args> class Const;
        //template <typename R, typename Obj, typename... Args> class Dynamic;
        template <typename R, typename... Args> class Static;

    private:
    
        ConstructorMeta(const std::source_location&sl, Meta*);
    };
}

