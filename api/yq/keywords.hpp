////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    This file is about making new keywords that can be used in the constructors 
    and function overloads.
    
    In certain circumstances, when the names are identical, rather than having
    a constructor have a possible nonsensical overload *OR* dealing with a 
    myriad of static methods for construction, we're adding keywords to allow
    for distinctions.  
    
    For example, in the case of a vector4, you can use NAN as the constructor
    keyword to get a vector populated by all NANs.  For a Quaternion, a 
    euler-angle based rotator can be created using the HPR keyword.
*/

namespace yq {

    #ifdef NAN
    #undef NAN
    #endif

        //  keywords
    struct absolute_t {};
    struct all_t {};
    struct allocate_t {};
    struct always_t {};
    struct any_t {};
    struct box_t {};
    struct cache_t {};
    struct cancel_t {};
    struct ccw_t {};
    struct cerr_t {};
    struct circle_t {};
    struct class_t {};
    struct clock_arg_t {};
    struct clockwise_t {};
    struct clear_t {};
    struct columns_t {};
    struct copy_t {};
    struct cout_t {};
    struct count_t {};
    struct data_t {};
    struct default_t {};
    struct diagonal_t {};
    struct diameter_t {};
    struct dimensions_t {};
    struct disabled_t {};
    struct done_t {};
    struct down_t {};
    struct easter_t {};
    struct edge_t {};
    struct ellipse_t {};
    struct euler_t {};
    struct even_t {};
    struct every_t {};
    struct focus_t {};
    struct frequency_t {};
    struct full_t {};
    struct global_t {};
    struct graph_t {};
    struct gregorian_t {};
    struct guard_t {};
    struct hpr_t {};
    struct i_t {};
    struct identity_t {};
    struct igcase_t {};
    struct individual_t {};
    struct intersect_t {};
    struct interval_t {};
    struct j_t {};
    struct json_t {};
    struct julian_t {};
    struct k_t {};
    struct l_t {};
    struct layout_t {};
    struct line_t {};
    struct m_t {};
    struct maybe_t {};
    struct move_t {};
    struct n_t {};
    struct nan_t {};
    struct negative_t {};
    struct no_t {};
    struct no_throw_t {};
    struct node_t {};
    struct normal_t {};
    struct normalized_t {};
    struct odd_t {};
    struct once_t {};
    struct one_t {};
    struct opposite_t {};
    struct optional_t {};
    struct parse_t {};
    struct partial_t {};
    struct pixel_t {};
    struct pixels_t {};
    struct positive_t {};
    struct read_only_t {};
    struct recursive_t {};
    struct rectangle_t {};
    struct ref_t {};
    struct repo_t {};
    struct required_t {};
    struct rotor_t {};
    struct rows_t {};
    struct set_t {};
    struct skip_t {};
    struct sort_t {};
    struct span_t {};
    struct stem_t {};
    struct three_t {};
    struct throw_t {};
    struct ticks_t {};
    struct triangle_t {};
    struct today_t {};
    struct total_t {};
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
    struct xml_t {};
    struct xw_t {};
    struct xx_t {};
    struct xy_t {};
    struct xyz_t {};
    struct xyzw_t {};
    struct xz_t {};
    struct y_t {};
    struct yes_t {};
    struct yw_t {};
    struct yx_t {};
    struct yy_t {};
    struct yz_t {};
    struct yzw_t {};
    struct z_t {};
    struct zero_t {};
    struct zw_t {};
    struct zwx_t {};
    struct zx_t {};
    struct zy_t {};
    struct zz_t {};

    static constexpr const absolute_t       ABSOLUTE;
    static constexpr const all_t            ALL;
    static constexpr const allocate_t       ALLOCATE;
    static constexpr const always_t         ALWAYS;
    static constexpr const any_t            ANY;
    static constexpr const box_t            BOX;
    static constexpr const cache_t          CACHE;
    static constexpr const cancel_t         CANCEL;
    static constexpr const ccw_t            CCW;
    static constexpr const cerr_t           CERR;
    static constexpr const circle_t         CIRCLE;
    static constexpr const class_t          CLASS;
    static constexpr const clear_t          CLEAR;
    static constexpr const clock_arg_t      CLOCK;
    static constexpr const clockwise_t      CLOCKWISE;
    static constexpr const columns_t        COLUMNS;
    static constexpr const copy_t           COPY;
    static constexpr const count_t          COUNT;
    static constexpr const cout_t           COUT;
    static constexpr const data_t           DATA;
    static constexpr const default_t        DEFAULT;
    static constexpr const diagonal_t       DIAGONAL;
    static constexpr const diameter_t       DIAMETER;
    static constexpr const dimensions_t     DIMENSIONS;
    static constexpr const disabled_t       DISABLED;
    static constexpr const done_t           DONE;
    static constexpr const down_t           DOWN;
    static constexpr const easter_t         EASTER;
    static constexpr const edge_t           EDGE;
    static constexpr const ellipse_t        ELLIPSE;
    static constexpr const euler_t          EULER;
    static constexpr const even_t           EVEN;
    static constexpr const every_t          EVERY;
    static constexpr const focus_t          FOCUS;
    static constexpr const frequency_t      FREQUENCY;
    static constexpr const full_t           FULL;
    static constexpr const global_t         GLOBAL;
    static constexpr const graph_t          GRAPH;
    static constexpr const gregorian_t      GREGORIAN;
    static constexpr const guard_t          GUARD;
    static constexpr const hpr_t            HPR;
    static constexpr const i_t              I;
    static constexpr const identity_t       IDENTITY;
    static constexpr const igcase_t         IGCASE;
    static constexpr const individual_t     INDIVIDUAL;
    static constexpr const intersect_t      INTERSECT;
    static constexpr const interval_t       INTERVAL;
    static constexpr const j_t              J;
    static constexpr const json_t           JSON;
    static constexpr const julian_t         JULIAN;
    static constexpr const k_t              K;
    static constexpr const l_t              L;
    static constexpr const layout_t         LAYOUT;
    static constexpr const line_t           LINE;
    static constexpr const m_t              M;
    static constexpr const maybe_t          MAYBE;
    static constexpr const move_t           MOVE;
    static constexpr const n_t              N;
    static constexpr const nan_t            NAN;
    static constexpr const negative_t       NEGATIVE;
    static constexpr const no_t             NO;
    static constexpr const no_throw_t       NO_THROW;
    static constexpr const node_t           NODE;
    static constexpr const normal_t         NORMAL;
    static constexpr const normalized_t     NORMALIZED;
    static constexpr const odd_t            ODD;
    static constexpr const once_t           ONCE;
    static constexpr const one_t            ONE;
    static constexpr const opposite_t       OPPOSITE; 
    static constexpr const optional_t       OPTIONAL;
    static constexpr const parse_t          PARSE;
    static constexpr const partial_t        PARTIAL;
    static constexpr const pixel_t          PIXEL;
    static constexpr const pixels_t         PIXELS;
    static constexpr const positive_t       POSITIVE;
    static constexpr const read_only_t      READ_ONLY;
    static constexpr const rectangle_t      RECTANGLE;
    static constexpr const recursive_t      RECURSIVE;
    static constexpr const ref_t            REF;
    static constexpr const repo_t           REPO;
    static constexpr const required_t       REQUIRED;
    static constexpr const rotor_t          ROTOR;
    static constexpr const rows_t           ROWS;
    static constexpr const set_t            SET;
    static constexpr const skip_t           SKIP;
    static constexpr const sort_t           SORT;
    static constexpr const span_t           SPAN;
    static constexpr const stem_t           STEM;
    static constexpr const three_t          THREE;
    static constexpr const throw_t          THROW;
    static constexpr const ticks_t          TICKS;
    static constexpr const today_t          TODAY;
    static constexpr const total_t          TOTAL;
    static constexpr const triangle_t       TRIANGLE;
    static constexpr const two_t            TWO;
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
    static constexpr const xml_t            XML;
    static constexpr const xw_t             XW;
    static constexpr const xx_t             XX;
    static constexpr const xy_t             XY;
    static constexpr const xyz_t            XYZ;
    static constexpr const xyzw_t           XYZW;
    static constexpr const xz_t             XZ;
    static constexpr const y_t              Y;
    static constexpr const yes_t            YES;
    static constexpr const yw_t             YW;
    static constexpr const yx_t             YX;
    static constexpr const yy_t             YY;
    static constexpr const yz_t             YZ;
    static constexpr const yzw_t            YZW;
    static constexpr const z_t              Z;
    static constexpr const zero_t           ZERO;
    static constexpr const zw_t             ZW;
    static constexpr const zwx_t            ZWX;
    static constexpr const zx_t             ZX;
    static constexpr const zy_t             ZY;
    static constexpr const zz_t             ZZ;

    static constexpr const two_t            ²;
    static constexpr const three_t          ³;
}
