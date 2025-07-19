////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceUrlDriver.hpp>
//#include "UrlDriver.hxx"

namespace yq {
    ///////////////////////////////////

    ResourceUrlInfoer::ResourceUrlInfoer(const ResourceMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceInfoer(meta, exts, sl, type)
    {
    }

    ResourceUrlInfoer::~ResourceUrlInfoer()
    {
    }
    
    ///////////////////////////////////

    ResourceUrlLoader::ResourceUrlLoader(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceLoader(meta, exts, sl, type)
    {
    }
    
    ResourceUrlLoader::~ResourceUrlLoader()
    {
    }

    ///////////////////////////////////

    ResourceUrlSaver::ResourceUrlSaver(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceSaver(meta, exts, sl, type)
    {
    }
    
    ResourceUrlSaver::~ResourceUrlSaver()
    {
    }

    ///////////////////////////////////
}
