////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/Py.hpp>
#include <yq/typedef/vector1.hpp>

namespace yq::spatial {
    class Py1Info : public PyInfo {
    public:
        template <typename T> class Writer;
        Py1Info(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };

    struct Vector1S {
        std::string x;
    };
    
    /*! A physical object in 1D
    */
    class Py1 : public Py {
        YQ_OBJECT_INFO(Py1Info)
        YQ_OBJECT_DECLARE(Py1, Py)
    public:
    
        static constexpr const char *szX     = "x";
    
        virtual uint8_t dimensions(count_k) const final { return 1; }

        static void init_info();
        
        std::string_view    x() const;

    protected:
        Py1(SDocument&);
        Py1(SDocument&, const Py1&);
        ~Py1();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py1(const Py1&) = delete;
        Py1(Py1&&) = delete;
        Py1& operator=(const Py1&) = delete;
        Py1& operator=(Py1&&) = delete;
    };

}
