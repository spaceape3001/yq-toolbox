////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/Py.hpp>

namespace yq::spatial {
    class Py0Info : public PyInfo {
    public:
        template <typename T> class Writer;
        Py0Info(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    /*! A physical object in 0D
    */
    class Py0 : public Py {
        YQ_OBJECT_INFO(Py0Info)
        YQ_OBJECT_DECLARE(Py0, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 0; }

        static void init_info();

    protected:
        Py0(SDocument&);
        Py0(SDocument&, const Py0&);
        ~Py0();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py0(const Py0&) = delete;
        Py0(Py0&&) = delete;
        Py0& operator=(const Py0&) = delete;
        Py0& operator=(Py0&&) = delete;
    };

}
