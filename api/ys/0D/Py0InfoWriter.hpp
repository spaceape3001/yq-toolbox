////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/0D/Py0.hpp>
#include <ys/PyInfoWriter.hpp>

namespace yq::spatial {
    template <typename T>
    class Py0Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py0Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py0Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
