function(group_files)
        foreach(_source ${ARGN})
                get_filename_component(_source_path "${_source}" PATH)
                string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
                source_group("${_source_path_msvc}" FILES "${_source}")
        endforeach()
endfunction(group_files)

