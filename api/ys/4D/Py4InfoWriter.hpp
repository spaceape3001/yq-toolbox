////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/4D/Py4.hpp>
#include <ys/PyInfoWriter.hpp>

namespace yq::spatial {
    template <typename T>
    class Py4Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py4Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py4Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
