////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/math/Operator.hpp>
#include <yq/meta/MethodMeta.hpp>

namespace yq {
    class OperatorMeta : public MethodMeta {
    public:
    
        template <typename R, typename... Args> class Writer;

        //template <typename R, typename Obj, typename... Args> class Const;
        //template <typename R, typename Obj, typename... Args> class Dynamic;
        template <typename R, typename... Args> class Static;

        /*
            OPERATORS will *NOT* be self-modifying... that'll be an action
            for expression evaluation instead.  These will basically be 
            static methods.
        */
    

        constexpr Operator    code() const { return m_code; }

    private:
    
        OperatorMeta(Operator, const std::source_location&sl, Meta*);
    
        const Operator    m_code;
    };
}

