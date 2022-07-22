////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__MULTI_MAP__H__

#include <basic/preamble.hpp>
#include <map>

namespace yq {

    template <typename K, typename V, typename C>
    class MultiMap : public std::multimap<K,V,C> {
    public:
        typedef std::multimap<K,V,C>   base_map;
        
                    MultiMap(){}
                    MultiMap(C c) : base_map(c) {}
                    MultiMap(const base_map&);
                    MultiMap(base_map&&);
                    ~MultiMap(){}
                    
        MultiMap&  operator=(const base_map&);
        MultiMap&  operator=(base_map&&);
        
        bool        has(const K&) const;
        bool        has(const K&, const V&) const;
        bool        has(std::initializer_list<K>, const V&) const;

        Vector<V>   get(const K&) const;
        Vector<V>   get(std::initializer_list<K>) const;
        Vector<V>   get(const Vector<K>&) const;
        
        V           first(const K&, const V&def={}) const;
        V           first(std::initializer_list<K>, const V&def={}) const;
        V           first(const std::vector<K>&, const V&def={}) const;
        
        void        rekey(const K&from, const K&to);
        
        Vector<K>   keys() const;
        Vector<V>   values() const;
        Vector<K>   unique_keys() const;
        
        using base_map::insert;
        
        void        insert(const K&, const V&);
        void        insert(const K&, V&&);

        MultiMap&   operator+=(const MultiMap&);

        using base_map::erase;
        void        erase(const K&, const V&);
        void        erase(std::initializer_list<K>);
        
    };




    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //


    template <typename K, typename V, typename C>
    MultiMap<K,V,C>::MultiMap(const base_map&cp) : base_map(cp)
    {
    }

    template <typename K, typename V, typename C>
    MultiMap<K,V,C>::MultiMap(base_map&&mv) : base_map(std::move(mv))
    {
    }

    template <typename K, typename V, typename C>
    MultiMap<K,V,C>&  MultiMap<K,V,C>::operator=(const base_map&cp)
    {
        base_map::operator=(cp);
        return *this;
    }


    template <typename K, typename V, typename C>
    MultiMap<K,V,C>&  MultiMap<K,V,C>::operator=(base_map&&mv)
    {
        base_map::operator=(std::move(mv));
        return *this;
    }

    template <typename K, typename V, typename C>
    MultiMap<K,V,C>&   MultiMap<K,V,C>::operator+=(const MultiMap&other)
    {
        base_map::insert(other.begin(), other.end());
        return *this;
    }


    template <typename K, typename V, typename C>
    bool        MultiMap<K,V,C>::has(const K&k) const
    {
        return base_map::find(k) != base_map::end();
    }

    template <typename K, typename V, typename C>
    bool        MultiMap<K,V,C>::has(const K& k, const V& v) const
    {
        auto ltr    = base_map::lower_bound(k);
        auto utr    = base_map::upper_bound(k);
        for(auto itr=ltr; itr != utr; ++itr){
            if(itr -> second == v)
                return true;
        }
        return false;
    }

    template <typename K, typename V, typename C>
    bool        MultiMap<K,V,C>::has(std::initializer_list<K>ks, const V&v) const
    {
        for(const K& k : ks)
            if(has(k, v))
                return true;
        return false;
    }

    template <typename K, typename V, typename C>
    void        MultiMap<K,V,C>::insert(const K&k, const V&v)
    {
        base_map::insert(std::make_pair(k,v));
    }

    template <typename K, typename V, typename C>
    void        MultiMap<K,V,C>::insert(const K&k, V&&v)
    {
        base_map::insert(std::move(std::make_pair(k,std::move(v))));
    }

    template <typename K, typename V, typename C>
    void        MultiMap<K,V,C>::erase(std::initializer_list<K> ks)
    {
        for(const K& k : ks)
            erase(k);
    }

    template <typename K, typename V, typename C>
    void        MultiMap<K,V,C>::erase(const K&k, const V&v)
    {
        auto ltr    = base_map::lower_bound(k);
        auto utr    = base_map::upper_bound(k);
        for(auto itr=ltr;itr!=utr;){
            if(itr->second == v){
                itr = base_map::erase(itr);
            } else
                ++itr;
        }
    }


    template <typename K, typename V, typename C>
    V           MultiMap<K,V,C>::first(const K&k, const V&def) const
    {
        auto itr = base_map::find(k);
        if(itr != base_map::end())
            return itr->second;
        return def;
    }    

    template <typename K, typename V, typename C>
    V           MultiMap<K,V,C>::first(std::initializer_list<K> ks, const V&def) const
    {
        for(K k : ks){
            auto itr = base_map::find(k);
            if(itr != base_map::end())
                return itr->second;
        }
        return def;
    }

}


#ifdef YQUILL__API__CORE__TYPE__VECTOR__H__
    #include "MultiMapVectorImpl.hxx"
#endif
