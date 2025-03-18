////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/1D/Py1.hpp>
#include <ys/PyInfoWriter.hpp>

namespace yq::spatial {
    template <typename T>
    class Py1Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py1Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py1Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
