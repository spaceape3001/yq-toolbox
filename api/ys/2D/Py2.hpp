////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/Py.hpp>
#include <yq/typedef/vector2.hpp>

namespace yq::spatial {
    class Py2Info : public PyInfo {
    public:
        template <typename T> class Writer;
        Py2Info(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    struct Vector2S {
        std::string x;
        std::string y;
    };

    /*! A physical object in 2D
    */
    class Py2 : public Py {
        YQ_OBJECT_INFO(Py2Info)
        YQ_OBJECT_DECLARE(Py2, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 2; }

        static void init_info();
        
        std::string_view    x() const;
        std::string_view    y() const;

    protected:
        Py2(SDocument&);
        Py2(SDocument&, const Py2&);
        ~Py2();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py2(const Py2&) = delete;
        Py2(Py2&&) = delete;
        Py2& operator=(const Py2&) = delete;
        Py2& operator=(Py2&&) = delete;
    };

}
