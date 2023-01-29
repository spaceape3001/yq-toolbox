////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    This file is about making new keywords that can be used in the constructors.
*/

namespace yq {

    #ifdef NAN
    #undef NAN
    #endif

    struct all_t {};
    struct ccw_t {};
    struct clockwise_t {};
    struct columns_t {};
    struct diagonal_t {};
    struct down_t {};
    struct identity_t {};
    struct nan_t {};
    struct rows_t {};
    struct sort_t {};
    struct three_t {};
    struct two_t {};
    struct up_t {};
    struct w_t {};
    struct x_t {};
    struct y_t {};
    struct z_t {};
    struct zero_t {};

    static constexpr const all_t        all_;
    static constexpr const ccw_t        ccw_;
    static constexpr const clockwise_t  clockwise_;
    static constexpr const columns_t    columns_;
    static constexpr const diagonal_t   diagonal_;
    static constexpr const down_t       down_;
    static constexpr const identity_t   identity_;
    static constexpr const nan_t        nan_;
    static constexpr const rows_t       rows_;
    static constexpr const sort_t       sort_;
    static constexpr const two_t        two_;
    static constexpr const three_t      three_;
    static constexpr const up_t         up_;
    static constexpr const w_t          w_;
    static constexpr const x_t          x_;
    static constexpr const y_t          y_;
    static constexpr const z_t          z_;
    static constexpr const zero_t       zero_;
    
    static constexpr const all_t        ALL;
    static constexpr const ccw_t        CCW;
    static constexpr const clockwise_t  CLOCKWISE;
    static constexpr const columns_t    COLUMNS;
    static constexpr const diagonal_t   DIAGONAL;
    static constexpr const down_t       DOWN;
    static constexpr const identity_t   IDENTITY;
    static constexpr const nan_t        NAN;
    static constexpr const rows_t       ROWS;
    static constexpr const sort_t       SORT;
    static constexpr const up_t         UP;
    static constexpr const w_t          W;
    static constexpr const x_t          X;
    static constexpr const y_t          Y;
    static constexpr const z_t          Z;
    static constexpr const zero_t       ZERO;

    static constexpr const two_t        ²;
    static constexpr const three_t      ³;
    
}
