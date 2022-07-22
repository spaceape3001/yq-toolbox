////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__VECTOR__H__

#include <basic/preamble.hpp>
#include <algorithm>
#include <vector>
#include <cstring>


namespace yq {

    //template <typename T>
    //std::vector<T>&  operator<<(std::vector<T>& vec, T&& v)
    //{
        //if constexpr ( std::is_rvalue_reference_v<T> ){
            //vec.push_back(std::move(v));
        //} else
            //vec.push_back(v);
        //return vec;
    //}

    /*! \brief Our vector container type

        Just extending the vector container to have some niceties.
        
        \tparam T   Type of the container.
    */
    template <typename T>
    class Vector : public std::vector<T> {
    public:

        typedef typename std::vector<T>::const_iterator const_iterator;
        typedef typename std::vector<T>::iterator iterator;

        typedef std::vector<T> base_vec;
        

        Vector(){}
        Vector(const base_vec& toCopy);
        
        template <class InputIterator>
        Vector(InputIterator, InputIterator);
        
        Vector(const T*, size_t);

        Vector(base_vec&& toMove);
        explicit Vector(size_t n) : std::vector<T>(n) {}
        Vector(size_t n, const T& v) : std::vector<T>(n,v) {}
        
        ~Vector(){}
        
        Vector&    operator=(const base_vec& toCopy);
        Vector&    operator=(base_vec&& toMove);

        Vector&    operator<<(const T& value);
        Vector&    operator<<(T&&);

        //! Merging (ie, will check, this is horrendous for  efficiency)
        Vector&     operator|=(const T& value);
        Vector&     operator|=(const std::vector<T>&);

        Vector&    operator += (const T& value);
        Vector&    operator += (T&&);
        Vector&    operator += (const std::vector<T>&);
        Vector&    operator += (const List<T>&);
        
        Vector      operator + (const Vector<T>&) const;

        Vector&    add(size_t pos, const T&);
        
        /*! \brief Returns all items after the specified index
        */
        Vector     after(size_t) const;
        
        Vector&     append(const T*, size_t);
        
        Vector&     append_if_unique(const T&);
        
        /*! \brief Erases element at specified location
        */
        Vector&    erase_at(size_t pos);

        Vector&     erase_at(size_t pos, size_t cnt);

        /*! \brief Erases from the current vector
        
            This will *DELETE* if the specified argument returns TRUE for the 
            specified item.
        */    
        template <typename Pred>
        Vector&    erase_if(Pred);
        
        Vector&    erase_range(size_t low, size_t high);

        /*! \brief Filters the current vector
        
            This will *KEEP* if the argument returns TRUE for the specified item.
        */
        template <typename Pred>
        Vector&    filter(Pred);

        /*! \brief Creates a new vector from the filter
        
            This does not alter the existing vector, but it will duplicate items
            contained (plan for this, accordingly)
        */
        template <typename Pred>
        Vector     filtered(Pred) const;

        iterator        find(const T&) ;
        const_iterator  find(const T&) const;

        T            first(const T& def={}) const;
        
        //!  Returns the first index, or size() if not found
        size_t      first_index_of(const T&) const;
        
        bool        has(const T&) const;
        
        // pull the STL ones forward
        using       base_vec::insert;
        
        Vector&     insert(size_t before, T&&);
        Vector&     insert(size_t before, const T&);
        
        T           last(const T& def={}) const;

        Vector      mid(size_t pos, size_t length=~0ULL) const;

        Vector&     move(size_t curIdx, size_t newIdx);
        
        T           next(const T&, const T& def={}) const;

        //  Assumes the vector is currently sorted....
        template <typename Pred>
        Vector&     insert_sort(const T&, Pred);
        
        void        prepend(const T&);
        
        T           prev(const T&, const T& def={}) const;

        
        size_t      push(const T&);
        
        Vector&     remove_all(const T&);
        
        using base_vec::resize;

        /*! \brief Resizes the vector if current size is less than necessary
        */
        void        resize_if_under(size_t needed, size_t extra, const T& def={});

        Vector&     set(size_t, const T&);
        
        //  Disable because Visual studio expands *everything* with an argument,
        //  and not everything should have to have a comparison operator in a 
        //  vector!
        //Vector&     sort(); // uses the natural order
        
        template <typename Pred>
        Vector&     sort(Pred);
        
        template <typename Pred>
        Vector&     stable_sort(Pred);

        Vector&     swap(size_t, size_t);
        
        T           take(size_t pos, const T& def={});
        
        Vector&     unique();

        template <typename Pred>
        Vector&     unique_insert_sort(const T&, Pred);

        bool        valid(size_t i) const { return i < base_vec::size(); }

        T           value(size_t, const T& def={}) const;
        
        struct CommaOp { 
            CommaOp(Vector& v) : vec(v) {}
            CommaOp& operator,(const T& t) { vec.push_back(t); return *this; }
            CommaOp& operator,(T&& t) { vec.push_back(std::move(t)); return *this; }
            Vector & vec;
        };
        
        CommaOp     operator=(const T&);
        CommaOp     operator=(T&&);
    };


    template <typename T>
    Vector<const T*> makeConst(const Vector<T*>&);

    template <typename T>
    Vector<const T*> makeConstVector(const List<T*>&);


    template <typename T>
    Vector<T>       makeVector(const List<T>&);

    //template <typename K, typename V, typename C>
    //Vector<std::pair<K,V>>  makeVector(const std::map<K,V,C>&);

    //template <typename T>
    //Vector<T>       makeVector(const std::set<T>&);

    //template <typename K, typename V>
    //Vector<std::pair<K,V>>  makeVector(const std::unordered_map<K,V>&);

    template <typename T>
    Vector<T>       makeVector(const std::vector<T>&);




    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //

    template <typename T>
    Vector<T>::Vector(const base_vec& cp) : 
        base_vec(cp) 
    {
    }

    template <typename T>
    Vector<T>::Vector(base_vec&& mv) : 
        base_vec(std::move(mv)) 
    {
    }

    template <typename T>
        template <class InputIterator>
    Vector<T>::Vector(InputIterator a, InputIterator b) :
        base_vec(a, b)
    {
    }

    template <typename T>
    Vector<T>::Vector(const T* p, size_t sz) : Vector(p, p+sz)
    {
    }

    template <typename T>
    Vector<T>&    Vector<T>::operator=(const base_vec& cp) 
    {
        base_vec::operator=(cp);
        return *this;
    }

    template <typename T>
    Vector<T>&    Vector<T>::operator=(base_vec&& mv) 
    {
        base_vec::operator=(std::move(mv));
        return *this;
    }


    template <typename T>
    Vector<T>&    Vector<T>::operator<<(const T& value)
    {
        Vector<T>::push_back(value);
        return *this;
    }


    template <typename T>
    Vector<T>&    Vector<T>::operator<<(T&& value)
    {
        Vector<T>::push_back(std::move(value));
        return *this;
    }

    template <typename T>
    Vector<T>&    Vector<T>::operator|=(const T& value)
    {
        for(const T& t : *this)
            if(t == value)
                return *this;
        Vector<T>::push_back(value);
        return *this;
    }

    template <typename T>
    Vector<T>&    Vector<T>::operator|=(const std::vector<T>& vals)
    {
        for(const T& t : vals)
            operator|=(t);
        return *this;
    }

    template <typename T>
    Vector<T>&    Vector<T>::operator+=(const T& value)
    {
        Vector<T>::push_back(value);
        return *this;
    }

    template <typename T>
    Vector<T>&    Vector<T>::operator+=(T&& value)
    {
        Vector<T>::push_back(std::move(value));
        return *this;
    }



    template <typename T>
    Vector<T>&    Vector<T>::operator += (const std::vector<T>&src)
    {
        Vector<T>::insert(Vector<T>::end(), src.begin(), src.end());
        return *this;
    }


    template <typename T>
    Vector<T>    Vector<T>::operator + (const Vector<T>&rhs) const
    {
        Vector<T>   ret = *this;
        ret += rhs;
        return ret;
    }


    template <typename T>
    typename Vector<T>::CommaOp     Vector<T>::operator=(const T&v)
    {
        base_vec::clear();
        base_vec::push_back(v);
        return CommaOp(*this);
    }

    template <typename T>
    typename Vector<T>::CommaOp     Vector<T>::operator=(T&&v)
    {
        base_vec::clear();
        base_vec::push_back(std::move(v));
        return CommaOp(*this);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T>
    Vector<T>&    Vector<T>::add(size_t pos, const T&t)
    {
        if(pos >= base_vec::size()){
            base_vec::push_back(t);
        } else {
            base_vec::insert(Vector<T>::begin() + pos, t);
        }
        return *this;
    }


    template <typename T>
    Vector<T>     Vector<T>::after(size_t n) const
    {
        if(n >= base_vec::size()){
            return Vector<T>();
        } else {
            return Vector<T>(base_vec::begin()+n, base_vec::end());
        }
    }

    template <typename T>
    Vector<T>&     Vector<T>::append(const T*p, size_t sz)
    {
        base_vec::insert(base_vec::end(), p, p+sz);
        return *this;
    }

    template <typename T>
    Vector<T>&     Vector<T>::append_if_unique(const T&val)
    {
        if(!has(val))
            *this << val;
        return *this;
    }



    template <typename T>
    Vector<T>& Vector<T>::erase_at(size_t pos)
    {
        if(pos < base_vec::size())
            base_vec::erase(base_vec::begin() + pos);
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::erase_at(size_t pos, size_t cnt)
    {
        if(cnt && (pos < base_vec::size())){
            if(cnt > base_vec::size() - pos)
                cnt = base_vec::size() - pos;
            base_vec::erase(base_vec::begin()+pos, base_vec::begin()+pos+cnt); 
        }
        return *this;
    }


    template <typename T>
        template <typename Pred>
    Vector<T>& Vector<T>::erase_if(Pred p)
    {
        auto itr = std::remove_if(base_vec::begin(), base_vec::end(), p);
        if(itr != base_vec::end())
            base_vec::resize(itr-base_vec::begin());
        return *this;
    }

    template <typename T>
    Vector<T>&    Vector<T>::erase_range(size_t low, size_t high)
    {
        if(low < high)
            base_vec::erase(base_vec::begin()+low, base_vec::end()+high);
        return *this;
    }



    template <typename T>
        template <typename Pred>
    Vector<T>&    Vector<T>::filter(Pred p)
    {
        auto itr = std::remove_if(base_vec::begin(), base_vec::end(), 
            [&p](const T& m) -> bool
            {
                return !p(m);
            }
        );
        if(itr != base_vec::end())
            base_vec::resize(itr-base_vec::begin());
        return *this;
    }

    template <typename T>
        template <typename Pred>
    Vector<T>     Vector<T>::filtered(Pred p) const
    {
        Vector<T>  ret;
        std::copy_if(base_vec::begin(), base_vec::end(), ret.begin(), p);
        return ret;
    }

    template <typename T>
    typename Vector<T>::iterator        Vector<T>::find(const T& v) 
    {
        return std::find(base_vec::begin(), base_vec::end(), v);
    }

    template <typename T>
    typename Vector<T>::const_iterator  Vector<T>::find(const T&v) const
    {
        return std::find(base_vec::begin(), base_vec::end(), v);
    }

    template <typename T>
    T           Vector<T>::first(const T& def) const
    {
        if(base_vec::empty()) 
            return def;
        else
            return base_vec::front();
    }

    template <typename T>
    size_t      Vector<T>::first_index_of(const T&v) const
    {
        size_t  i=0ULL;
        for(;i < base_vec::size(); ++i)
            if(base_vec::operator[](i) == v)
                return i;
        return base_vec::size();
    }


    template <typename T>
    bool        Vector<T>::has(const T& val) const
    {
        for(auto& i : *this)
            if(i == val)
                return true;
        return false;
    }

    template <typename T>
    Vector<T>&     Vector<T>::insert(size_t before, T&& mv)
    {
        if(before < base_vec::size()){
            base_vec::insert( base_vec::begin() + before, std::move(mv));
        } else {
            base_vec::push_back(std::move(mv));
        }
        return *this;
    }

    template <typename T>
    Vector<T>&     Vector<T>::insert(size_t before, const T& cp)
    {
        if(before < base_vec::size()){
            base_vec::insert( base_vec::begin() + before, cp);
        } else {
            base_vec::push_back(cp);
        }
        return *this;
    }

    template <typename T>
        template <typename Pred>
    Vector<T>&     Vector<T>::insert_sort(const T&val, Pred p)
    {
        if(base_vec::empty()){
            base_vec::push_back(val);
            return *this;
        }
        
        for(auto itr = Vector<T>::begin(); itr != Vector<T>::end(); ++itr){
            if(p(val, *itr)){
                base_vec::insert(itr, val);
                return *this;
            }
        }
        
        base_vec::push_back(val);
        return *this;
    }

    template <typename T>
    T           Vector<T>::last(const T& def) const
    {
        if(base_vec::empty())
            return def;
        else
            return base_vec::back();
    }

    template <typename T>
    Vector<T>     Vector<T>::mid(size_t pos, size_t length) const
    {
        if(pos > base_vec::size()){
            return Vector<T>();
        } else if((length > base_vec::size()) || (pos + length > base_vec::size())){
            return Vector<T>( base_vec::begin() + pos, base_vec::end());
        } else {
            auto      it  = base_vec::begin() + pos;
            return Vector<T>( it, it + length);
        }
    }

    template <typename T>
    Vector<T>&        Vector<T>::move(size_t curIdx, size_t newIdx)
    {
        if(curIdx < newIdx){
            if(newIdx < base_vec::size()){
                T       tmp = base_vec::at(curIdx);
                for(size_t n=curIdx;n<newIdx;++n){
                    base_vec::at(n) = base_vec::at(n+1);
                }
                base_vec::at(newIdx)   = tmp;
            }
        } else if(curIdx > newIdx){
            if(curIdx < base_vec::size()){
                T       tmp = base_vec::at(curIdx);
                for(size_t n=curIdx;n>newIdx;--n){
                    base_vec::at(n) = base_vec::at(n-1);
                }
                base_vec::at(newIdx)   = tmp;
            }
        }
        
        return *this;
    }

    template <typename T>
    T           Vector<T>::next(const T& val, const T& def) const
    {
        if(!base_vec::empty()){
            size_t n    = firstIndexOf(val) + 1;
            if(n < base_vec::size())
                return base_vec::at(n);
        }
        return def;
    }

    template <typename T>
    void        Vector<T>::prepend(const T& val)
    {
        if(base_vec::empty()){
            base_vec::push_back(val);
        } else {
            base_vec::insert(base_vec::begin(), val);
        }
    }

    template <typename T>
    T           Vector<T>::prev(const T& val, const T& def) const
    {
        if(!base_vec::empty()){
            size_t  n   = firstIndexOf(val);
            if(n > 0 && n < base_vec::size()){
                --n;
                return base_vec::at(n);
            }
        }
        return def;
    }

    template <typename T>
    size_t      Vector<T>::push(const T& val)
    {
        size_t  cur = base_vec::size();
        base_vec::push_back(val);
        return cur;
    }

    template <typename T>
    Vector<T>&     Vector<T>::remove_all(const T&val)
    {
        erase_if([val](const T&v) -> bool { return val == v; } );
        return *this;
    }


    template <typename T>
    void        Vector<T>::resize_if_under(size_t needed, size_t extra, const T& def)
    {
        if(base_vec::size() < needed)
            base_vec::resize(needed + extra, def);
    }


    template <typename T>
    Vector<T>&     Vector<T>::set(size_t pos, const T&val)
    {
        if(pos >= base_vec::size())
            base_vec::resize(pos+1);
        base_vec::at(pos)  = val;
        return *this;
    }

    template <typename T>
    T           Vector<T>::take(size_t pos, const T& def)
    {
        if(pos >= base_vec::size())
            return def;
        auto itr = base_vec::begin() + pos;
        T       ret = *itr;
        base_vec::erase(itr);
        return ret;
    }


    //template <typename T>
    //Vector<T>&        Vector<T>::sort()
    //{
    //    std::sort(Vector<T>::begin(), Vector<T>::end());
    //    return *this;
    //}

    template <typename T>
        template <typename Pred>
    Vector<T>& Vector<T>::sort(Pred p)
    {
        std::sort(base_vec::begin(), base_vec::end(), p);
        return *this;
    }

    template <typename T>
        template <typename Pred>
    Vector<T>&     Vector<T>::stable_sort(Pred p)
    {
        std::stable_sort(base_vec::begin(), base_vec::end(), p);
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::swap(size_t a, size_t b)
    {
        assert((a < base_vec::size()) && (b < base_vec::size()));
        if((a != b) && (a<base_vec::size()) && (b < base_vec::size()))
            std::swap( base_vec::operator[](a), base_vec::operator[](b));
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::unique()
    {
        auto itr = std::unique(base_vec::begin(), base_vec::end());
        base_vec::resize(itr-base_vec::begin());
        return *this;
    }

    template <typename T>
        template <typename Pred>
    Vector<T>&     Vector<T>::unique_insert_sort(const T&val, Pred p)
    {
        if(base_vec::empty()){
            base_vec::push_back(val);
            return *this;
        }
        
        for(auto itr = base_vec::begin(); itr != base_vec::end(); ++itr){
            if(p(val, *itr)){
                if(p(*itr,val))    // equal, don't insert
                    return *this;
                    
                base_vec::insert(itr, val);
                return *this;
            }
        }
        
        base_vec::push_back(val);
        return *this;
    }


    template <typename T>
    T           Vector<T>::value(size_t n, const T& def) const
    {
        if(n<base_vec::size())
            return base_vec::operator[](n);
        return def;
    }

    template <typename T>
    Vector<const T*> makeConst(const Vector<T*>&src)
    {
        return Vector<const T*>(src.begin(), src.end());
    }

    template <typename T>
    Vector<T>       makeVector(const std::vector<T>&src)
    {
        return Vector<T>(src.begin(), src.end());
    }

}

#ifdef YQUILL__API__CORE__TYPE__HASH__H__
    #include "HashVectorImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__LIST__H__
    #include "ListVectorImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__MAP__H__
    #include "MapVectorImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__MULTI_MAP__H__
    #include "MultiMapVectorImpl.hxx"
#endif
#ifdef YQUILL__API__CORE__TYPE__SET__H__
    #include "SetVectorImpl.hxx"
#endif

