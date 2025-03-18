////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py4.hpp"
#include "Py4InfoWriter.hpp"
#include <ys/strings.hpp>

YQ_OBJECT_IMPLEMENT(yq::spatial::Py4)

namespace yq::spatial {
    Py4Info::Py4Info(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D4);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py4::init_info()
    {
        auto w = writer<Py4>();
        w.description("Physical Object in 4D");
    }

    Py4::Py4(SDocument& doc) : Py(doc)
    {
    }
    
    Py4::Py4(SDocument& doc, const Py4&cp) : Py(doc, cp)
    {
    }

    Py4::~Py4()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py4::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py4::x() const
    {
        return attribute("x");
    }

    std::string_view    Py4::y() const
    {
        return attribute("y");
    }
    
    std::string_view    Py4::z() const
    {
        return attribute("z");
    }
    
    std::string_view    Py4::w() const
    {
        return attribute("w");
    }

}

