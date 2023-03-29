////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    This file is about making new keywords that can be used in the constructors and function overloads.
*/

namespace yq {

    #ifdef NAN
    #undef NAN
    #endif

    struct all_t {};
    struct ccw_t {};
    struct clock_arg_t {};
    struct clockwise_t {};
    struct columns_t {};
    struct diagonal_t {};
    struct diameter_t {};
    struct down_t {};
    struct euler_t {};
    struct focus_t {};
    struct guard_t {};
    struct hpr_t {};
    struct identity_t {};
    struct intersect_t {};
    struct nan_t {};
    struct normal_t {};
    struct one_t {};
    struct opposite_t {};
    struct rotor_t {};
    struct rows_t {};
    struct sort_t {};
    struct three_t {};
    struct two_t {};
    struct union_t {};
    struct unit_t {};
    struct up_t {};
    struct w_t {};
    struct ww_t {};
    struct wx_t {};
    struct wxy_t {};
    struct wy_t {};
    struct wz_t {};
    struct x_t {};
    struct xw_t {};
    struct xx_t {};
    struct xy_t {};
    struct xyz_t {};
    struct xyzw_t {};
    struct xz_t {};
    struct y_t {};
    struct yw_t {};
    struct yx_t {};
    struct yy_t {};
    struct yz_t {};
    struct yzw_t {};
    struct z_t {};
    struct zw_t {};
    struct zwx_t {};
    struct zx_t {};
    struct zy_t {};
    struct zz_t {};
    struct zero_t {};

    //static constexpr const all_t        all_;
    //static constexpr const columns_t    COLUMNS;
    //static constexpr const diagonal_t   diagonal_;
    //static constexpr const identity_t       identity_;
    //static constexpr const rows_t           rows_;
    //static constexpr const w_t              w_;
    //static constexpr const x_t              x_;
    //static constexpr const y_t              y_;
    //static constexpr const z_t              z_;
    //static constexpr const zero_t           zero_;
    
    static constexpr const all_t            ALL;
    static constexpr const ccw_t            CCW;
    static constexpr const clock_arg_t      CLOCK;
    static constexpr const clockwise_t      CLOCKWISE;
    static constexpr const columns_t        COLUMNS;
    static constexpr const diagonal_t       DIAGONAL;
    static constexpr const diameter_t       DIAMETER;
    static constexpr const down_t           DOWN;
    static constexpr const euler_t          EULER;
    static constexpr const focus_t          FOCUS;
    static constexpr const guard_t          GUARD;
    static constexpr const hpr_t            HPR;
    static constexpr const identity_t       IDENTITY;
    static constexpr const intersect_t      INTERSECT;
    static constexpr const nan_t            NAN;
    static constexpr const normal_t         NORMAL;
    static constexpr const one_t            ONE;
    static constexpr const opposite_t       OPPOSITE; 
    static constexpr const rotor_t          ROTOR;
    static constexpr const rows_t           ROWS;
    static constexpr const sort_t           SORT;
    static constexpr const union_t          UNION;
    static constexpr const unit_t           UNIT;
    static constexpr const up_t             UP;
    static constexpr const w_t              W;
    static constexpr const ww_t             WW;
    static constexpr const wx_t             WX;
    static constexpr const wxy_t            WXY;
    static constexpr const wy_t             WY;
    static constexpr const wz_t             WZ;
    static constexpr const x_t              X;
    static constexpr const xw_t             XW;
    static constexpr const xx_t             XX;
    static constexpr const xy_t             XY;
    static constexpr const xyz_t            XYZ;
    static constexpr const xyzw_t           XYZW;
    static constexpr const xz_t             XZ;
    static constexpr const y_t              Y;
    static constexpr const yw_t             YW;
    static constexpr const yx_t             YX;
    static constexpr const yy_t             YY;
    static constexpr const yz_t             YZ;
    static constexpr const yzw_t            YZW;
    static constexpr const z_t              Z;
    static constexpr const zw_t             ZW;
    static constexpr const zwx_t            ZWX;
    static constexpr const zx_t             ZX;
    static constexpr const zy_t             ZY;
    static constexpr const zz_t             ZZ;
    static constexpr const zero_t           ZERO;

    static constexpr const two_t            ²;
    static constexpr const three_t          ³;
    
}
