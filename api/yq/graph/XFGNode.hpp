////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>

namespace yq::xfg {

    class XFGPinInfo;

    class XFGNodeInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;
        XFGNodeInfo(std::string_view, ObjectInfo&, const std::source_location& sl = std::source_location::current());
        
        const LUC<XFGPinInfo>&  inputs(bool all=false) const;
        const LUC<XFGPinInfo>&  outputs(bool all=false) const;
    
    protected:
        //! Sweeps on the type (ie gathers properties/methdos)
        virtual void    sweep_impl() override;
    private:
        struct D {
            LUC<XFGPinInfo>     m_inputs;
            LUC<XFGPinInfo>     m_outputs;
        };

        //! What's defined on this object
        D               m_local;
        //! What's defiend across all relevant objects
        D               m_all;

        const D& _def(bool all) const;
    };
    

    class XFGPinInfo : public Meta {
    public:
        class Writer;
        XFGPinInfo(std::string_view, XFGNodeInfo&, const std::source_location& sl = std::source_location::current());
        
        bool    is_input() const { return (flags() & INPUT) != 0; }
        bool    is_output() const { return (flags() & OUTPUT) != 0; }
    };
    
    template <typename T> 
    struct ExecPinIn {
        T       data;
    };
    
    template <typename T> 
    struct ExecPinIn {
        T       data;
    };

    class XFGNode : public Object {
        YQ_OBJECT_INFO(XFGNodeInfo)
        YQ_OBJECT_DECLARE(XFGNode, Object)
    public:
    
        struct Execute {
            bool    triggered       = false;
            constexpr Execute() noexcept = default;
            constexpr Execute(bool f) noexcept : triggered(f) {}
            constexpr auto operator<=>(const Execute&) const noexcept = default;
        };
    
        /*! \brief An "INPUT" DATA pin
        */
        template <typename> struct In {
            T                   data;
        };

        /*! \brief Multiple "INPUT" pins (1...n)
        
            \note This number will be *FIXED* at instantiation
        */
        template <typename T>
        struct VecIn {
            std::vector<T>      data;
        };
    

        /*! \brief An "OUTPUT" data/execute pins
        */
        template <typename T>
        struct Out {
            XFGNode*    us  = nullptr;
            size_t      idx = 0;
            
            void    publish(const T& data)
            {
                if(us)
                    us -> publish(idx, &data, meta<T>());
            }
        };

        template <typename> struct VecOut;
        
        template <typename, size_t> struct ArrIn;
        template <typename, size_t> struct ArrOut;

        struct Pin {
            void*           data    = nullptr;
            const TypeMeta* type    = nullptr;
        };

        std::vector<Pin>            make_inputs();
        void                        subscribe(size_t, const Pin&);
        
        virtual void                execute() = 0;
        
    protected:
        XFGNode();
        virtual ~XFGNode();
        
        //! Default execute in... used if you don't define any
        In<Execute>         m_execIn;
        
        //! Default execute out... used if you don't define any
        Out<Execute>        m_execOut;
        
    
    private:
        std::multimap<size_t, Pin>      m_outputs;
        void        publish(size_t, const void*, const TypeMeta&);
    };

    /*! \brief Multiple "INPUT" pins (1...n)
    
        \note This number will be *FIXED* at instantiation
    */
    
    /*! \brief Multiple "INPUT" pins (1...n)
    
        \note This number is fixed by the template parameter
    */
    template <typename T, size_t N>
    struct XFGNode::ArrIn {
        std::array<T,N>     data;
    };

    /*! \brief Multiple "OUTPUT" pins (1...n)
    
        \note This number will be *FIXED* at instantiation
    */
    template <typename T>
    struct XFGNode::VecOut {
        XFGNode*    us      = nullptr;
        size_t      base    = 0;
        size_t      count   = 0;

        //! Push data 0...(n-1)
        void    push(size_t i, const T& data)
        {
            if(us && (i<count))
                us -> publish(base+i, &data, meta<T>());
        }
    };
    
    template <typename T, size_t N>
    struct XFGNode::ArrOut {
        XFGNode*    us      = nullptr;
        size_t      base    = 0;
    
        //! Push data 0...(N-1)
        void    push(size_t i, const T& data)
        {
            if(us && (i<N))
                us -> publish(base+i, &data, meta<T>());
        }
    };

}
