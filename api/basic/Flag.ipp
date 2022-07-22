////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "Flag.hpp"
#include <basic/TextUtils.hpp>

namespace yq {
    std::string     flag_string(const EnumDef* def, uint64_t values, std::string_view sep)
    {
        std::string ret;
        if(!def || !values)
            return std::string();
        
        bool    f = true;
        for(auto& i : def->val2name()){
            if(i.first < 0)
                continue;
            if(i.first >= (int)(sizeof(values)*8))
                continue;
            if(!(values & (1ULL << i.first)))
                continue;
            if(f){
                f   = false;
            } else {
                ret += sep;
            }
            ret += i.second;
        }
        return ret;
    }

    template <>
    uint64_t        flag_decode<uint64_t>(const EnumDef* def, std::string_view keys, std::string_view sep)
    {
        if(keys.empty() || sep.empty() || !def)
            return 0ULL;

        uint64_t    ret   = 0ULL;
        vsplit(keys, sep, [&](std::string_view k){
            k   = trimmed(k);
            auto r = def->value_of(k);
            if(!r.good)
                return ;
            ret |= (1ULL << r.value);
        });
        return ret;
    }
}
