////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Enum.hpp>

namespace yq {

    YQ_ENUM(HttpStatus, ,
        None                        = 0,
        
        Continue                    = 100,
        SwitchingProtocols          = 101,
        Processing                  = 102,
        EarlyHints                  = 103,

        Okay                        = 200,
        Success                     = 200,
        Created                     = 201,
        Accepted                    = 202,
        NonAuthoritative            = 203,
        NoContent                   = 204,
        ResetContent                = 205,
        PartialContent              = 206,
        MultiStatus                 = 207,
        AlreadyReported             = 208,
        ThisIsFine                  = 218,
        IMUsed                      = 226,

        MultipleChoice              = 300,
        MovedPermanently            = 301,
        Found                       = 302,
        SeeOther                    = 303,
        NotModified                 = 304,
        UseProxy                    = 305,
        TemporaryRedirect           = 307,
        PermanentRedirect           = 308,
        
        PostedRedirect              = 399,
        
        BadRequest                  = 400,
        Unauthorized                = 401,
        PaymentRequired             = 402,
        Forbidden                   = 403,
        NotFound                    = 404,
        MethodNotAllowed            = 405,
        NotAcceptable               = 406,
        ProxyAuthenticationReq      = 407,
        RequestTimeout              = 408,
        Conflict                    = 409,
        Gone                        = 410,
        LengthRequired              = 411,
        PreconditionFailed          = 412,
        PayloadTooLarge             = 413,
        UriTooLong                  = 414,
        UnsupportedMedia            = 415,
        BadRange                    = 416,
        ExpectationFailed           = 417,
        Teapot                      = 418,
        PageExpired                 = 419,
        EnhanceYourCalm             = 420,
        MisdirectedRequest          = 421,
        UnprocessableEntity         = 422,
        Locked                      = 423,
        FailedDependency            = 424,
        TooEarly                    = 425,
        UpgradeRequired             = 426,
        PreconditionRequired        = 428,
        TooManyRequests             = 429,
        RequestHeaderTooLarge       = 431,
        LoginTimeout                = 440,
        NoResponse                  = 444,
        RetryWith                   = 449,
        ParentalControl             = 450,
        Censored                    = 451,
        
        BadArgument                 = 495,
        BadHTTPVersion              = 496,
        MissingURI                  = 497,
        BadURI                      = 498,
        ClientClosedRequest         = 499,

        InternalError               = 500,
        NotImplemented              = 501,
        BadGateway                  = 502,
        ServiceUnavailable          = 503,
        GatewayTimeout              = 504,
        HTTPVersionNotSupported     = 505,
        VariantAlsoNegotiates       = 506,
        InsufficientStorage         = 507,
        LoopDetected                = 508,
        BandwidthLimitExceeded      = 509,
        NotExtended                 = 510,
        NetworkAuthenticationReq    = 511,
        InvalidSSLCertificate       = 526,
        
        UnableToPerform             = 596,
        CurlError                   = 597,
        NetworkReadTimeout          = 598,
        NetworkConnectTimeout       = 599
    )

    static constexpr const HttpStatus::enum_t   hNotFound           = HttpStatus::NotFound;
    static constexpr const HttpStatus::enum_t   hBadRequest         = HttpStatus::BadRequest;

    std::string_view    statusMessage(HttpStatus);
    std::string_view    statusMessage(unsigned short);

    bool        isRedirect(HttpStatus);
    bool        isRedirect(unsigned short);

    bool        isError(HttpStatus);
    bool        isError(unsigned short);

    bool        isClientError(HttpStatus);
    bool        isClientError(unsigned short);

    bool        isServerError(HttpStatus);
    bool        isServerError(unsigned short);

    bool        isSuccessful(HttpStatus);
    bool        isSuccessful(unsigned short);

    bool        isInformational(HttpStatus);
    bool        isInformational(unsigned short);

}
