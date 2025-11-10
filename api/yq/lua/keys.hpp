////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::lua {
    //  standard keys for internals
    static constexpr const char* keyVM                  = "_vm";
    static constexpr const char* keyName                = "_name";
    static constexpr const char* keyStem                = "_stem";
    static constexpr const char* keyDescription         = "_desc";
    static constexpr const char* keyMeta                = "_meta";
    static constexpr const char* keyPointer             = "_ptr";
    static constexpr const char* keyFlags               = "_flags";
    static constexpr const char* keyGarbageCollection   = "__gc"; // LUA's
    static constexpr const char* keyOutput              = "_output";
    static constexpr const char* keyError               = "_error";
    static constexpr const char* keyWarning             = "_warning";
}
