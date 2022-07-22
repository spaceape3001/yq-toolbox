////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    namespace trait {
        //! Trait to prohibit moving
        class not_moveable {
            not_moveable(not_moveable&&) = delete;
            not_moveable& operator=(not_moveable&&) = delete;
        protected:
            not_moveable(){}
        };
    }
}
