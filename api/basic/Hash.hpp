////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQUILL__API__CORE__TYPE__HASH__H__

#include <basic/preamble.hpp>
#include <unordered_map>

namespace yq {


    /*! \brief Unordered map (aka hash)
    */
    template <typename K, typename V>
    class Hash : public std::unordered_map<K, V> {
    public:
        typedef std::unordered_map<K,V>  base_hash;

                    Hash(){}
                    Hash(const base_hash& );
                    Hash(base_hash&&);
                    
                    template <typename C>
                    Hash(const Map<K,V,C>&);
                    
                    template <typename Iterator>
                    Hash(Iterator, Iterator);
                    
                    ~Hash(){}
                    
        Hash&       operator=(const base_hash& toCopy);
        Hash&       operator=(base_hash&& toMove);

        //  I know, I know, a hash isn't a map, but they're similar enough that 
        //  the names ought to match.  Unfortunately, VS2013 has issues with
        //  naming them "emplace" or "insert".....
        
        Hash&       emplace_map(const std::unordered_map<K,V>&);
        Hash&       insert_map(const std::unordered_map<K,V>&);
        Hash&       merge_map(const std::unordered_map<K,V>&, bool overwrite=true);

        bool        has(const K& key) const;
        V           get(const K& key, const V& def={}) const;
        Vector<K>   keys() const;
        Vector<V>   values() const;

        const V*    get_ptr(const K&) const;

    };

    //template <typename K, typename V>
    //Hash<K,V>       makeHash(const List<std::pair<K,V>>&);

    //template <typename K, typename V>
    //Hash<K,V>       makeHash(const Vector<std::pair<K,V>>&);

    //template <typename K, typename V, typename C>
    //Hash<K,V>       makeHash(const std::map<K,V,C>&);

    template <typename K, typename V>
    Hash<K,V>       makeHash(const std::unordered_map<K,V>&);



    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //

    template <typename K, typename V>
    Hash<K,V>::Hash(const std::unordered_map<K,V>& cp) : 
        base_hash(cp) 
    {
    }

    template <typename K, typename V>
    Hash<K,V>::Hash(std::unordered_map<K,V> && mv) : 
        base_hash(std::move(mv)) 
    {
    }


    template <typename K, typename V>
    Hash<K,V>&   Hash<K,V>::operator=(const std::unordered_map<K,V>& cp) 
    {
        base_hash::operator=(cp);
        return *this;
    }

    template <typename K, typename V>
    Hash<K,V>&   Hash<K,V>::operator=(std::unordered_map<K,V>&& mv)
    {
        base_hash::operator=(std::move(mv));
        return *this;
    }

    template <typename K, typename V>
    Hash<K,V>&      Hash<K,V>::emplace_map(const std::unordered_map<K,V> &rhs)
    {
        for(auto& i : rhs)
            base_hash::emplace(i);
        return *this;
    }

    template <typename K, typename V>
    V       Hash<K,V>::get(const K& key, const V& def) const
    {
        auto itr = base_hash::find(key);
        if(itr != base_hash::end()){
            return itr->second;
        }
        return def;
    }

    template <typename K, typename V>
    const V*      Hash<K,V>::get_ptr(const K& key) const
    {
        auto itr = base_hash::find(key);
        if(itr != base_hash::end()){
            return &itr->second;
        }
        return nullptr;
    }

    template <typename K, typename V>
    bool       Hash<K,V>:: has(const K& key) const
    {
        return base_hash::contains(key);
    }


    template <typename K, typename V>
    Hash<K,V>&      Hash<K,V>::insert_map(const std::unordered_map<K,V>&rhs)
    {
        for(auto& i : rhs)
            base_hash::insert(i);
        return *this;
    }

    template <typename K, typename V>
    Hash<K,V>&      Hash<K,V>::merge_map(const std::unordered_map<K,V>&rhs, 
                        bool overwrite)
    {
        if(overwrite)
            return insert_map(rhs);
        else
            return emplace_map(rhs);
    }

    template <typename K, typename V>
    Hash<K,V>       makeHash(const std::unordered_map<K,V>&src)
    {
        return Hash<K,V>(src.begin(), src.end());
    }

    template <typename K, typename V>
    Hash<K,V>       makeHash(const Hash<K,V>&src)
    {
        return src;
    }

}

#ifdef YQUILL__API__CORE__TYPE__LIST__H__
    #include "HashListImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__MAP__H__
    #include "HashMapImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__VECTOR__H__
    #include "HashVectorImpl.hxx"
#endif
