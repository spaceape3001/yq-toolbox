////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Object.hpp>
#include <0/xfg/preamble.hpp>

namespace yq::xfg {

    class ExecNodeInfo : public ObjectInfo {
    public:

        template <typename C> class Writer;
        ExecNodeInfo(std::string_view, const ObjectInfo&, const std::source_location& sl = std::source_location::current());
    };

    class ExecNode : public Object {
        YQ_OBJECT_INFO(ExecNodeInfo)
        YQ_OBJECT_DECLARE(ExecNode, Object)
    public:
    
    
        struct Input;
        struct Output;
    
        struct Trigger;
        struct Command;
    
        auto            pins()         { return std::span<ExecPin* const>(m_pins); }
        auto            pins() const   { return std::span<const ExecPin* const>(m_pins); }
        
        template <typename> struct In;
        template <typename> struct Out;

        template <typename> struct VecIn;
        template <typename> struct VecOut;
        
        template <typename, size_t> struct ArrIn;
        template <typename, size_t> struct ArrOut;

    
        /*! \brief Executes the node
        */
        virtual void    execute() = 0;

    
    protected:
        ExecNode();
        virtual ~ExecNode();
        
        using TX        = std::vector<ExecPin*>;
    
    private:
        friend class ExecDoc;
        std::vector<Output*>    m_pins;
    };
    
    
    ///////////////////////////////////////////////
    //  PIN HELPERS
    

    /*! \brief An "INPUT" DATA pin
    */
    template <typename T>
    struct ExecNode::In {
        T                   data;
    };

    /*! \brief Multiple "INPUT" pins (1...n)
    
        \note This number will be *FIXED* at instantiation
    */
    template <typename T>
    struct ExecNode::VecIn {
        std::vector<T>      data;
    };
    
    /*! \brief Multiple "INPUT" pins (1...n)
    
        \note This number is fixed by the template parameter
    */
    template <typename T, size_t N>
    struct ExecNode::ArrIn {
        std::array<T,N>     data;
    };

    /*! \brief An "OUTPUT" data/execute pins
    */
    template <typename T>
    struct ExecNode::Out {
        TX      tx;
        void    push(const T&);
    };

    /*! \brief Multiple "OUTPUT" pins (1...n)
    
        \note This number will be *FIXED* at instantiation
    */
    template <typename T>
    struct ExecNode::VecOut {
        std::vector<TX>     tx;

        //! Push data 0...(n-1)
        void    push(size_t, const T&);
    };
    
    template <typename T, size_t N>
    struct ExecNode::ArrOut {
        std::array<TX,N>    tx;
    
        //! Push data 0...(N-1)
        void    push(size_t, const T&);
    };

};


