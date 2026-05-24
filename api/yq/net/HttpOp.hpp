////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Http operations
    
        This represets the http operations that can be legitimately passed via text
    */
    enum class HttpOp {
    
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
    };


    //! HTTP Connect operation
    static constexpr const HttpOp hConnect                  = HttpOp::Connect;
    
    //! HTTP Delete operation
    static constexpr const HttpOp hDelete                   = HttpOp::Delete;
    
    //! HTTP Get operation
    static constexpr const HttpOp hGet                      = HttpOp::Get;
    
    //! HTTP Head operation
    static constexpr const HttpOp hHead                     = HttpOp::Head;
    
    //! HTTP Options operation
    static constexpr const HttpOp hOptions                  = HttpOp::Options;
    
    //! HTTP Patch operation
    static constexpr const HttpOp hPatch                    = HttpOp::Patch;
    
    //! HTTP Post operation
    static constexpr const HttpOp hPost                     = HttpOp::Post;
    
    //! HTTP Put operation
    static constexpr const HttpOp hPut                      = HttpOp::Put;
    
    //! HTTP Trace operation
    static constexpr const HttpOp hTrace                    = HttpOp::Trace;

}
