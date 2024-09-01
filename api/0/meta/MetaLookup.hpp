////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/Meta.hpp>
#include <yq/container/MultiMap.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/TextUtils32.hpp>

namespace yq {
    template <typename MT>
    struct MetaLookup {
        using MM    = MultiMap<std::string_view, const MT*, IgCase>;
        using MM32  = MultiMap<std::u32string_view, const MT*, IgCase>;
        
        Vector<const MT*>               all;
        MM                              lut;
        MM32                            lut32;
        StringViewSet                   keys;
        U32StringViewSet                keys32;
        std::vector<std::string*>       alts;
        std::vector<std::u32string*>    alts32;
        MM                              stem;
        MM32                            stem32;

        using equal_range_t     = decltype(((const MetaLookup*) nullptr)->lut.equal_range(std::string_view()));
        using equal_range32_t   = decltype(((const MetaLookup*) nullptr)->lut32.equal_range(std::u32string_view()));
        

        MetaLookup(){}
        
        ~MetaLookup()
        {
            clear();
        }
        
        void    clear()
        {
            all.clear();
            lut.clear();
            lut32.clear();
            stem.clear();
            stem32.clear();
            keys.clear();
            keys32.clear();
            for(std::u32string* p : alts32)
                delete p;
            alts32.clear();
            for(std::string*p : alts)
                delete p;
            alts.clear();
        }
        
        //  Disable copy/move
        MetaLookup(const MetaLookup&) = delete;
        MetaLookup(MetaLookup&&) = delete;
        MetaLookup& operator=(const MetaLookup&) = delete;
        MetaLookup& operator=(MetaLookup&&) = delete;

        MetaLookup& operator<<(const MT* p)
        {
            if(p){
                all << p;
                lut.insert(p->name(), p);
                lut32.insert(p->name32(), p);
                stem.insert(p->stem(), p);
                stem32.insert(p->stem32(), p);
                keys << p->name();
                keys32 << p->name32();
            }
            return *this;
        }
        
        MetaLookup&    operator += (const MetaLookup& b)
        {
            all    += b.all;
            lut    += b.lut;
            lut32  += b.lut32;
            keys   += b.keys;
            keys32 += b.keys32;
            stem   += b.stem;
            stem32 += b.stem32;
            return *this;
        }
        
        void    add_mapping(std::string_view k, const MT* d)
        {
            std::u32string* s   = new std::u32string(to_u32string(k));
            alts32.push_back(s);
            lut32.insert(*s, d);
            lut.insert(k,d);
            keys += k;
            keys32 += *s;
        }

        void    add_mapping(std::u32string_view k, const MT* d)
        {
            std::string* s   = new std::string(to_string(k));
            alts.push_back(s);
            lut32.insert(k, d);
            lut.insert(*s,d);
            keys   += *s;
            keys32 += k;
        }
        
        const MT* find(const std::u32string_view k) const
        {
            return lut32.first(k, nullptr);
        }
        
        const MT* find(const std::string_view k) const
        {
            return lut.first(k, nullptr);
        }

        const MT* find_stem(const std::u32string_view k) const
        {
            return stem32.first(k, nullptr);
        }

        const MT* find_stem(const std::string_view k) const
        {
            return stem.first(k, nullptr);
        }
    };

    template <typename MT, typename K, K (MT::*FN)() const>
    struct MetaLookup2 {
        //   CONDITION is still valid, however, we can't use it w/o compiler issues
        //static_assert( std::is_base_of_v<Meta, T>, "T must derive from Meta!");
        using MM    = MultiMap<K, const MT*>;
        Vector<const MT*>           all;
        MM                          lut;
        Set<K>                      keys;
        
        using equal_range_t     = decltype(((const MetaLookup2*) nullptr)->lut.equal_range(K()));

        MetaLookup2& operator<<(const MT* p)
        {
            all << p;
            K   k   = (p->*FN)();
            lut.insert(k, p);
            keys << k;
            return *this;
        }
        
        MetaLookup2&    operator += (const MetaLookup2& b)
        {
            all += b.all;
            lut += b.lut;
            keys += b.keys;
            return *this;
        }
        
        const MT* find(K k) const
        {
            return lut.first(k, nullptr);
        }
    };

}

