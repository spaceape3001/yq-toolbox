////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/Obj.hpp>
#include <yq/art/vertex.hpp>

namespace yq::art {

    /*! \brief User defined point
    
        This is a user defined point, could be to share, to annotate, etc
    */
    class Point : public Obj {
        YQ_OBJECT_DECLARE(Point, Obj)
    public:

        static void init_meta();
    
        Point(Doc&);
        virtual ~Point();
        
        const vertex_t&     vertex() const { return m_vertex; }
        void                vertex(set_k, const vertex_t&);

    protected:
        virtual void    save_to(XmlNode&) const override;
        virtual bool    load_from(const XmlNode&) override;
        
    private:
        vertex_t            m_vertex;
    };
    
}
