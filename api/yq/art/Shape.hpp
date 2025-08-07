////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/Obj.hpp>
#include <yq/art/vertex.hpp>

namespace yq::art {
    class Shape : public Obj {
        YQ_OBJECT_DECLARE(Shape, Obj)
    public:
        
        static void init_meta();
    
        Shape(Doc&);
        ~Shape();
        
        // Override for your shape....
        
        virtual size_t          vertex(count_k) const { return 0; }
        virtual bool            vertex(appendable_k) const { return false; }
        virtual bool            vertex(erasable_k) const { return false; }

        virtual const vertex_t* vertex(size_t) const { return nullptr; }
        virtual bool            vertex(size_t, erase_k) { return false; }
        virtual bool            vertex(size_t, set_k, const vertex_t&) { return false; }
        virtual bool            vertex(append_k, const vertex_t&) { return false; }
        
    protected:
    

        virtual void    save_to(XmlNode&) const override;
        virtual bool    load_from(const XmlNode&) override;
    };
}

