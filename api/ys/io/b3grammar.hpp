////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//#include <doodler/preamble.hpp>
#include <yq/core/Expect.hpp>
#include <yq/core/Flags.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <utility>

namespace yq::spatial {
    struct B3Line {
        string_vector_t tokens;
        uint32_t        line        = 0;            //!< Line number
        uint16_t        indent      = 0;            //!< Line indent
        
        static Expect<B3Line>   decode(const char*& text, const char* last, uint32_t& line);
        static Expect<B3Line>   decode(std::string_view);
        
        bool    empty() const { return tokens.empty(); }
    };
    
    #if 0
    struct B3Error {
        std::string     message;
        uint32_t        line    = 0;
    };
    
    //using B3Result  = 
    
    struct B3Command {
        arg_vector_t    pArgs;                      //!< Positional arguments 0, 1, 2...
        arg_map_t       nArgs;                      //!< Named arguments x=foo
        b3cmd_vector_t  subcommands;
        uint32_t        line        = 0;            //!< Line number
        uint16_t        indent      = 0;            //!< Line indent
    };

    struct B3Document {
        std::filesystem::path       file;
        b3cmd_vector_t              commands;
        
        static std::pair<B3Document,std::error_code>    load(const std::filesystem::path&);
        static std::pair<B3Document,std::error_code>    load(std::string_view);
    };
    #endif

}
