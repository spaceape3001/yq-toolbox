////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#define YQUILL__API__CORE__TYPE__STACK__H__

#include <span>
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
        T&          top();
        const T&    top() const;
        
        /*! \brief Pops the stack until the size is beneath the argument */
        void        pop_to(size_t sz);
        
        //! Pops this many items from the stack
        void        pop_last(size_t);

        //! Peeks n from top, nullptr if not found
        T*          peek(size_t);
        
        //! Peeks n from top, nullptr if not found
        const T*    peek(size_t) const;
        
        std::span<const T>  top_cspan(size_t n) const;
        std::span<T>        top_span(size_t n);
        
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
    T*          Stack<T>::peek(size_t n) 
    {
        if(n > base_stack::size())
            return nullptr;
        return &base_stack::operator[](base_stack::size()-n);
    }

    template <typename T>
    const T*    Stack<T>::peek(size_t n) const
    {
        if(n > base_stack::size())
            return nullptr;
        return &base_stack::operator[](base_stack::size()-n);
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
    void        Stack<T>::pop_last(size_t n)
    {
        if(n > base_stack::size())
            n   = base_stack::size();
        if(n){
            size_t m = base_stack::size() - n;
            base_stack::erase(base_stack::begin()+m, base_stack::end());
        }
    }

    template <typename T>
    void        Stack<T>::pop_to(size_t sz)
    {
        if(sz < base_stack::size())
            base_stack::erase(base_stack::begin()+sz, base_stack::end());
    }


    template <typename T>
    const T&    Stack<T>::top() const
    {
        static const T  s_def{};
        if(base_stack::empty())
            return s_def;
        return base_stack::back();
    }

    template <typename T>
    T&    Stack<T>::top() 
    {
        static thread_local T  s_def{};
        if(base_stack::empty())
            return s_def;
        return base_stack::back();
    }

    template <typename T>
    std::span<const T>  Stack<T>::top_cspan(size_t n) const
    {
        if(base_stack::empty())
            return {};
        if(n > base_stack::size())
            n   = base_stack::size();
        size_t m = base_stack::size() - n;
        return std::span<const T>(base_stack::data()+m, n);
    }

    template <typename T>
    std::span<T>        Stack<T>::top_span(size_t n)
    {
        if(base_stack::empty())
            return {};
        if(n > base_stack::size())
            n   = base_stack::size();
        size_t m = base_stack::size() - n;
        return std::span<T>(base_stack::data()+m, n);
    }
}
