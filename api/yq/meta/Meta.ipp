////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Meta.hpp"

#include <yq/core/Any.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/core/ThreadId.hpp>
#include <yq/meta/MetaRepo.hpp>
#include <yq/meta/ReservedIDs.hpp>
#include <yq/text/match.hpp>
#include <cassert>

namespace yq {

    Meta::Repo::Repo()
    {
        all.reserve(16384);      // adjust as necessary, performance tradeoff, basically
        all.resize(M_USER, nullptr);
    }
    
    Meta::Repo::~Repo()
    {
    }
    
    ////////////////////////////////////
    ////////////////////////////////////

    Meta::Repo&     Meta::repo()
    {
        static Repo*    s_repo  = new Repo;
        return *s_repo;
    }

    const std::vector<const Meta*>&   Meta::all()
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

    const Meta*                  Meta::lookup(id_t i)
    {
        Repo&   r   = repo();
        if(i < r.all.size())
            return r.all[i];
        return nullptr;
    }

    void    Meta::sweep_all()
    {
        if(thread_safe_write()){
            Repo&   r = repo();
            for(const Meta* m : r.all)
                if(m)   // gaps can show
                    const_cast<Meta*>(m) -> clear(Flag::SWEPT);
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
            _r.all.push_back(this);
        }
        if(i >= MT_String)
            _r.metas.push_back(this);
    }
    
    Meta::~Meta()
    {
        assert(false && "Do NOT delete Meta!  It's not meant to be deleted.");

    }

    void        Meta::add_alias(std::string_view sv)
    {
        m_aliases.insert(sv);
    }

    void        Meta::clear(Flag f)
    {
        m_flags.clear((size_t) f);
    }

    bool  Meta::has(Flag f) const
    {
        return m_flags[(size_t) f];
    }

    bool  Meta::has_tag(std::string_view k) const
    {
        return m_tags.contains(k);
    }

    bool  Meta::is_1d() const
    {
        return has(Flag::D1);
    }
    
    bool  Meta::is_2d() const
    {
        return has(Flag::D2);
    }
    
    bool  Meta::is_3d() const
    {
        return has(Flag::D3);
    }
    
    bool  Meta::is_4d() const
    {
        return has(Flag::D4);
    }

    bool  Meta::is_5d() const
    {
        return has(Flag::D5);
    }
    
    bool  Meta::is_6d() const
    {
        return has(Flag::D6);
    }

    bool  Meta::is_abstract() const 
    { 
        return has(Flag::ABSTRACT); 
    }

    bool  Meta::is_argument() const
    {
        return has(Flag::ARG);
    }

    bool  Meta::is_asset() const
    {
        return has(Flag::ASSET);
    }
    
    bool Meta::is_association() const
    {
        return has(Flag::ASSOCIATION);
    }
    
    bool  Meta::is_cache() const
    {
        return has(Flag::CACHE);
    }

    bool  Meta::is_camera() const
    {
        return has(Flag::CAMERA) && !has(Flag::EVENT);
    }
    
    bool  Meta::is_camera_command() const
    {
        return has(Flag::CAMERA) && has(Flag::EVENT) && has(Flag::COMMAND);
    }

    bool  Meta::is_camera_event() const
    {
        return has(Flag::CAMERA) && has(Flag::EVENT) && !has(Flag::COMMAND);
    }

    bool  Meta::is_collection() const
    {
        return has(Flag::COLLECTION);
    }

    bool  Meta::is_command() const
    {
        return has(Flag::COMMAND);
    }

    bool  Meta::is_compound() const
    {
        return has(Flag::COMPOUND);
    }

    bool  Meta::is_const() const 
    { 
        return has(Flag::CONST); 
    }
    
    bool  Meta::is_constraint() const
    {
        return has(Flag::CONSTRAINT);
    }

    bool  Meta::is_cursor() const
    {
        return has(Flag::CURSOR);
    }

    bool  Meta::is_editor() const
    {
        return has(Flag::EDITOR);
    }

    bool  Meta::is_event() const
    {
        return has(Flag::EVENT);
    }

    bool  Meta::is_execute() const
    {
        return has(Flag::EXECUTE);
    }

    bool  Meta::is_expansion_disabled() const
    {
        return has(Flag::NO_EXPAND);
    }

    bool  Meta::is_global() const
    {
        return has(Flag::GLOBAL);
    }

    bool  Meta::is_image() const
    {
        return has(Flag::IMAGE);
    }

    bool  Meta::is_imgui() const
    {
        return has(Flag::IMGUI);
    }

    bool  Meta::is_input() const 
    { 
        return has(Flag::INPUT) && !has(Flag::EVENT); 
    }

    bool  Meta::is_input_event() const 
    { 
        return has(Flag::INPUT) && has(Flag::EVENT); 
    }

    bool  Meta::is_loader() const
    {
        return has(Flag::LOADER);
    }

    bool  Meta::is_login_required() const
    {
        return has(Flag::LOGIN_REQ);
    }

    bool  Meta::is_manipulator() const
    {
        return has(Flag::MANIPULATOR);
    }

    bool  Meta::is_method() const
    {
        return has(Flag::METHOD);
    }

    bool  Meta::is_node() const
    {
        return has(Flag::NODE);
    }

    bool  Meta::is_object() const 
    { 
        return has(Flag::OBJECT); 
    }

    bool  Meta::is_operator() const
    {
        return has(Flag::OPERATOR);
    }

    bool  Meta::is_output() const 
    { 
        return has(Flag::OUTPUT); 
    }

    bool  Meta::is_pin() const
    {
        return has(Flag::PIN);
    }

    bool  Meta::is_pipeline() const
    {
        return has(Flag::PIPELINE);
    }

    bool  Meta::is_pixmap() const
    {
        return has(Flag::PIXMAP);
    }

    bool  Meta::is_property() const
    {
        return has(Flag::PROPERTY);
    }

    bool  Meta::is_render3d() const
    {
        return has(Flag::RENDER3D);
    }

    bool  Meta::is_rendered() const
    {
        return has(Flag::RENDERED);
    }

    bool  Meta::is_sampler() const
    {
        return has(Flag::SAMPLER);
    }

    bool  Meta::is_sealed() const
    {
        return has(Flag::SEALED);
    }

    bool  Meta::is_shader() const
    {
        return has(Flag::SHADER);
    }

    bool  Meta::is_small() const
    { 
        return has(Flag::SMALL); 
    }

    bool  Meta::is_state() const
    {
        return has(Flag::STATE);
    }

    bool  Meta::is_static() const 
    { 
        return has(Flag::STATIC); 
    }

    bool  Meta::is_template() const
    {
        return has(Flag::TEMPLATE);
    }

    bool  Meta::is_texture() const
    {
        return has(Flag::TEXTURE);
    }
    
    bool  Meta::is_todo() const 
    { 
        return has(Flag::TODO);
    }

    bool  Meta::is_tool() const
    {
        return has(Flag::TOOL);
    }
    
    bool  Meta::is_type() const 
    { 
        return has(Flag::TYPE); 
    }

    bool  Meta::is_vulkan() const
    {
        return has(Flag::VULKAN);
    }

    bool  Meta::is_widget() const
    {
        return has(Flag::WIDGET) && !has(Flag::EVENT);
    }
    
    bool  Meta::is_widget_event() const
    {
        return has(Flag::WIDGET) && has(Flag::EVENT);
    }

    bool  Meta::is_xfg() const
    {
        return has(Flag::XFG);
    }

    void  Meta::set(Flag f)
    {
            //  If this flunks, it means the flags hasn't been enlarged.
            //  Thus, go to Meta.h and bump the number (by at least one)
        assert((size_t) f < m_flags.size() && "Expand the second number on meta flags"); 
        m_flags.set((size_t) f);
    }
    
    void    Meta::set(std::initializer_list<Flag> flags)
    {
        for(Flag f : flags)
            set(f);
    }

    void  Meta::set_name(std::string_view v) 
    { 
        //  strip out the yq namespace
        if(starts(v, "yq::"))
            m_name  = v.substr(4);
        else
            m_name = v;
        m_name32    = to_u32string(m_name);
        auto ecolon = m_name.find_last_of(':');
        if(ecolon != std::string_view::npos){
            m_stem  = m_name.substr(ecolon+1);
        } else
            m_stem  = m_name;
            
        ecolon      = m_name32.find_last_of(':');
        if(ecolon != std::string_view::npos){
            m_stem32  = m_name32.substr(ecolon+1);
        } else
            m_stem32  = m_name32;
    }


    void  Meta::sweep()
    {
        assert(thread_safe_write());

        if(!has(Flag::SWEPT)){
            sweep_impl();
            set(Flag::SWEPT);
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

