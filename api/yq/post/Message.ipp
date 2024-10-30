////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Message.hpp"
#include "MessageInfoWriter.hpp"
#include <yq/core/DelayInit.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::Message)

namespace yq::post {
    MessageInfo::MessageInfo(std::string_view zName, PostInfo& base, const std::source_location& sl) :
        PostInfo(zName, base, sl)
    {
        set(Flag::MESSAGE);
    }

    ////////////////////////////////////////////////////////////////////////////

    Message::Message(const Param& p) : Post(p)
    {
    }
    
    Message::~Message()
    {
    }


    ////////////////////////////////////////////////////////////////////////////

    static void reg_message()
    {
        auto w = writer<Message>();
        w.description("Abstract Message Class");
    }
    
    YQ_INVOKE(reg_message();)
}
