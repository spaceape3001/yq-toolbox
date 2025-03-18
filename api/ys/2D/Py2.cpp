////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py2.hpp"
#include "Py2InfoWriter.hpp"
#include <ys/strings.hpp>

YQ_OBJECT_IMPLEMENT(yq::spatial::Py2)

namespace yq::spatial {
    Py2Info::Py2Info(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D2);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py2::init_info()
    {
        auto w = writer<Py2>();
        w.description("Physical Object in 2D");
    }

    Py2::Py2(SDocument& doc) : Py(doc)
    {
    }
    
    Py2::Py2(SDocument& doc, const Py2&cp) : Py(doc, cp)
    {
    }

    Py2::~Py2()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py2::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py2::x() const
    {
        return attribute("x");
    }

    std::string_view    Py2::y() const
    {
        return attribute("y");
    }
}

