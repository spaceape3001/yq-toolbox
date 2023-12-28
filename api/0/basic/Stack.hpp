////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__STACK__H__

#include <vector>

namespace yq {


    /* \brief Stack container
    */
    template <typename T>
    class Stack : public std::vector<T> {
    public:

        using base_stack =  std::vector<T>;
        
                    Stack(){}
                    Stack(const Stack&);
                    Stack(Stack&&);

        Stack&     operator<<(const T&);
        Stack&     operator<<(T&&);
        Stack&     operator>>(T&);

        T           pop(const T& def={});
        T           top(const T& def={}) const;
        
        /*! \brief Pops the stack until the size is beneath the argument */
        void        pop_to(size_t sz);
        
    };

    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
    //  ====================================================================  //
    //                      IMPLEMENTATION!!!!!                               //
    //  ====================================================================  //
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //



    template <typename T>
    Stack<T>::Stack(const Stack& cp) :
        base_stack(cp)
    {
    }

    template <typename T>
    Stack<T>::Stack(Stack&& mv) :
        base_stack(std::move(mv))
    {
    }

    /*
    #if INFCFG_QT
    template <typename T>
    Stack<T>::Stack(const QStack<T>& cp) :
        base_stack(cp.begin(), cp.end())
    {
    }

    template <typename T>
    QStack<T>   Stack<T>::qStack() const
    {
        QStack<T>   ret;
        for(const T& v : *this){
            ret.push(v);
        }
        return ret;
    }

    template <typename T>
    QList<T>    Stack<T>::qList() const
    {
        return QList<T>::fromStdList(zlist<T>(*this));
    }

    template <typename T>
    QVector<T>  Stack<T>::qVector() const
    {
        return QVector<T>::fromStdVector(Vector<T>(*this));
    }


    template <typename T>
    QSet<T>     Stack<T>::qSet() const
    {
        return QSet<T>::fromStdSet(zset<T>(*this));
    }
    #endif
    */

    template <typename T>
    Stack<T>&     Stack<T>::operator<<(const T&value)
    {
        base_stack::push_back(value);
        return *this;
    }

    template <typename T>
    Stack<T>&     Stack<T>::operator<<(T&&value)
    {
        base_stack::push_back(std::move(value));
        return *this;
    }

    template <typename T>
    Stack<T>&     Stack<T>::operator>>(T& value)
    {
        //  this will allow the assertion to fail
        value   =    base_stack::back();
        base_stack::pop_back();
        return *this;
    }

    template <typename T>
    T           Stack<T>::pop(const T& def)
    {
        if(base_stack::empty()) 
            return def;
        T val   =    base_stack::back();
        base_stack::pop_back();
        return val;
    }

    template <typename T>
    void        Stack<T>::pop_to(size_t sz)
    {
        if(sz < base_stack::size())
            base_stack::erase(base_stack::begin()+sz, base_stack::end());
    }


    template <typename T>
    T           Stack<T>::top(const T&def) const
    {
        if(base_stack::empty())
            return def;
        return base_stack::back();
    }
}
