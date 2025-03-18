////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/Py.hpp>
#include <yq/typedef/vector4.hpp>

namespace yq::spatial {
    class Py4Info : public PyInfo {
    public:
        template <typename T> class Writer;
        Py4Info(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };

    struct Vector4S {
        std::string x;
        std::string y;
        std::string z;
        std::string w;
    };
    
    /*! A physical object in 4D
    */
    class Py4 : public Py {
        YQ_OBJECT_INFO(Py4Info)
        YQ_OBJECT_DECLARE(Py4, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 4; }

        static void init_info();
        
        std::string_view    x() const;
        std::string_view    y() const;
        std::string_view    z() const;
        std::string_view    w() const;

    protected:
        Py4(SDocument&);
        Py4(SDocument&, const Py4&);
        ~Py4();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py4(const Py4&) = delete;
        Py4(Py4&&) = delete;
        Py4& operator=(const Py4&) = delete;
        Py4& operator=(Py4&&) = delete;
    };

}
