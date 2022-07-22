////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/DelayInit.hpp>
#include <basic/ThreadId.hpp>
#include <basic/meta/Meta.hpp>
#include <basic/meta/MetaRepo.hpp>
#include <basic/meta/ReservedIDs.hpp>
#include <basic/Any.hpp>
#include <cassert>

namespace yq {

    const Vector<const Meta*>&   Meta::all()
    {
        assert(thread_safe_read());
        return repo().all;
    }


    void    Meta::freeze()
    {
        init();
        repo().openReg  = false;
    }

    void    Meta::init()
    {
        if(thread_safe_write()){
            DelayInit::init_all();
            sweep_all();
        }
    }

    void    Meta::sweep_all()
    {
        if(thread_safe_write()){
            Repo&   r = repo();
            for(const Meta* m : r.all)
                if(m)   // gaps can show
                    const_cast<Meta*>(m) -> m_flags &= ~SWEPT;
            for(const Meta* m : r.all)
                if(m)
                    const_cast<Meta*>(m) -> sweep();
        }
    }

    bool    Meta::thread_safe_read()
    {
        return (!repo().openReg) || (!thread::id());
    }

    bool    Meta::thread_safe_write()
    {
        return repo().openReg && !thread::id();
    }

    bool    Meta::unlocked()
    {
        return repo().openReg;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    Meta::Meta(std::string_view zName, const std::source_location& sl, id_t i) : Meta(zName, nullptr, sl, i)
    {
    }
    
    Meta::Meta(std::string_view zName, Meta* parent, const std::source_location& sl, id_t i) 
    {
        assert(thread_safe_write());
        
        set_name(zName);
        m_label     = m_name;                       // default (can be overriden)
        m_parent    = parent;
        m_source    = sl;
        
        if(parent)
            parent->m_children.push_back(this);

        auto& _r     = repo();
        if(i < M_USER){
            m_id    = i;
            _r.all[i]   = this;
        } else {
            m_id    = _r.all.size();
            _r.all << this;
        }
        if(i >= MT_String)
            _r.metas << this;
    }
    
    Meta::~Meta()
    {
        assert(false && "Do NOT delete Meta!  It's not meant to be deleted.");

    }

    bool  Meta::has_tag(std::string_view k) const
    {
        return m_tags.contains(k);
    }

    void  Meta::set_name(std::string_view v) 
    { 
        //  strip out the yq namespace
        if(starts(v, "yq::"))
            m_name  = v.substr(4);
        else
            m_name = v;
        auto ecolon = m_name.find_last_of(':');
        if(ecolon != std::string_view::npos){
            m_stem  = m_name.substr(ecolon+1);
        } else
            m_stem  = m_name;
    }

    void  Meta::sweep()
    {
        assert(thread_safe_write());

        if(!(m_flags & SWEPT)){
            sweep_impl();
            m_flags |= SWEPT;
        }
    }

    const Any&  Meta::tag(std::string_view k) const
    {
        static Any bad;
        auto i = m_tags.find(k);
        if(i != m_tags.end())
            return i->second;
        return bad;
    }
}

