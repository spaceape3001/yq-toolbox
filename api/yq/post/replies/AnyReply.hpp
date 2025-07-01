////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Any.hpp>
#include <yq/post/Reply.hpp>

namespace yq::post {

    /*! \brief Test post, carries an any value
    */
    class AnyReply : public Reply {
        YQ_OBJECT_DECLARE(AnyReply, Reply)
    public:
    
        using Reply::Param;
        
        AnyReply(const RequestCPtr&, const Any& val, const Param&p={});
        AnyReply(const RequestCPtr&, Any&& val, const Param&p={});
        ~AnyReply();
    
        const Any&    value() const { return m_value; }
    
        static void init_meta();
    
    private:
        Any     m_value;
    };
}
