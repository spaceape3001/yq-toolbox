////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "HttpStatus.hpp"

#include <basic/DelayInit.hpp>
#include <basic/EnumMap.hpp>

namespace yq {

    bool        isClientError(unsigned short u)
    {
        return (u>=400) && (u<500);
    }

    bool        isClientError(HttpStatus u)
    {
        return isClientError((unsigned short) u.value());
    }

    bool        isError(unsigned short u)
    {
        return (u>=400) && (u<600);
    }

    bool        isError(HttpStatus u)
    {
        return isError((unsigned short) u.value());
    }

    bool        isInformational(unsigned short u)
    {
        return (u>=100) && (u<200);
    }

    bool        isInformational(HttpStatus u)
    {
        return isInformational((unsigned short) u);
    }

    bool        isRedirect(unsigned short u)
    {
        return (u>=300) && (u<400);
    }

    bool        isRedirect(HttpStatus u)
    {
        return isRedirect((unsigned short) u);
    }


    bool        isServerError(unsigned short u)
    {
        return (u>=500) && (u<600);
    }

    bool        isServerError(HttpStatus u)
    {
        return isServerError((unsigned short) u);
    }

    bool        isSuccessful(unsigned short u)
    {
        return (u>=200) && (u<300);
    }

    bool        isSuccessful(HttpStatus u)
    {
        return isSuccessful((unsigned short) u);
    }


    namespace {
    
        //std::string makeMessage(const char* cat, unsigned short value)
        //{
            //char        buffer[256];
            //sprintf(buffer, "%s %d", cat, (int) value);
            //return std::string(buffer);
        //}
        
        using HttpStatusMap	= EnumMap<HttpStatus,std::string_view>;
        
        HttpStatusMap 	makeStatusMessage()
        {
            static const struct {
                HttpStatus::enum_t  code;
                std::string_view    message;
            } kCodes[] = {
                { HttpStatus::None,                     	"Invalid"                           },

                //  100 Codes (information)
                { HttpStatus::Continue,                     "Continue"                          },
                { HttpStatus::SwitchingProtocols,           "Switching Protcols"                },
                { HttpStatus::Processing,                   "Processing...."                    },
                { HttpStatus::EarlyHints,                   "Psst, Early Hints."                },
                
                //  200 codes (success)
                { HttpStatus::Okay,                         "OK"                                },
                { HttpStatus::Created,                      "Created"                           },
                { HttpStatus::Accepted,                     "Accepted"                          },
                { HttpStatus::NonAuthoritative,             "Non-Authroitative Information"     },
                { HttpStatus::NoContent,                    "No content"                        },
                { HttpStatus::ResetContent,                 "Reset Content"                     },
                { HttpStatus::PartialContent,               "Partial Content"                   },
                { HttpStatus::MultiStatus,                  "Multi Status"                      },
                { HttpStatus::AlreadyReported,              "Already Reported"                  },
                { HttpStatus::ThisIsFine,                   "This is fine."                     },
                { HttpStatus::IMUsed,                       "IM Used"                           },

                //  300 codes
                { HttpStatus::MultipleChoice,               "Multiple Choice Redirect"          },
                { HttpStatus::MovedPermanently,             "Moved Permanently"                 },
                { HttpStatus::Found,                        "Found"                             },
                { HttpStatus::SeeOther,                     "See Other"                         },
                { HttpStatus::NotModified,                  "Not Modified"                      },
                { HttpStatus::UseProxy,                     "Use Proxy"                         },
                { HttpStatus::TemporaryRedirect,            "Temporary Redirect"                },
                { HttpStatus::PermanentRedirect,            "Permanent Redirect"                },
                { HttpStatus::PostedRedirect,               "Redirecting After Post"            },
            
                { HttpStatus::BadRequest,                   "Bad Request"                       },
                { HttpStatus::Unauthorized,                 "Unauthorized"                      },
                { HttpStatus::PaymentRequired,              "Payment Required"                  },
                { HttpStatus::Forbidden,                    "Forbidden"                         },
                { HttpStatus::NotFound,                     "Not Found"                         },
                { HttpStatus::MethodNotAllowed,             "Method Not Allowed"                },
                { HttpStatus::NotAcceptable,                "Not Acceptable"                    },
                { HttpStatus::ProxyAuthenticationReq,       "Proxy Authentication Required"     },
                { HttpStatus::RequestTimeout,               "RequestTimeout"                    },
                { HttpStatus::Conflict,                     "Conflict"                          },
                { HttpStatus::Gone,                         "Gone"                              },
                { HttpStatus::LengthRequired,               "Length Required"                   },
                { HttpStatus::PreconditionFailed,           "Precondition Failed"               },
                { HttpStatus::PayloadTooLarge,              "Payload Too Large"                 },
                { HttpStatus::UriTooLong,                   "Uri Too Long"                      },
                { HttpStatus::UnsupportedMedia,             "Unsupported Media"                 },
                { HttpStatus::BadRange,                     "Bad Range"                         },
                { HttpStatus::ExpectationFailed,            "Expectation Failed"                },
                { HttpStatus::Teapot,                       "I'm a Teapot"                      },
                { HttpStatus::PageExpired,                  "Page Expired"                      },
                { HttpStatus::EnhanceYourCalm,              "Enhance Your Calm"                 },
                { HttpStatus::MisdirectedRequest,           "Misdirected Request"               },
                { HttpStatus::UnprocessableEntity,          "Unprocessable Entity"              },
                { HttpStatus::Locked,                       "Locked"                            },
                { HttpStatus::FailedDependency,             "Failed Dependency"                 },
                { HttpStatus::TooEarly,                     "Too Early"                         },
                { HttpStatus::UpgradeRequired,              "Upgrade Required"                  },
                { HttpStatus::PreconditionRequired,         "Precondition Required"             },
                { HttpStatus::TooManyRequests,              "Too Many Requests"                 },
                { HttpStatus::RequestHeaderTooLarge,        "Request Header Too Large"          },
                { HttpStatus::LoginTimeout,                 "Login Timeout"                     },
                { HttpStatus::NoResponse,                   "No Response"                       },
                { HttpStatus::RetryWith,                    "Retry With"                        },
                { HttpStatus::ParentalControl,              "Parental Control"                  },
                { HttpStatus::Censored,                     "Censored"                          },
                { HttpStatus::BadArgument,                  "Bad Argument Provided"             },
                { HttpStatus::BadHTTPVersion,               "Incompatible HTTP Version"         },
                { HttpStatus::MissingURI,                   "Missing URI"                       },
                { HttpStatus::BadURI,                       "Malformed URI"                     }, 
                { HttpStatus::ClientClosedRequest,          "Client Closed Request"             },

                { HttpStatus::InternalError,                "Internal Error"                    },
                { HttpStatus::NotImplemented,               "Not Implemented"                   },
                { HttpStatus::BadGateway,                   "Bad Gateway"                       },
                { HttpStatus::ServiceUnavailable,           "Service Unavailable"               },
                { HttpStatus::GatewayTimeout,               "Gateway Timeout"                   },
                { HttpStatus::HTTPVersionNotSupported,      "Http Version Not Supported"        },
                { HttpStatus::VariantAlsoNegotiates,        "Variant Also Negotiates"           },
                { HttpStatus::InsufficientStorage,          "Insufficient Storage"              },
                { HttpStatus::LoopDetected,                 "Loop Detected"                     },
                { HttpStatus::BandwidthLimitExceeded,       "Bandwidth Limit Exceeded"          },
                { HttpStatus::NotExtended,                  "Not Extended"                      },
                { HttpStatus::NetworkAuthenticationReq,     "Network Authentication Required"   },
                { HttpStatus::InvalidSSLCertificate,        "Invalid SSL Certificate"           },
                { HttpStatus::UnableToPerform,              "Unable to Perform Requested Function" },
                { HttpStatus::CurlError,                    "Error in CURL library"             },
                { HttpStatus::NetworkReadTimeout,           "Network Read Timeout"              },
                { HttpStatus::NetworkConnectTimeout,        "Network Connect Timeout"           }
            };


            HttpStatusMap      ret;
            for(auto& k : kCodes)
                ret[k.code] 	= k.message;
            return ret;
        }
        
        const HttpStatusMap& statusMessages()
        {
            static const HttpStatusMap ret = makeStatusMessage();
            return ret;
        }
    }

    std::string_view    statusMessage(unsigned short code)
    {
        const auto & r	= statusMessages();
        if(!r.valid((int) code))
            return std::string_view();
        return r[code];
    }

    std::string_view    statusMessage(HttpStatus code)
    {
        return statusMessages()[code];
    }

    YQ_INVOKE(
        statusMessages();
    )
}
