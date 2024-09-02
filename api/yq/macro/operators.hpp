////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


/*! \brief Dot product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the dot product between zvecs.
    
    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define DOT         ||

/*! \brief Inner product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the inner product.

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define INNER       &
#define INNER_EQ    &=

/*! \brief Outer product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the outer product.

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define OUTER       ^
#define OUTER_EQ    ^=

/*! \brief Outer Vector to Tensor operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the outer zvec product between zvecs.
    This is different than the general outer product because this one
    produces ztens, whereas the general outer product makes for zbvecs.
    
    Also, this operator can produce non-square ztens (ie, 3x2).

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define OTIMES      &&

/*! \brief Cross product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the cross product between zvecs.

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define CROSS       %
#define CROSS_EQ   %=
