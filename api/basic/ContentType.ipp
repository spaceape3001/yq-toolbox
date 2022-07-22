////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Http.hpp"

#include <basic/DelayInit.hpp>
#include <basic/EnumMap.hpp>
#include <basic/Logging.hpp>
#include <basic/StreamOps.hpp>
#include <basic/stream/Text.hpp>
#include <basic/TextUtils.hpp>
#include <stdio.h>

namespace yq {

    bool        isImage(ContentType ct)
    {
        switch(ct){
        case ContentType::bmp:
        case ContentType::gif:
        case ContentType::jpeg:
        case ContentType::png:
        case ContentType::svg:
        case ContentType::tiff:
            return true;
        default:
            return false;
        }
    }

    bool    isTextual(ContentType ct)
    {
        switch(ct){
        case ContentType::css:
        case ContentType::csv:
        case ContentType::form:
        case ContentType::html:
        case ContentType::javascript:
        case ContentType::json:
        case ContentType::latex:
        case ContentType::markdown:
        case ContentType::rtf:
        case ContentType::svg:
        case ContentType::text:
        case ContentType::xml:
            return true;
        default:
            return false;
        }
    }
    
    bool            isAudio(ContentType ct)
    {
        switch(ct){
        case ContentType::mp3:
        case ContentType::ogg:
        case ContentType::wave:
            return true;
        default:
            return false;
        }
    }
    
    bool            isMovie(ContentType ct)
    {
        switch(ct){
        case ContentType::mp4:
        case ContentType::mpeg:
            return true;
        default:
            return false;
        }
    }


    namespace {
        
        using ContentTypeMap	= EnumMap<ContentType, std::string_view>;
        
        ContentTypeMap makeContentType()
        {
            static const struct {
                ContentType::enum_t     code;
                std::string_view        mime;
            } kCodes[] = {
                { ContentType::unknown,         "application/octet-stream"  },
                { ContentType::binary,          "application/octet-stream"  },
                { ContentType::bmp,             "image/bmp"                 },
                { ContentType::css,             "text/css"                  },
                { ContentType::csv,             "text/csv"                  },
                { ContentType::form,            "application/x-www-form-urlencoded" },
                { ContentType::gif,             "text/gif"                  },
                { ContentType::html,            "text/HTML"                 },
                { ContentType::javascript,      "application/javascript"    },
                { ContentType::jpeg,            "image/jpeg"                },
                { ContentType::json,            "application/json"          },
                { ContentType::latex,           "application/x-latex"       },
                { ContentType::markdown,        "text/markdown"             },
                { ContentType::mp3,             "audio/mpeg3"               },
                { ContentType::mp4,             "video/mp4"                 },
                { ContentType::mpeg,            "video/mpeg"                },
                { ContentType::ogg,             "audio/ogg"                 },
                { ContentType::pdf,             "application/pdf"           },
                { ContentType::png,             "image/png"                 },
                { ContentType::rtf,             "text/richtext"             },
                { ContentType::svg,             "image/svg+xml"             },
                { ContentType::text,            "text/plain"                },
                { ContentType::tiff,            "image/tiff"                },
                { ContentType::wave,            "audio/wav"                 },
                { ContentType::xml,             "text/xml"                  }
            };
            
            ContentTypeMap ret;
            for(auto& k : kCodes)
                ret[k.code] = k.mime;
            return ret;
        }
        
        const ContentTypeMap&	contentTypes()
        {
            static const ContentTypeMap	ret = makeContentType();
            return ret;
        }
        
        using ContentExtMap = Map<std::string_view,ContentType,IgCase>;
        
        ContentExtMap   makeExtensionMap()
        {
            static const struct {
                std::string_view        ext;
                ContentType::enum_t     code;
            } kExts[] = {
                { "bmp",    ContentType::bmp        },
                { "css",    ContentType::css        },
                { "csv",    ContentType::csv        },
                { "gif",    ContentType::gif        },
                { "htm",    ContentType::html       },
                { "html",   ContentType::html       },
                { "js",     ContentType::javascript },
                { "jpe",    ContentType::jpeg       },
                { "jpeg",   ContentType::jpeg       },
                { "jpg",    ContentType::jpeg       },
                { "json",   ContentType::json       },
                { "latex",  ContentType::latex      },
                { "md",     ContentType::markdown   },
                { "mp3",    ContentType::mp3        },
                { "mp4",    ContentType::mp4        },
                { "ogg",    ContentType::ogg        },
                { "pdf",    ContentType::pdf        },
                { "png",    ContentType::png        },
                { "rtf",    ContentType::rtf        },
                { "svg",    ContentType::svg        },
                { "tex",    ContentType::latex      },
                { "txt",    ContentType::text       },
                { "tif",    ContentType::tiff       },
                { "tiff",   ContentType::tiff       },
                { "wav",    ContentType::wave       },
                { "xml",    ContentType::xml        }
            };
            
            ContentExtMap ret;
            for(auto& k : kExts)
                ret[k.ext]  = k.code;
            return ret;
        }
        
        const ContentExtMap&    extToTypeMap()
        {
            static const ContentExtMap s_ret = makeExtensionMap();
            return s_ret;
        }
        
    }

    std::string_view    mimeType(ContentType ct)
    {
        return contentTypes()[ct];
    }

    ContentType mimeTypeForExt(std::string_view ext)
    {
        const auto& r = extToTypeMap();
        return r.get(ext);
    }


    YQ_INVOKE(
        contentTypes();
        extToTypeMap();
    )
}
