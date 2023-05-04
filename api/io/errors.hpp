////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/ErrorDB.hpp>

namespace yq::errors {
    using cant_open_read            = error_db::entry<"Unable to open file for reading">;
    using cant_open_write           = error_db::entry<"Unable to open file for writing">;
    using failed_to_write_file      = error_db::entry<"Failed to write to the file">;
    using filepath_empty            = error_db::entry<"Filepath is empty">;
    using xml_bad_syntax            = error_db::entry<"XML syntax failure">;
    using xml_no_root_element       = error_db::entry<"XML document has no sutable root element">;
    using xml_wrong_document_node   = error_db::entry<"XML document type does not match expectations">;
}
