////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py.hpp"
#include "PyInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::spatial::Py)

namespace yq::spatial {
    PyInfo::PyInfo(std::string_view zName, SObjectInfo& base, const std::source_location& sl) : 
        SObjectInfo(zName, base, sl)
    {
        set(Flag::PHYSICAL);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py::init_info()
    {
        auto w = writer<Py>();
        w.description("Physical Object");
    }

    Py::Py(SDocument& prj) : SObject(prj)
    {
    }
    
    Py::Py(SDocument& prj, const Py&cp) : SObject(prj, cp)
    {
    }

    Py::~Py()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py::remap(const Remapper&rMap)
    {
        SObject::remap(rMap);
    }
}

