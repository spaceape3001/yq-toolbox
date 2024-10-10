////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>

namespace yq {

    /*! \brief Http operations
    
        This represets the http operations that can be legitimately passed via text
    */
    YQ_ENUM(HttpOp, ,
    
        //! Unknown/undefined operations
        Unknown = 0,
        
        //! Error (Not real, here for pages)
        Error,
        
        //! "Get" operation which is the most common
        Get,
        
        //! Equivalent to get but without data
        Head,
        
        //! Post data (ie, changing) to the server
        Post,
        
        //! Creates a new element
        Put,
        
        //! Deletes soemthing
        Delete,
        
        //! Trace HTTP
        Trace,
        
        //! Options list HTTP operation
        Options,
        
        //! Connect HTTP operation
        Connect,
        
        //! Patch HTTP operation
        Patch
    )


    //! HTTP Connect operation
    static constexpr const HttpOp::enum_t hConnect                  = HttpOp::Connect;
    
    //! HTTP Delete operation
    static constexpr const HttpOp::enum_t hDelete                   = HttpOp::Delete;
    
    //! HTTP Get operation
    static constexpr const HttpOp::enum_t hGet                      = HttpOp::Get;
    
    //! HTTP Head operation
    static constexpr const HttpOp::enum_t hHead                     = HttpOp::Head;
    
    //! HTTP Options operation
    static constexpr const HttpOp::enum_t hOptions                  = HttpOp::Options;
    
    //! HTTP Patch operation
    static constexpr const HttpOp::enum_t hPatch                    = HttpOp::Patch;
    
    //! HTTP Post operation
    static constexpr const HttpOp::enum_t hPost                     = HttpOp::Post;
    
    //! HTTP Put operation
    static constexpr const HttpOp::enum_t hPut                      = HttpOp::Put;
    
    //! HTTP Trace operation
    static constexpr const HttpOp::enum_t hTrace                    = HttpOp::Trace;

}
