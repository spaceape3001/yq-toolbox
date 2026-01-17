////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Expect.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/Vector.hpp>
#include <yq/text/IgCase.hpp>
//#include <yq/net/Url.hpp>
#include <filesystem>

namespace yq::b3 {
    struct line_t {

        //! Named attributes
        StringMap           attrs;

        //! Positional arguments
        StringVector        values;
        
        //! Sublines
        std::vector<line_t> sublines;
        
        uint32_t            line        = 0;
    };
    
    
    using line_vector_t = std::vector<line_t>;
    
    struct file_t {
        line_vector_t     lines;
        //Url                     url;
    };
    
    using file_x    = Expect<file_t>;

        // This loads, is does *NOT* execute
    file_x      loadB3File(const std::filesystem::path&);
    file_x      loadB3Buffer(std::string_view);
    file_x      loadB3(std::istream&);
}

