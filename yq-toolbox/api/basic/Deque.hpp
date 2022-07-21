////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__DEQUE__H__ 1

#include <deque>

namespace yq {

    template <typename T>
    class Deque : public std::deque<T> {
    public:

        using const_iterator    =  typename std::deque<T>::const_iterator;
        using iterator          =  typename std::deque<T>::iterator;

        using base_deq          = std::deque<T>;

        Deque(){}
        Deque(const base_deq&);
        Deque(base_deq&&);
        
        template <class InputIterator>
        Deque(InputIterator, InputIterator);
        ~Deque(){}
        
        Deque& operator=(const base_deq&);
        Deque& operator=(base_deq&&);
        
        Deque&  operator>>(T&);
        Deque&  operator<<(const T&);
        Deque&  operator<<(T&&);
        
        T       pop();
        
    };

    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //

    template <typename T>
    Deque<T>::Deque(const base_deq& cp) : base_deq(cp)
    {
    }

    template <typename T>
    Deque<T>::Deque(base_deq&&mv) : base_deq(std::move(mv))
    {
    }

    template <typename T>
        template <class InputIterator>
    Deque<T>::Deque(InputIterator a, InputIterator b) : base_deq(a,b)
    {
    }

    template <typename T>
    Deque<T>& Deque<T>::operator=(const base_deq& cp)
    {
        base_deq::operator=(cp);
        return *this;
    }

    template <typename T>
    Deque<T>& Deque<T>::operator=(base_deq&&mv)
    {
        base_deq::operator=(std::move(mv));
        return *this;
    }

    template <typename T>
    Deque<T>&  Deque<T>::operator>>(T& v)
    {
        v   = base_deq::front();
        base_deq::pop_front();
        return *this;
    }

    template <typename T>
    Deque<T>&  Deque<T>::operator<<(const T&v)
    {
        base_deq::push_back(v);
        return *this;
    }

    template <typename T>
    Deque<T>&  Deque<T>::operator<<(T&&v)
    {
        base_deq::push_back(std::move(v));
        return *this;
    }

    template <typename T>
    T       Deque<T>::pop()
    {
        T   v   = base_deq::front();
        base_deq::pop_front();
        return v;
    }

}
