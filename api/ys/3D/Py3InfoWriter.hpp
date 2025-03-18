////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/3D/Py3.hpp>
#include <ys/PyInfoWriter.hpp>

namespace yq::spatial {
    template <typename T>
    class Py3Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py3Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py3Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
