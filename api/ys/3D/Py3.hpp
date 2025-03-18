////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/Py.hpp>
#include <yq/typedef/vector3.hpp>

namespace yq::spatial {
    class Py3Info : public PyInfo {
    public:
        template <typename T> class Writer;
        Py3Info(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    struct Vector3S {
        std::string x;
        std::string y;
        std::string z;
    };

    /*! A physical object in 3D
    */
    class Py3 : public Py {
        YQ_OBJECT_INFO(Py3Info)
        YQ_OBJECT_DECLARE(Py3, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 3; }

        static void init_info();
        
        std::string_view    x() const;
        std::string_view    y() const;
        std::string_view    z() const;

    protected:
        Py3(SDocument&);
        Py3(SDocument&, const Py3&);
        ~Py3();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py3(const Py3&) = delete;
        Py3(Py3&&) = delete;
        Py3& operator=(const Py3&) = delete;
        Py3& operator=(Py3&&) = delete;
    };

}
