////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/MetaRepo.hpp>
#include <0/meta/ReservedIDs.hpp>

namespace yq {
    Meta::Repo::Repo()
    {
        all.reserve(8192);      // adjust as necessary, performance tradeoff, basically
        all.resize(M_USER, nullptr);
    }
    
    Meta::Repo&     Meta::repo()
    {
        static Repo*    s_repo  = new Repo;
        return *s_repo;
    }
}
