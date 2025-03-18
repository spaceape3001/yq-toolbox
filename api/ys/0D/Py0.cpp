////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py0.hpp"
#include "Py0InfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::spatial::Py0)

namespace yq::spatial {
    Py0Info::Py0Info(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D0);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py0::init_info()
    {
        auto w = writer<Py0>();
        w.description("Physical Object in 0D");
    }

    Py0::Py0(SDocument& prj) : Py(prj)
    {
    }
    
    Py0::Py0(SDocument& prj, const Py0&cp) : Py(prj, cp)
    {
    }

    Py0::~Py0()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py0::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

}

