////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>
#include <0/basic/Ref.hpp>
#include <0/math/Operator.hpp>
#include <0/math/UserExpr.hpp>
#include <0/math/expr/Analysis.hpp>
#include <0/math/expr/Context.hpp>
#include <0/math/expr/Symbol.hpp>
#include <0/math/expr/Token.hpp>
#include <unordered_set>
#include <tbb/spin_rw_mutex.h>


namespace yq::expr {



    
 
    //! Compiles
    //! \param[in,out]  ctx Context (it's expected may be modified with an assignment)
    Expect<InstructionCPtr> compile(const SymVector&, const Context&ctx, Analysis& pAnalysis);
}


namespace yq::expr {

}

