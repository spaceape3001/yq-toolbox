////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Enum.hpp>

namespace yq {


    YQ_ENUM(ContentType, ,
        unknown                     = 0,
        binary,
        bmp,
        css,
        csv,
        form,
        gif,
        html,
        javascript,
        jpeg,
        json,
        latex,
        markdown,
        mp3,
        mp4,
        mpeg,
        ogg,
        pdf,
        png,
        rtf,
        svg,
        text,
        tiff,
        wave,
        xml
    )

    std::string_view    mimeType(ContentType);
    ContentType         mimeTypeForExt(std::string_view);
    
    //! TRUE for types that can render as images
    bool                isImage(ContentType);
    
    //! TRUE for types that can reasonably render as text
    //! \note this will overlap with isImage for some formats.
    bool                isTextual(ContentType);
    
    bool            isAudio(ContentType);
    bool            isMovie(ContentType);

}
