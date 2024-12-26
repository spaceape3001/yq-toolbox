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

    // Problematic macros...
    #ifdef NAN
        #undef NAN
    #endif

        //  keywords
    struct absolute_k {};
    struct all_k {};
    struct allocate_k {};
    struct always_k {};
    struct any_k {};
    struct box_k {};
    struct cache_k {};
    struct cancel_k {};
    struct ccw_k {};
    struct cerr_k {};
    struct circle_k {};
    struct class_k {};
    struct clock_arg_k {};
    struct clockwise_k {};
    struct clear_k {};
    struct columns_k {};
    struct copy_k {};
    struct cout_k {};
    struct count_k {};
    struct cursor_k {};
    struct data_k {};
    struct default_k {};
    struct diagonal_k {};
    struct diameter_k {};
    struct dimensions_k {};
    struct disabled_k {};
    struct done_k {};
    struct down_k {};
    struct easter_k {};
    struct edge_k {};
    struct ellipse_k {};
    struct empty_k {};
    struct euler_k {};
    struct even_k {};
    struct every_k {};
    struct fail_k {};
    struct focus_k {};
    struct frequency_k {};
    struct full_k {};
    struct from_k {};
    struct global_k {};
    struct graph_k {};
    struct gregorian_k {};
    struct guard_k {};
    struct high_k {};
    struct hpr_k {};
    struct i_k {};
    struct identity_k {};
    struct if_k {};
    struct igcase_k {};
    struct individual_k {};
    struct init_k {};
    struct intersect_k {};
    struct interval_k {};
    struct j_k {};
    struct json_k {};
    struct julian_k {};
    struct k_k {};
    struct l_k {};
    struct layout_k {};
    struct line_k {};
    struct local_k {};
    struct low_k {};
    struct m_k {};
    struct maybe_k {};
    struct move_k {};
    struct n_k {};
    struct nan_k {};
    struct negative_k {};
    struct no_k {};
    struct no_khrow_k {};
    struct node_k {};
    struct none_k {};
    struct normal_k {};
    struct normalized_k {};
    struct not_k {};
    struct odd_k {};
    struct once_k {};
    struct one_k {};
    struct only_k {};
    struct opposite_k {};
    struct optional_k {};
    struct parse_k {};
    struct partial_k {};
    struct pass_k {};
    struct pickup_k {};
    struct pixel_k {};
    struct pixels_k {};
    struct pointer_k {};
    struct positive_k {};
    struct pull_k {};
    struct push_k {};
    struct read_only_k {};
    struct receiver_k {};
    struct recipient_k {};
    struct recursive_k {};
    struct rectangle_k {};
    struct ref_k {};
    struct reference_k {};
    struct remote_k {};
    struct repo_k {};
    struct required_k {};
    struct return_k {};
    struct rotor_k {};
    struct rows_k {};
    struct rx_k {};
    struct self_k {};
    struct sender_k {};
    struct set_k {};
    struct skip_k {};
    struct snoop_k {};
    struct sort_k {};
    struct span_k {};
    struct square_k {};
    struct stem_k {};
    struct thread_k {};
    struct three_k {};
    struct throw_k {};
    struct ticks_k {};
    struct timeout_k {};
    struct triangle_k {};
    struct to_k {};
    struct today_k {};
    struct total_k {};
    struct two_k {};
    struct tx_k {};
    struct type_k {};
    struct union_k {};
    struct unit_k {};
    struct up_k {};
    struct w_k {};
    struct ww_k {};
    struct wx_k {};
    struct wxy_k {};
    struct wy_k {};
    struct wz_k {};
    struct x_k {};
    struct xml_k {};
    struct xw_k {};
    struct xx_k {};
    struct xy_k {};
    struct xyz_k {};
    struct xyzw_k {};
    struct xz_k {};
    struct y_k {};
    struct yes_k {};
    struct yw_k {};
    struct yx_k {};
    struct yy_k {};
    struct yz_k {};
    struct yzw_k {};
    struct z_k {};
    struct zero_k {};
    struct zw_k {};
    struct zwx_k {};
    struct zx_k {};
    struct zy_k {};
    struct zz_k {};

    static constexpr const absolute_k       ABSOLUTE;
    static constexpr const all_k            ALL;
    static constexpr const allocate_k       ALLOCATE;
    static constexpr const always_k         ALWAYS;
    static constexpr const any_k            ANY;
    static constexpr const box_k            BOX;
    static constexpr const cache_k          CACHE;
    static constexpr const cancel_k         CANCEL;
    static constexpr const ccw_k            CCW;
    static constexpr const cerr_k           CERR;
    static constexpr const circle_k         CIRCLE;
    static constexpr const class_k          CLASS;
    static constexpr const clear_k          CLEAR;
    static constexpr const clock_arg_k      CLOCK;
    static constexpr const clockwise_k      CLOCKWISE;
    static constexpr const columns_k        COLUMNS;
    static constexpr const copy_k           COPY;
    static constexpr const count_k          COUNT;
    static constexpr const cout_k           COUT;
    static constexpr const cursor_k         CURSOR;
    static constexpr const data_k           DATA;
    static constexpr const default_k        DEFAULT;
    static constexpr const diagonal_k       DIAGONAL;
    static constexpr const diameter_k       DIAMETER;
    static constexpr const dimensions_k     DIMENSIONS;
    static constexpr const disabled_k       DISABLED;
    static constexpr const done_k           DONE;
    static constexpr const down_k           DOWN;
    static constexpr const easter_k         EASTER;
    static constexpr const edge_k           EDGE;
    static constexpr const ellipse_k        ELLIPSE;
    static constexpr const empty_k          EMPTY;
    static constexpr const euler_k          EULER;
    static constexpr const even_k           EVEN;
    static constexpr const every_k          EVERY;
    static constexpr const fail_k           FAIL;
    static constexpr const focus_k          FOCUS;
    static constexpr const frequency_k      FREQUENCY;
    static constexpr const full_k           FULL;
    static constexpr const from_k           FROM;
    static constexpr const global_k         GLOBAL;
    static constexpr const graph_k          GRAPH;
    static constexpr const gregorian_k      GREGORIAN;
    static constexpr const guard_k          GUARD;
    static constexpr const hpr_k            HPR;
    static constexpr const high_k           HIGH;
    static constexpr const i_k              I;
    static constexpr const identity_k       IDENTITY;
    static constexpr const if_k             IF;
    static constexpr const igcase_k         IGCASE;
    static constexpr const individual_k     INDIVIDUAL;
    static constexpr const init_k           INIT;
    static constexpr const intersect_k      INTERSECT;
    static constexpr const interval_k       INTERVAL;
    static constexpr const j_k              J;
    static constexpr const json_k           JSON;
    static constexpr const julian_k         JULIAN;
    static constexpr const k_k              K;
    static constexpr const l_k              L;
    static constexpr const layout_k         LAYOUT;
    static constexpr const line_k           LINE;
    static constexpr const local_k          LOCAL;
    static constexpr const low_k            LOW;
    static constexpr const m_k              M;
    static constexpr const maybe_k          MAYBE;
    static constexpr const move_k           MOVE;
    static constexpr const n_k              N;
    static constexpr const nan_k            NAN;
    static constexpr const negative_k       NEGATIVE;
    static constexpr const no_k             NO;
    static constexpr const no_khrow_k       NO_THROW;
    static constexpr const node_k           NODE;
    static constexpr const none_k           NONE;
    static constexpr const normal_k         NORMAL;
    static constexpr const normalized_k     NORMALIZED;
    static constexpr const not_k            NOT;
    static constexpr const odd_k            ODD;
    static constexpr const once_k           ONCE;
    static constexpr const one_k            ONE;
    static constexpr const only_k           ONLY;
    static constexpr const opposite_k       OPPOSITE; 
    static constexpr const optional_k       OPTIONAL;
    static constexpr const parse_k          PARSE;
    static constexpr const partial_k        PARTIAL;
    static constexpr const pass_k           PASS;
    static constexpr const pickup_k         PICKUP;
    static constexpr const pixel_k          PIXEL;
    static constexpr const pixels_k         PIXELS;
    static constexpr const pointer_k        POINTER;
    static constexpr const positive_k       POSITIVE;
    static constexpr const pull_k           PULL;
    static constexpr const push_k           PUSH;
    static constexpr const read_only_k      READ_ONLY;
    static constexpr const receiver_k       RECEIVER;
    static constexpr const recipient_k      RECIPIENT;
    static constexpr const rectangle_k      RECTANGLE;
    static constexpr const recursive_k      RECURSIVE;
    static constexpr const ref_k            REF;
    static constexpr const reference_k      REFERENCE;
    static constexpr const remote_k         REMOTE;
    static constexpr const repo_k           REPO;
    static constexpr const required_k       REQUIRED;
    static constexpr const return_k         RETURN;
    static constexpr const rotor_k          ROTOR;
    static constexpr const rows_k           ROWS;
    static constexpr const rx_k             RX;
    static constexpr const self_k           SELF;
    static constexpr const sender_k         SENDER;
    static constexpr const set_k            SET;
    static constexpr const skip_k           SKIP;
    static constexpr const sort_k           SORT;
    static constexpr const snoop_k          SNOOP;
    static constexpr const span_k           SPAN;
    static constexpr const square_k         SQUARE;
    static constexpr const stem_k           STEM;
    static constexpr const thread_k         THREAD;
    static constexpr const three_k          THREE;
    static constexpr const throw_k          THROW;
    static constexpr const ticks_k          TICKS;
    static constexpr const timeout_k        TIMEOUT;
    static constexpr const to_k             TO;
    static constexpr const today_k          TODAY;
    static constexpr const total_k          TOTAL;
    static constexpr const triangle_k       TRIANGLE;
    static constexpr const two_k            TWO;
    static constexpr const tx_k             TX;
    static constexpr const type_k           TYPE;
    static constexpr const union_k          UNION;
    static constexpr const unit_k           UNIT;
    static constexpr const up_k             UP;
    static constexpr const w_k              W;
    static constexpr const ww_k             WW;
    static constexpr const wx_k             WX;
    static constexpr const wxy_k            WXY;
    static constexpr const wy_k             WY;
    static constexpr const wz_k             WZ;
    static constexpr const x_k              X;
    static constexpr const xml_k            XML;
    static constexpr const xw_k             XW;
    static constexpr const xx_k             XX;
    static constexpr const xy_k             XY;
    static constexpr const xyz_k            XYZ;
    static constexpr const xyzw_k           XYZW;
    static constexpr const xz_k             XZ;
    static constexpr const y_k              Y;
    static constexpr const yes_k            YES;
    static constexpr const yw_k             YW;
    static constexpr const yx_k             YX;
    static constexpr const yy_k             YY;
    static constexpr const yz_k             YZ;
    static constexpr const yzw_k            YZW;
    static constexpr const z_k              Z;
    static constexpr const zero_k           ZERO;
    static constexpr const zw_k             ZW;
    static constexpr const zwx_k            ZWX;
    static constexpr const zx_k             ZX;
    static constexpr const zy_k             ZY;
    static constexpr const zz_k             ZZ;

    static constexpr const two_k            ²;
    static constexpr const three_k          ³;
}
