////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/Logging.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/meta/MetaRepo.hpp>
#include <yq/meta/UntypeMeta.hpp>
#include <yq/container/initlist_utils.hpp>
#include <cassert>

namespace yq {

    const std::vector<const UntypeMeta*>&   UntypeMeta::all()
    {
        assert(thread_safe_read());
        return repo().untypes.all;
    }
    
    const UntypeMeta*                  UntypeMeta::find(id_t i)
    {
        assert(thread_safe_read());
        const Meta* m   = repo().all.value(i, nullptr);
        return (m && m->is_untype()) ? static_cast<const UntypeMeta*>(m) : nullptr;
    }
    
    const UntypeMeta*                  UntypeMeta::find(std::string_view sv)
    {
        assert(thread_safe_read());
        return repo().untypes.lut.first(sv, nullptr);
    }

    const UntypeMeta*                  UntypeMeta::find(stem_k, std::string_view sv)
    {
        assert(thread_safe_read());
        return repo().untypes.stem.first(sv, nullptr);
    }

    std::vector<const UntypeMeta*>          UntypeMeta::find_all(const string_set_t& untypes, bool noisy)
    {
        std::vector<const UntypeMeta*> ret;
        auto&   r   = repo().untypes.lut;
        for(const std::string& s : untypes){
            if(s.empty())
                continue;
                
            const UntypeMeta* ti  = r.first(s);
            if(!ti){
                if(noisy)
                    yWarning() << "Unable to find untype info for: " << s;
                continue;
            }
            ret.push_back(ti);
        }
        return ret;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    UntypeMeta::UntypeMeta(std::string_view zName, const std::source_location& sl) : 
        Meta(zName, sl)
    {
        set(Flag::UNTYPE);
        
        Repo&   r  = repo();
        assert("no duplicate typenames!" && !r.untypes.lut.has(name())); 
        
        r.untypes << this;
    }

    UntypeMeta::~UntypeMeta()
    {
        //  should never be used....
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    /*! \brief Converts meta to type, if it's valid
    
        \return UntypeMeta pointer, if valid, NULL otherwise
    */
    const UntypeMeta* to_untype(const Meta* m)
    {
        return (m && m->is_untype()) ? static_cast<const UntypeMeta*>(m) : nullptr;
    }
    
    const UntypeMeta* to_untype(const Meta& m)
    {
        return m.is_untype() ? static_cast<const UntypeMeta*>(&m) : nullptr;
    }

    /*! \brief Converts meta to type, if it's valid
    
        \return UntypeMeta pointer, if valid, NULL otherwise
    */
    UntypeMeta* to_untype(Meta* m)
    {
        return (m && m->is_untype()) ? static_cast<UntypeMeta*>(m) : nullptr;
    }

    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& str, std::span<const UntypeMeta*> untypes)
    {
        bool    f = true;
        str << "{";
        for(const UntypeMeta* ti : untypes){
            if(f){
                f   = false;
            } else {
                str << ", ";
            }
            str << ti->name();
        }
        str << "}";
        return str;
    }
}

