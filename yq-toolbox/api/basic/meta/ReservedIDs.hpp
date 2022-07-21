////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef YQ__CORE__OVERRIDE
    #error  "Don't include this outside of the meta sub-comopnent!"
#endif

namespace yq {
    //  Reserved IDs
    enum {
        MT_Invalid      = 0,
        MT_Any,
        MC_Global,      // Global is a compound, not type
        MT_String,
        MT_Boolean,
        MT_Float,
        MT_Double,
        MT_Int8,
        MT_Int16,
        MT_Int32,
        MT_Int64,
        MT_UInt8,
        MT_UInt16,
        MT_UInt32,
        MT_UInt64,
        
        M_USER
    };
}

