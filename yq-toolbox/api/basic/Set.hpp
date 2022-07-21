////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__SET__H__

#include <basic/preamble.hpp>

#include <set>
#include <list>
#include <vector>

namespace yq {


    /*! \brief Set container
    */
    template <typename T,typename C>
    class Set : public std::set<T,C> {
    public:

        typedef std::set<T,C> base_set;
        typedef std::vector<T>  base_vec;
        
        Set(){}
        Set(const base_set&);
        Set(base_set&&);
        template <class InputIterator>
        Set(InputIterator, InputIterator);

        Set&   operator= (const base_set&);
        Set&   operator= (base_set&&);
        
        Set    operator+ (const base_set&) const;
        Set    operator- (const base_set&) const;
        
        Set    operator+ (const T&) const;
        Set    operator- (const T&) const;
        
        Set    operator& (const Set&) const;
        Set    operator| (const Set&) const;
        Set    operator^ (const Set&) const;
        

        Set&   operator+=(T&&);
        Set&   operator+=(const T&);
        Set&   operator+=(const std::list<T>&);
        Set&   operator+=(const std::set<T,C>&);
        Set&   operator+=(const std::vector<T>&);

        Set&   operator-=(const T&);
        Set&   operator-=(const std::list<T>&);
        Set&   operator-=(const std::set<T,C>&);
        Set&   operator-=(const std::vector<T>&);
        
        Set&   operator&=(const Set&);
        Set&   operator|=(const Set&);
        Set&   operator^=(const Set&);
        
        Set&   operator<<(const T&);
        Set&   operator<<(T&&);
        
        // Returns TRUE if this item was inserted, FALSE if it already existed
        bool    add(const T&);
        bool    add(T&&);
        
        bool    has(const T&) const;
        bool    has_any(const Set<T,C>&) const;
    };


    template <typename T>
    Set<T>          makeSet(const List<T>&);
    template <typename T>
    Set<T>          makeSet(const Set<T>&);
    template <typename T>
    Set<T>          makeSet(const Vector<T>&);

    template <typename T>
    Set<T>          makeSet(const std::list<T>&);
    template <typename T>
    Set<T>          makeSet(const std::set<T>&);
    template <typename T>
    Set<T>          makeSet(const std::vector<T>&);


    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //

    template <typename T,typename C>
    Set<T,C>::Set(const base_set& cp) : base_set(cp)
    {
    }

    template <typename T,typename C>
    Set<T,C>::Set(base_set&&mv) : base_set(std::move(mv))
    {
    }

    template <typename T,typename C>
        template <class InputIterator>
    Set<T,C>::Set(InputIterator b, InputIterator e) : base_set(b,e)
    {
    }



    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator= (const base_set&cp)
    {
        base_set::operator=(cp);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator= (base_set&&mv)
    {
        base_set::operator=(mv);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>    Set<T,C>::operator+ (const base_set&rhs) const
    {
        Set ret(*this);
        ret.insert(rhs.begin(), rhs.end());
        return ret;
    }

    template <typename T,typename C>
    Set<T,C>    Set<T,C>::operator- (const base_set&rhs) const
    {
        Set ret(*this);
        for(const T& k : rhs)
            ret.erase(k);
        return ret;
    }

    template <typename T,typename C>
    Set<T,C>    Set<T,C>::operator+ (const T&rhs) const
    {
        Set ret(*this);
        ret.insert(rhs);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>    Set<T,C>::operator- (const T&rhs) const
    {
        Set ret(*this);
        ret.erase(rhs);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>    Set<T,C>::operator& (const Set&rhs) const
    {
        Set ret;
        for(const T& k : *this)
            if(rhs.has(k))
                ret.insert(k);
        return ret;
    }

    template <typename T,typename C>
    Set<T,C>    Set<T,C>::operator| (const Set&rhs) const
    {
        Set ret(*this);
        ret.insert(rhs.begin(), rhs.end());
        return ret;
    }

    template <typename T,typename C>
    Set<T,C>    Set<T,C>::operator^ (const Set&rhs) const
    {
        Set ret;
        for(const T& k : *this)
            if(!rhs.has(k))
                ret.insert(k);
        for(const T& k : rhs)
            if(!has(k))
                ret.insert(k);
        return ret;
    }


    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator+=(T&&rhs)
    {
        base_set::insert(std::move(rhs));
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator+=(const T&rhs)
    {
        base_set::insert(std::move(rhs));
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator+=(const std::list<T>&rhs)
    {
        base_set::insert(rhs.begin(), rhs.end());
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator+=(const std::set<T,C>&rhs)
    {
        base_set::insert(rhs.begin(), rhs.end());
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator+=(const std::vector<T>&rhs)
    {
        base_set::insert(rhs.begin(), rhs.end());
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator-=(const T&rhs)
    {
        base_set::erase(rhs);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator-=(const std::list<T>&rhs)
    {
        for(const T& k : rhs)
            base_set::erase(k);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator-=(const std::set<T,C>&rhs)
    {
        for(const T& k : rhs)
            base_set::erase(k);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator-=(const std::vector<T>&rhs)
    {
        for(const T& k : rhs)
            base_set::erase(k);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator&=(const Set&rhs)
    {
        // FIXME Improve this
        *this       = *this & rhs;
        return *this;
    }


    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator|=(const Set&rhs)
    {
        base_set::insert(rhs.begin(), rhs.end());
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator^=(const Set&rhs)
    {
        // FIXME Improve this
        *this       = *this ^ rhs;
        return *this;
    }


    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator<<(const T&cp)
    {
        base_set::insert(cp);
        return *this;
    }

    template <typename T,typename C>
    Set<T,C>&   Set<T,C>::operator<<(T&&mv)
    {
        base_set::insert(std::move(mv));
        return *this;
    }

    template <typename T,typename C>
    bool    Set<T,C>::add(const T&cp)
    {
        return base_set::insert(cp).second;
    }

    template <typename T,typename C>
    bool    Set<T,C>::add(T&&mv)
    {
        return base_set::insert(std::move(mv)).second;
    }

    template <typename T,typename C>
    bool    Set<T,C>::has(const T&k) const
    {
        return base_set::find(k) != base_set::end();
    }

    template <typename T,typename C>
    bool    Set<T,C>::has_any(const Set<T,C>&keys) const
    {
        for(const T& k : keys)
            if(has(k))
                return true;
        return false;
    }


    template <typename T>
    Set<T>          makeSet(const std::set<T>&src)
    {
        return Set<T>(src.begin(), src.end());
    }

}

#ifdef YQUILL__API__CORE__TYPE__LIST__H__
    #include "ListSetImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__VECTOR__H__
    #include "SetVectorImpl.hxx"
#endif
