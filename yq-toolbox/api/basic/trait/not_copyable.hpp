////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    namespace trait {

        //! Trait to prohibit copying
        class not_copyable {
            not_copyable(const not_copyable&) = delete;
            not_copyable& operator=(const not_copyable&) = delete;
        protected:
            not_copyable(){}
        };

    }
}
