////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <0/math/Operator.hpp>
#include <0/meta/MethodInfo.hpp>

namespace yq {
    class OperatorInfo : public MethodInfo {
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
    
        OperatorInfo(Operator, const std::source_location&sl, Meta*);
    
        const Operator    m_code;
    };
}

