////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGBA.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/core/UniqueID.hpp>
#include <yq/xg/types.hpp>
#include <yq/trait/numbers.hpp>

namespace yq::xg {
    class XGRuntime;
    
    class XGElementMeta : public ObjectMeta {
    public:
        template <typename> class Writer;
        
        XGElementMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        bool                always() const { return m_always; }
        const RGBA4F&       bgcolor() const { return m_bgcolor; }
        std::string_view    category() const { return m_category; }
        const RGBA4F&       color() const { return m_color; }
        //! Lets user know this is a *decision* type of element
        bool                decision() const { return m_decision; }
        float               priority() const { return m_priority; }
        bool                start() const { return m_start; }
        
        static const std::vector<const XGElementMeta*>& all();

    private:
        bool                m_always        = false;
        std::string_view    m_category      = "";
        RGBA4F              m_bgcolor       = { 0., 0., 0., 0. };
        RGBA4F              m_color         = { 0., 0., 0., 0. };
        bool                m_decision      = false;
        float               m_priority      = NaNf;
        bool                m_start         = false;
        
        struct Repo;
        static Repo&    repo();
    };

    class XGElement : public Object, public UniqueID {
        YQ_OBJECT_META(XGElementMeta)
        YQ_OBJECT_DECLARE(XGElement, Object)
    public:
    
        virtual result_t    execute(XGContext&);
        
        //! True if this an always node
        bool                always() const;
        
        //! True if this is the starting node (should generally only be ONE per document)
        bool                start() const;
        
        float               priority() const;
        
        static void init_meta();
        
    protected:
        XGElement();
        virtual ~XGElement();
    
    private:
        friend class XGRuntime;
        
        std::vector<execute_t>  m_next;
        Tristate                m_always    = Tristate::Inherit;
        Tristate                m_start     = Tristate::Inherit;
        float                   m_priority  = NaNf;
    };
}
