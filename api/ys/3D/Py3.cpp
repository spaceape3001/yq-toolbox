////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py3.hpp"
#include "Py3InfoWriter.hpp"
#include <ys/strings.hpp>

YQ_OBJECT_IMPLEMENT(yq::spatial::Py3)

namespace yq::spatial {
    Py3Info::Py3Info(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D3);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py3::init_info()
    {
        auto w = writer<Py3>();
        w.description("Physical Object in 3D");
    }

    Py3::Py3(SDocument& doc) : Py(doc)
    {
    }
    
    Py3::Py3(SDocument& doc, const Py3&cp) : Py(doc, cp)
    {
    }

    Py3::~Py3()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py3::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py3::x() const
    {
        return attribute("x");
    }

    std::string_view    Py3::y() const
    {
        return attribute("y");
    }
    
    std::string_view    Py3::z() const
    {
        return attribute("z");
    }
}

