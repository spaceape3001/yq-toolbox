////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/meta/Meta.hpp>
#include <basic/meta/ArgInfo.hpp>

namespace yq {
    class MethodInfo : public Meta {
    public:
    
        class Writer;
    
        const LUC<ArgInfo>&     args() const { return m_args; }
        const ArgInfo*          result() const { return m_result; }
    
    protected:
        const ArgInfo*          m_result;
        LUC<ArgInfo>            m_args;
        MethodInfo(std::string_view zName, const std::source_location& sl, Meta*, options_t opts=0);
    };
}
