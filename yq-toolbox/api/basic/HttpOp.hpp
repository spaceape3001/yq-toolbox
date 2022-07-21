////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Enum.hpp>

namespace yq {

    YQ_ENUM(HttpOp, ,
        Unknown = 0,
        Error,          // shoved in here for the pages... not a real method
        Get,
        Head,
        Post,
        Put,
        Delete,
        Trace,
        Options,
        Connect,
        Patch
    )


    static constexpr const HttpOp::enum_t hConnect                  = HttpOp::Connect;
    static constexpr const HttpOp::enum_t hDelete                   = HttpOp::Delete;
    static constexpr const HttpOp::enum_t hGet                      = HttpOp::Get;
    static constexpr const HttpOp::enum_t hHead                     = HttpOp::Head;
    static constexpr const HttpOp::enum_t hOptions                  = HttpOp::Options;
    static constexpr const HttpOp::enum_t hPatch                    = HttpOp::Patch;
    static constexpr const HttpOp::enum_t hPost                     = HttpOp::Post;
    static constexpr const HttpOp::enum_t hPut                      = HttpOp::Put;
    static constexpr const HttpOp::enum_t hTrace                    = HttpOp::Trace;

}
