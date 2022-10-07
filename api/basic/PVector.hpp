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

    /*! \brief Vector type that mimics Python's list
    
        \note This will be eventually replaced, but as a crutch, being added

        Essentially, a python list can handle negative indices, so this vector will too.  

        Just extending the vector container to have some niceties.
        
        \tparam T   Type of the container.
    */
    template <typename T>
    class PVector : public std::vector<T> {
    public:

        typedef typename std::vector<T>::const_iterator const_iterator;
        typedef typename std::vector<T>::iterator iterator;

        typedef std::vector<T> base_vec;
        

        PVector(){}
        PVector(const base_vec& toCopy);
        
        template <class InputIterator>
        PVector(InputIterator, InputIterator);
        
        PVector(const T*, ssize_t);

        PVector(base_vec&& toMove);
        explicit PVector(ssize_t n) : std::vector<T>((size_t) n) {}
        PVector(ssize_t n, const T& v) : std::vector<T>((size_t) n,v) {}
        
        ~PVector(){}
        
        PVector&    operator=(const base_vec& toCopy);
        PVector&    operator=(base_vec&& toMove);

        PVector&    operator<<(const T& value);
        PVector&    operator<<(T&&);

        //! Merging (ie, will check, this is horrendous for  efficiency)
        PVector&     operator|=(const T& value);
        PVector&     operator|=(const std::vector<T>&);

        PVector&    operator += (const T& value);
        PVector&    operator += (T&&);
        PVector&    operator += (const std::vector<T>&);
        PVector&    operator += (const List<T>&);
        
        PVector      operator + (const PVector<T>&) const;
        
        size_t      index(ssize_t n) const
        {
            if(n>=0)
                return (size_t) n;
            return base_vec::size() + n;
        }
        
        const T&    operator[](ssize_t n)  const
        {
            return base_vec::operator[](index(n));
        }

        T&          operator[](ssize_t n) 
        {
            return base_vec::operator[](index(n));
        }

        PVector&    add(ssize_t pos, const T&);
        
        /*! \brief Returns all items after the specified index
        */
        PVector     after(ssize_t) const;
        
        PVector&     append(const T*, size_t);
        
        PVector&     append_if_unique(const T&);
        
        /*! \brief Erases element at specified location
        */
        PVector&    erase_at(ssize_t pos);

        PVector&     erase_at(ssize_t pos, size_t cnt);

        /*! \brief Erases from the current vector
        
            This will *DELETE* if the specified argument returns TRUE for the 
            specified item.
        */    
        template <typename Pred>
        PVector&    erase_if(Pred);
        
        PVector&    erase_range(size_t low, size_t high);
        
        PVector&    fill(const T& v)
        {
            for(T& t : *this)
                t   = v;
            return *this;
        }
        

        /*! \brief Filters the current vector
        
            This will *KEEP* if the argument returns TRUE for the specified item.
        */
        template <typename Pred>
        PVector&    filter(Pred);

        /*! \brief Creates a new vector from the filter
        
            This does not alter the existing vector, but it will duplicate items
            contained (plan for this, accordingly)
        */
        template <typename Pred>
        PVector     filtered(Pred) const;

        iterator        find(const T&) ;
        const_iterator  find(const T&) const;

        T            first(const T& def={}) const;
        
        //!  Returns the first index, or size() if not found
        size_t      first_index_of(const T&) const;
        
        bool        has(const T&) const;
        
        // pull the STL ones forward
        using       base_vec::insert;
        
        PVector&     insert(ssize_t before, T&&);
        PVector&     insert(ssize_t before, const T&);
        
        T           last(const T& def={}) const;

        PVector      mid(ssize_t pos, size_t length=~0ULL) const;

        PVector&     move(ssize_t curIdx, ssize_t newIdx);
        
        T           next(const T&, const T& def={}) const;

        //  Assumes the vector is currently sorted....
        template <typename Pred>
        PVector&     insert_sort(const T&, Pred);
        
        void        prepend(const T&);
        
        T           prev(const T&, const T& def={}) const;

        
        size_t      push(const T&);
        
        PVector&     remove_all(const T&);
        
        using base_vec::resize;

        /*! \brief Resizes the vector if current size is less than necessary
        */
        void        resize_if_under(size_t needed, size_t extra, const T& def={});

        PVector&     set(ssize_t, const T&);
        
        //  Disable because Visual studio expands *everything* with an argument,
        //  and not everything should have to have a comparison operator in a 
        //  vector!
        //PVector&     sort(); // uses the natural order
        
        template <typename Pred>
        PVector&     sort(Pred);
        
        template <typename Pred>
        PVector&     stable_sort(Pred);

        PVector&     swap(ssize_t, ssize_t);
        
        T           take(ssize_t pos, const T& def={});
        
        PVector&     unique();

        template <typename Pred>
        PVector&     unique_insert_sort(const T&, Pred);

        bool        valid(ssize_t i) const { return index(i) < base_vec::size(); }

        T           value(ssize_t, const T& def={}) const;
        
        struct CommaOp { 
            CommaOp(PVector& v) : vec(v) {}
            CommaOp& operator,(const T& t) { vec.push_back(t); return *this; }
            CommaOp& operator,(T&& t) { vec.push_back(std::move(t)); return *this; }
            PVector & vec;
        };
        
        CommaOp     operator=(const T&);
        CommaOp     operator=(T&&);
    };


    template <typename T>
    PVector<const T*> makeConst(const PVector<T*>&);

    template <typename T>
    PVector<const T*> makeConstPVector(const List<T*>&);


    template <typename T>
    PVector<T>       makePVector(const List<T>&);

    //template <typename K, typename V, typename C>
    //PVector<std::pair<K,V>>  makePVector(const std::map<K,V,C>&);

    //template <typename T>
    //PVector<T>       makePVector(const std::set<T>&);

    //template <typename K, typename V>
    //PVector<std::pair<K,V>>  makePVector(const std::unordered_map<K,V>&);

    template <typename T>
    PVector<T>       makePVector(const std::vector<T>&);




    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //

    template <typename T>
    PVector<T>::PVector(const base_vec& cp) : 
        base_vec(cp) 
    {
    }

    template <typename T>
    PVector<T>::PVector(base_vec&& mv) : 
        base_vec(std::move(mv)) 
    {
    }

    template <typename T>
        template <class InputIterator>
    PVector<T>::PVector(InputIterator a, InputIterator b) :
        base_vec(a, b)
    {
    }

    template <typename T>
    PVector<T>::PVector(const T* p, ssize_t sz) : PVector(p, p+sz)
    {
    }

    template <typename T>
    PVector<T>&    PVector<T>::operator=(const base_vec& cp) 
    {
        base_vec::operator=(cp);
        return *this;
    }

    template <typename T>
    PVector<T>&    PVector<T>::operator=(base_vec&& mv) 
    {
        base_vec::operator=(std::move(mv));
        return *this;
    }


    template <typename T>
    PVector<T>&    PVector<T>::operator<<(const T& value)
    {
        PVector<T>::push_back(value);
        return *this;
    }


    template <typename T>
    PVector<T>&    PVector<T>::operator<<(T&& value)
    {
        PVector<T>::push_back(std::move(value));
        return *this;
    }

    template <typename T>
    PVector<T>&    PVector<T>::operator|=(const T& value)
    {
        for(const T& t : *this)
            if(t == value)
                return *this;
        PVector<T>::push_back(value);
        return *this;
    }

    template <typename T>
    PVector<T>&    PVector<T>::operator|=(const std::vector<T>& vals)
    {
        for(const T& t : vals)
            operator|=(t);
        return *this;
    }

    template <typename T>
    PVector<T>&    PVector<T>::operator+=(const T& value)
    {
        PVector<T>::push_back(value);
        return *this;
    }

    template <typename T>
    PVector<T>&    PVector<T>::operator+=(T&& value)
    {
        PVector<T>::push_back(std::move(value));
        return *this;
    }



    template <typename T>
    PVector<T>&    PVector<T>::operator += (const std::vector<T>&src)
    {
        PVector<T>::insert(PVector<T>::end(), src.begin(), src.end());
        return *this;
    }


    template <typename T>
    PVector<T>    PVector<T>::operator + (const PVector<T>&rhs) const
    {
        PVector<T>   ret = *this;
        ret += rhs;
        return ret;
    }


    template <typename T>
    typename PVector<T>::CommaOp     PVector<T>::operator=(const T&v)
    {
        base_vec::clear();
        base_vec::push_back(v);
        return CommaOp(*this);
    }

    template <typename T>
    typename PVector<T>::CommaOp     PVector<T>::operator=(T&&v)
    {
        base_vec::clear();
        base_vec::push_back(std::move(v));
        return CommaOp(*this);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T>
    PVector<T>&    PVector<T>::add(ssize_t pos, const T&t)
    {
        pos = index(pos);
        if(pos >= base_vec::size()){
            base_vec::push_back(t);
        } else {
            base_vec::insert(PVector<T>::begin() + pos, t);
        }
        return *this;
    }


    template <typename T>
    PVector<T>     PVector<T>::after(ssize_t n) const
    {
        n = index(n);
        if(n >= base_vec::size()){
            return PVector<T>();
        } else {
            return PVector<T>(base_vec::begin()+n, base_vec::end());
        }
    }

    template <typename T>
    PVector<T>&     PVector<T>::append(const T*p, size_t sz)
    {
        base_vec::insert(base_vec::end(), p, p+sz);
        return *this;
    }

    template <typename T>
    PVector<T>&     PVector<T>::append_if_unique(const T&val)
    {
        if(!has(val))
            *this << val;
        return *this;
    }



    template <typename T>
    PVector<T>& PVector<T>::erase_at(ssize_t pos)
    {
        pos = index(pos);
        if(pos < base_vec::size())
            base_vec::erase(base_vec::begin() + pos);
        return *this;
    }

    template <typename T>
    PVector<T>& PVector<T>::erase_at(ssize_t pos, size_t cnt)
    {
        pos = index(pos);
        if(cnt && (pos < base_vec::size())){
            if(cnt > base_vec::size() - pos)
                cnt = base_vec::size() - pos;
            base_vec::erase(base_vec::begin()+pos, base_vec::begin()+pos+cnt); 
        }
        return *this;
    }


    template <typename T>
        template <typename Pred>
    PVector<T>& PVector<T>::erase_if(Pred p)
    {
        auto itr = std::remove_if(base_vec::begin(), base_vec::end(), p);
        if(itr != base_vec::end())
            base_vec::resize(itr-base_vec::begin());
        return *this;
    }

    template <typename T>
    PVector<T>&    PVector<T>::erase_range(size_t low, size_t high)
    {
        if(low < high)
            base_vec::erase(base_vec::begin()+low, base_vec::end()+high);
        return *this;
    }



    template <typename T>
        template <typename Pred>
    PVector<T>&    PVector<T>::filter(Pred p)
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
    PVector<T>     PVector<T>::filtered(Pred p) const
    {
        PVector<T>  ret;
        std::copy_if(base_vec::begin(), base_vec::end(), ret.begin(), p);
        return ret;
    }

    template <typename T>
    typename PVector<T>::iterator        PVector<T>::find(const T& v) 
    {
        return std::find(base_vec::begin(), base_vec::end(), v);
    }

    template <typename T>
    typename PVector<T>::const_iterator  PVector<T>::find(const T&v) const
    {
        return std::find(base_vec::begin(), base_vec::end(), v);
    }

    template <typename T>
    T           PVector<T>::first(const T& def) const
    {
        if(base_vec::empty()) 
            return def;
        else
            return base_vec::front();
    }

    template <typename T>
    size_t      PVector<T>::first_index_of(const T&v) const
    {
        size_t  i=0ULL;
        for(;i < base_vec::size(); ++i)
            if(base_vec::operator[](i) == v)
                return i;
        return base_vec::size();
    }


    template <typename T>
    bool        PVector<T>::has(const T& val) const
    {
        for(auto& i : *this)
            if(i == val)
                return true;
        return false;
    }

    template <typename T>
    PVector<T>&     PVector<T>::insert(ssize_t before, T&& mv)
    {
        before  = index(before);
        if(before < base_vec::size()){
            base_vec::insert( base_vec::begin() + before, std::move(mv));
        } else {
            base_vec::push_back(std::move(mv));
        }
        return *this;
    }

    template <typename T>
    PVector<T>&     PVector<T>::insert(ssize_t before, const T& cp)
    {
        before  = index(before);
        if(before < base_vec::size()){
            base_vec::insert( base_vec::begin() + before, cp);
        } else {
            base_vec::push_back(cp);
        }
        return *this;
    }

    template <typename T>
        template <typename Pred>
    PVector<T>&     PVector<T>::insert_sort(const T&val, Pred p)
    {
        if(base_vec::empty()){
            base_vec::push_back(val);
            return *this;
        }
        
        for(auto itr = PVector<T>::begin(); itr != PVector<T>::end(); ++itr){
            if(p(val, *itr)){
                base_vec::insert(itr, val);
                return *this;
            }
        }
        
        base_vec::push_back(val);
        return *this;
    }

    template <typename T>
    T           PVector<T>::last(const T& def) const
    {
        if(base_vec::empty())
            return def;
        else
            return base_vec::back();
    }

    template <typename T>
    PVector<T>     PVector<T>::mid(ssize_t pos, size_t length) const
    {
        pos = index(pos);
        if(pos > base_vec::size()){
            return PVector<T>();
        } else if((length > base_vec::size()) || (pos + length > base_vec::size())){
            return PVector<T>( base_vec::begin() + pos, base_vec::end());
        } else {
            auto      it  = base_vec::begin() + pos;
            return PVector<T>( it, it + length);
        }
    }

    template <typename T>
    PVector<T>&        PVector<T>::move(ssize_t curIdx, ssize_t newIdx)
    {
        curIdx  = index(curIdx);
        newIdx  = index(newIdx);
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
    T           PVector<T>::next(const T& val, const T& def) const
    {
        if(!base_vec::empty()){
            size_t n    = firstIndexOf(val) + 1;
            if(n < base_vec::size())
                return base_vec::at(n);
        }
        return def;
    }

    template <typename T>
    void        PVector<T>::prepend(const T& val)
    {
        if(base_vec::empty()){
            base_vec::push_back(val);
        } else {
            base_vec::insert(base_vec::begin(), val);
        }
    }

    template <typename T>
    T           PVector<T>::prev(const T& val, const T& def) const
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
    size_t      PVector<T>::push(const T& val)
    {
        size_t  cur = base_vec::size();
        base_vec::push_back(val);
        return cur;
    }

    template <typename T>
    PVector<T>&     PVector<T>::remove_all(const T&val)
    {
        erase_if([val](const T&v) -> bool { return val == v; } );
        return *this;
    }


    template <typename T>
    void        PVector<T>::resize_if_under(size_t needed, size_t extra, const T& def)
    {
        if(base_vec::size() < needed)
            base_vec::resize(needed + extra, def);
    }


    template <typename T>
    PVector<T>&     PVector<T>::set(ssize_t pos, const T&val)
    {
        pos = index(pos);
        if(pos >= base_vec::size())
            base_vec::resize(pos+1);
        base_vec::at(pos)  = val;
        return *this;
    }

    template <typename T>
    T           PVector<T>::take(ssize_t pos, const T& def)
    {
        pos = index(pos);
        if(pos >= base_vec::size())
            return def;
        auto itr = base_vec::begin() + pos;
        T       ret = *itr;
        base_vec::erase(itr);
        return ret;
    }


    //template <typename T>
    //PVector<T>&        PVector<T>::sort()
    //{
    //    std::sort(PVector<T>::begin(), PVector<T>::end());
    //    return *this;
    //}

    template <typename T>
        template <typename Pred>
    PVector<T>& PVector<T>::sort(Pred p)
    {
        std::sort(base_vec::begin(), base_vec::end(), p);
        return *this;
    }

    template <typename T>
        template <typename Pred>
    PVector<T>&     PVector<T>::stable_sort(Pred p)
    {
        std::stable_sort(base_vec::begin(), base_vec::end(), p);
        return *this;
    }

    template <typename T>
    PVector<T>& PVector<T>::swap(ssize_t a, ssize_t b)
    {
        a   = index(a); b = index(b);
        assert((a < base_vec::size()) && (b < base_vec::size()));
        if((a != b) && (a<base_vec::size()) && (b < base_vec::size()))
            std::swap( base_vec::operator[](a), base_vec::operator[](b));
        return *this;
    }

    template <typename T>
    PVector<T>& PVector<T>::unique()
    {
        auto itr = std::unique(base_vec::begin(), base_vec::end());
        base_vec::resize(itr-base_vec::begin());
        return *this;
    }

    template <typename T>
        template <typename Pred>
    PVector<T>&     PVector<T>::unique_insert_sort(const T&val, Pred p)
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
    T           PVector<T>::value(ssize_t n, const T& def) const
    {
        n   = index(n);
        if(n<base_vec::size())
            return base_vec::operator[](n);
        return def;
    }


}

