////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/SObjectInfoWriter.hpp>
#include <ys/Py.hpp>

namespace yq::spatial {

    template <typename T>
    class PyInfo::Writer : public SObjectInfo::Writer<T> {
    public:
        Writer(PyInfo* pInfo) : SObjectInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(PyInfo& pInfo) : Writer(&pInfo)
        {
        }
    };
}
