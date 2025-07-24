////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__MAP__H__

#include <yq/typedef/string.hpp>
#include <yq/container/forward.hpp>
#include <yq/errors.hpp>
#include <map>
#include <vector>
#include <set>
#include <span>

namespace yq {

    /*! \brief Map<K,V,C>:: Container
    */
    template <typename K, typename V, typename C>
    class Map : public std::map<K,V,C> {
    public:

        typedef std::map<K,V,C>  base_map;
        
        using KK = std::conditional_t<has_view_type<K>, view_type_t<K>, K>;
        using VV = std::conditional_t<has_view_type<V>, view_type_t<V>, V>;

        Map()
        {
        }
        
        Map(C c) : base_map(c) 
        {
        }
        
        Map(const base_map& toCopy) : base_map(toCopy)
        {
        }
                    
        Map(base_map&& toMove) : base_map(std::move(toMove))
        {
        }
        
        template <class Iterator>
        Map(Iterator a, Iterator b) : base_map(a,b)
        {
        }
        
        ~Map(){}

        Map&        operator=(const base_map& toCopy)
        {
            base_map::operator=(toCopy);
            return *this;
        }
        
        Map&        operator=(base_map&& toMove)
        {
            base_map::operator=(std::move(toMove));
            return *this;
        }
        
        Map&        operator|=(const base_map&rhs)
        {
            merge_map(rhs, false);
            return *this;
        }
        
        Expect<V>  operator()(const K&key) const
        {
            auto itr=base_map::find(key);
            if(itr == base_map::end())
                return errors::key_not_found();
            return itr->second;
        }
        
        bool        add(const K& key, const V& val)
        {
            return base_map::insert(typename base_map::value_type(key, val)).second;
        }
        
        Map&        emplace_map(const std::map<K,V,C>& rhs)
        {
            for(auto& i : rhs)
                base_map::emplace(i);
            return *this;
        }
        
        K           first_key(const K& def={}) const
        {
            if(base_map::empty())
                return def;
            return base_map::begin() -> first;
        }
        
        V          first(const std::initializer_list<K>& ks, const V& def={}) const
        {
            for(auto& k : ks){
                auto i = base_map::find(k);
                if(i != base_map::end())
                    return i->second;
            }
            return def;
        }
        
        V          first(const std::span<const K>& ks, const V& def={}) const
        {
            for(auto& k : ks){
                auto i = base_map::find(k);
                if(i != base_map::end())
                    return i->second;
            }
            return def;
        }

        template <typename=void>
        requires has_view_type<V>
        VV         first_view(const std::initializer_list<K>& ks, const VV& def={}) const
        {
            for(auto& k : ks){
                auto i = base_map::find(k);
                if(i != base_map::end())
                    return i->second;
            }
            return def;
        }
        
        template <typename=void>
        requires has_view_type<V>
        VV         first_view(const std::span<const K>& ks, const VV& def={}) const
        {
            for(auto& k : ks){
                auto i = base_map::find(k);
                if(i != base_map::end())
                    return i->second;
            }
            return def;
        }

        V          get(const K& key, const V& def={}) const
        {
            auto itr=base_map::find(key);
            if(itr != base_map::end())
                return itr->second;
            return def;
        }
        
        const V*    get_ptr(const K& key) const
        {
            auto itr = base_map::find(key);
            if(itr != base_map::end())
                return &itr->second;
            return nullptr;
        }
        
        Expect<V>   get_r(const K& key) const
        {
            auto itr=base_map::find(key);
            if(itr == base_map::end())
                return errors::key_not_found();
            return itr->second;
        }
        
        template <typename=void>
        requires has_view_type<V>
        VV         get_view(const K& key, const VV& def={}) const
        {
            auto itr=base_map::find(key);
            if(itr != base_map::end())
                return itr->second;
            return def;
        }

        bool        has(const K& key) const
        {
            return base_map::find(key) != base_map::end();
        }
        
        
        using base_map::insert;
        
        bool        insert(const K&k, const V&v)
        {
            return base_map::insert({ k, v }).second;
        }
        
        
        Map&        insert_map(const std::map<K,V,C>& rhs)
        {
            for(auto& i : rhs)
                base_map::insert(i);
            return *this;
        }
        
        std::vector<K>   keys() const
        {
            std::vector<K>  ret;
            ret.reserve(base_map::size());
            for(auto& i : *this){
                ret.push_back(i.first);
            }
            return ret;
        }
        
        std::set<K,C>       key_set() const
        {
            std::set<K,C> ret(base_map::key_comp());
            for(auto& i : *this){
                ret.insert(i.first);
            }
            return ret;
        }

        K           last_key(const K& def={}) const
        {
            if(base_map::empty())   
                return *this;
            return base_map::rbegin() -> first;
        }
        
        Map&        merge_map(const std::map<K,V,C>& rhs, bool overwrite=true)
        {
            if(overwrite)
                return insert_map(rhs);
            else
                return emplace_map(rhs);
        }
        
        /*! \brief Replaces the value with the provided, inserting if necessary
        
            \param[in] key      Key
            \param[in] value    Value to insert/prelace
            \param[in] def      Default value for insert
            
            \return Previous value (default in case of insert)
        */
        V           replace(const K& key, const V& value, const V& def={})
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

        /*! \brief Replaces the value with the provided, inserting if necessary
        
            \param[in] key      Key
            \param[in] value    Value to insert/prelace
            \param[in] def      Default value for insert
            
            \return Previous value (default in case of insert)
        */
        V           replace(const K& key, V&& value, const V& def={})
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
        
        Map&        set(const K& key, const V& val)
        {
            base_map::operator[](key) = val;
            return *this;
        }
        
        Map&        set(const K& key, V&& val)
        {
            base_map::operator[](key) = val;
            return *this;
        }
        
        V           take(const K& key, const V& def={})
        {
            auto itr = base_map::find(key);
            if(itr != base_map::end()){
                V   t   = itr->second;
                base_map::erase(itr);
                return t;
            }
            return def;
        }
        
        std::vector<V>   values() const
        {
            std::vector<V>  ret;
            ret.reserve(base_map::size());
            for(auto& i : *this)
                ret.push_back(i.second);
            return ret;
        }
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
