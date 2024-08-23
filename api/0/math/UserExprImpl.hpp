////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/UserExpr.hpp>
#include <0/math/expr/preamble.hpp>


namespace yq::expr {



    
 
    //! Compiles
    //! \param[in,out]  ctx Context (it's expected may be modified with an assignment)
    Expect<InstructionCPtr> compile(const SymVector&, const Context&ctx, Analysis& pAnalysis);
}

