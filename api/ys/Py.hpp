////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/SObject.hpp>

namespace yq::spatial {
    class PyInfo : public SObjectInfo {
    public:
        template <typename T> class Writer;
        PyInfo(std::string_view zName, SObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A physical object
    
        This represents a physical object, the number represents the number of coordinates needed to describe it.
    */
    class Py : public SObject {
        YQ_OBJECT_INFO(PyInfo)
        YQ_OBJECT_DECLARE(Py, SObject)
    public:
    
        virtual uint8_t dimensions(count_k) const = 0;
    
        static void init_info();
    
    protected:
        Py(SDocument&);
        Py(SDocument&, const Py&);
        ~Py();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py(const Py&) = delete;
        Py(Py&&) = delete;
        Py& operator=(const Py&) = delete;
        Py& operator=(Py&&) = delete;
    };
}
