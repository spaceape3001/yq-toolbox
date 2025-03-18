////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py1.hpp"
#include "Py1InfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::spatial::Py1)

namespace yq::spatial {
    Py1Info::Py1Info(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D1);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py1::init_info()
    {
        auto w = writer<Py1>();
        w.description("Physical Object in 1D");
    }

    Py1::Py1(SDocument& prj) : Py(prj)
    {
    }
    
    Py1::Py1(SDocument& prj, const Py1&cp) : Py(prj, cp)
    {
    }

    Py1::~Py1()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py1::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py1::x() const
    {
        return attribute("x");
    }

}

