////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LoggerBox.hpp"

#include <yq/core/StreamOps.hpp>
#include <yq/stream/Logger.hpp>
#include <log4cpp/Category.hh>
#include <log4cpp/CategoryStream.hh>

namespace yq::post {
    LoggerBox::LoggerBox() : LoggerBox(Param()) {}
    LoggerBox::LoggerBox(const Param& cfg) : 
        m_category(log_category(cfg.category)), m_priority(log4cpp_priority(cfg.priority))
    {
        add_role(R::Listener);
        if(cfg.global)
            capture(GLOBAL);
    }
    
    LoggerBox::~LoggerBox()
    {
    }

    void    LoggerBox::receive(const PostCPtr& pp) 
    {
        if(!pp)
            return ;
        
        const auto&     pi  = pp->metaInfo();
        
        stream::Logger  log(m_category.getStream(m_priority));
        log << pi.stem() << "[" << pp->id() << "]";
        bool    f = true;
        
        for(const PropertyInfo* prop : pi.properties(ALL).all){
            // filter out properties
            if(prop->name() == "id")
                continue;

            // Comma!
            if(f){  
                log << " ";
                f = false;
            } else {
                log << "; ";
            }
        
            log << prop->name() << "=\"";
            prop->print(pp.ptr(), log);
            log << "\"";
        }
    }
}
