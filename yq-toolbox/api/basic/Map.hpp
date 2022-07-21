////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__MAP__H__

#include <basic/preamble.hpp>
#include <basic/Result.hpp>
#include <map>

namespace yq {

    /*! \brief Map<K,V,C>:: Container
    */
    template <typename K, typename V, typename C>
    class Map : public std::map<K,V,C> {
    public:

        typedef std::map<K,V,C>  base_map;
        
                    Map(){}
                    Map(C c) : base_map(c) {}
                    Map(const base_map&);
                    Map(base_map&&);
                    
                    template <class Iterator>
                    Map(Iterator, Iterator);
                    
                    ~Map(){}

        Map&        operator=(const base_map& toCopy);
        Map&        operator=(base_map&&);
        
        Map&        operator|=(const base_map&);
        
        Result<V>   operator()(const K&) const;
        
        bool        add(const K& key, const V&);
        
        Map&        emplace_map(const std::map<K,V,C>&);
        K           first_key(const K& def={}) const;
        V           get(const K& key, const V& def={}) const;
        const V*    get_ptr(const K&) const;
        Result<V>   get_r(const K& key) const;
        bool        has(const K& key) const;
        
        using base_map::insert;
        bool        insert(const K&, const V&);
        
        
        Map&        insert_map(const std::map<K,V,C>&);
        Vector<K>   keys() const;
        K           last_key(const K& def={}) const;
        Map&        merge_map(const std::map<K,V,C>&, bool overwrite=true);
        
        /*! \brief Replaces the value with the provided, inserting if necessary
        
            \param[in] key      Key
            \param[in] value    Value to insert/prelace
            \param[in] def      Default value for insert
            
            \return Previous value (default in case of insert)
        */
        V           replace(const K& key, const V& value, const V& def={});

        /*! \brief Replaces the value with the provided, inserting if necessary
        
            \param[in] key      Key
            \param[in] value    Value to insert/prelace
            \param[in] def      Default value for insert
            
            \return Previous value (default in case of insert)
        */
        V           replace(const K& key, V&& value, const V& def={});
        
        V           take(const K& key, const V& def={});
        Vector<V>   values() const;
    };

    template <typename K, typename V>
    Map<K,V>       makeMap(const List<std::pair<K,V>>&);

    template <typename K, typename V>
    Map<K,V>       makeMap(const Vector<std::pair<K,V>>&);

    template <typename K, typename V, typename C>
    Map<K,V,C>      makeMap(const std::map<K,V,C>&);

    //template <typename K, typename V>
    //Map<K,V>       makeMap(const std::unordered_map<K,V>&);


    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //



    template <typename K, typename V, typename C>
    Map<K,V,C>::Map(const std::map<K,V,C>& cp) : 
        base_map(cp) 
    {
    }

    template <typename K, typename V, typename C>
    Map<K,V,C>::Map(std::map<K,V,C>&& mv) : 
        base_map(std::move(mv))
    {
    }

    template <typename K, typename V, typename C>
    Map<K,V,C>&   Map<K,V,C>::operator=(const std::map<K,V,C>& cp) 
    {
        base_map::operator=(cp);
        return *this;
    }

    template <typename K, typename V, typename C>
    Map<K,V,C>&   Map<K,V,C>::operator=(std::map<K,V,C>&& mv)
    {
        base_map::operator=(std::move(mv));
        return *this;
    }

    template <typename K, typename V, typename C>
    Result<V>   Map<K,V,C>:: operator()(const K& key) const
    {
        auto itr=base_map::find(key);
        if(itr != base_map::end())
            return { itr->second, true };
        return {{}, false };
    }


    template <typename K, typename V, typename C>
    bool        Map<K,V,C>::add(const K& key, const V& val)
    {
        return base_map::insert(typename base_map::value_type(key, val)).second;
    }

    template <typename K, typename V, typename C>
    Map<K,V,C>&      Map<K,V,C>::emplace_map(const std::map<K,V,C>& rhs)
    {
        for(auto& i : rhs)
            base_map::emplace(i);
        return *this;
    }

    template <typename K, typename V, typename C>
    K       Map<K,V,C>::first_key(const K& def) const
    {
        if(base_map::empty())
            return def;
        return base_map::begin() -> first;
    }


    template <typename K, typename V, typename C>
    V       Map<K,V,C>::get(const K& key, const V& def) const
    {
        auto itr=base_map::find(key);
        if(itr != base_map::end())
            return itr->second;
        return def;
    }


    template <typename K, typename V, typename C>
    const V*      Map<K,V,C>::get_ptr(const K& key) const
    {
        auto itr = base_map::find(key);
        if(itr != base_map::end())
            return &itr->second;
        return nullptr;
    }

    template <typename K, typename V, typename C>
    Result<V>   Map<K,V,C>:: get_r(const K& key) const
    {
        auto itr=base_map::find(key);
        if(itr != base_map::end())
            return { itr->second, true };
        return { {}, false };
    }

    template <typename K, typename V, typename C>
    bool       Map<K,V,C>:: has(const K& key) const
    {
        return base_map::find(key) != base_map::end();
    }

    template <typename K, typename V, typename C>
    bool       Map<K,V,C>::insert(const K&k, const V&v)
    {
        return base_map::insert({ k, v }).second;
    }


    template <typename K, typename V, typename C>
    Map<K,V,C>&      Map<K,V,C>::insert_map(const std::map<K,V,C>& rhs)
    {
        for(auto& i : rhs)
            base_map::insert(i);
        return *this;
    }

    template <typename K, typename V, typename C>
    K               Map<K,V,C>::last_key(const K& def) const
    {
        if(base_map::empty())   
            return *this;
        return base_map::rbegin() -> first;
    }


    template <typename K, typename V, typename C>
    Map<K,V,C>&      Map<K,V,C>::merge_map(const std::map<K,V,C>&rhs, bool overwrite)
    {
        if(overwrite)
            return insert_map(rhs);
        else
            return emplace_map(rhs);
    }

    template <typename K, typename V, typename C>
    V           Map<K,V,C>::replace(const K& key, const V& value, const V& def)
    {
        auto itr = base_map::find(key);
        if(itr != base_map::end()){
            V   t   = itr -> second;
            itr -> second   = value;
            return t;
        } else {
            base_map::insert({key, value});
            return def;
        }
    }

    template <typename K, typename V, typename C>
    V           Map<K,V,C>::replace(const K& key, V&& value, const V& def)
    {
        auto itr = base_map::find(key);
        if(itr != base_map::end()){
            V   t   = itr -> second;
            itr -> second   = std::move(value);
            return t;
        } else {
            base_map::insert({key, std::move(value)});
            return def;
        }
    }

    template <typename K, typename V, typename C>
    V           Map<K,V,C>::take(const K& key, const V& def)
    {
        auto itr = base_map::find(key);
        if(itr != base_map::end()){
            V   t   = itr->second;
            base_map::erase(itr);
            return t;
        }
        return def;
    }
    
    template <typename K, typename V, typename C>
    Map<K,V,C>&        Map<K,V,C>::operator|=(const base_map& rhs)
    {
        merge_map(rhs, false);
        return *this;
    }

    template <typename K, typename V, typename C>
    Map<K,V,C>       makeMap(const std::map<K,V,C>&src)
    {
        return Map<K,V,C>(src.begin(), src.end());
    }

}


#ifdef YQUILL__API__CORE__TYPE__HASH__H__
    #include "HashMapImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__LIST__H__
    #include "MapListImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__VECTOR__H__
    #include "MapVectorImpl.hxx"
#endif
