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

    ResourceUrlInfoer::ResourceUrlInfoer(const ResourceMeta& meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) :
        ResourceInfoer(meta, spec, sl, type)
    {
    }

    ResourceUrlInfoer::~ResourceUrlInfoer()
    {
    }
    
    ///////////////////////////////////

    ResourceUrlLoader::ResourceUrlLoader(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceLoader(meta, spec, sl, type)
    {
    }
    
    ResourceUrlLoader::~ResourceUrlLoader()
    {
    }

    ///////////////////////////////////

    ResourceUrlSaver::ResourceUrlSaver(const ResourceMeta&meta, const ResourceIOSpec& spec, const std::source_location& sl, Type type) : 
        ResourceSaver(meta, spec, sl, type)
    {
    }
    
    ResourceUrlSaver::~ResourceUrlSaver()
    {
    }

    ///////////////////////////////////
}
