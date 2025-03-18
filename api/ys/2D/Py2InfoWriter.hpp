////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/2D/Py2.hpp>
#include <ys/PyInfoWriter.hpp>

namespace yq::spatial {
    template <typename T>
    class Py2Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py2Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py2Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
