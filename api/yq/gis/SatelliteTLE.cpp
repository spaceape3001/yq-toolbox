////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SatelliteTLE.hpp"
#include <0/basic/TextUtils.hpp>

namespace yq {
    Expect<SatelliteTLE>  SatelliteTLE::parse( std::string_view line0, std::string_view line1, std::string_view line2)
    {
    
        line0   = trimmed(line0);
        line1   = trimmed(line1);
        line2   = trimmed(line2);
        
        SatelliteTLE        ret;
        if(!line0.empty())
            ret.name        = to_string(line0.substr(0,24));
        
        if(!line1.empty()){
            if(!verify_checksum(line1))
                return errors::checksum_failure();
                
            auto catnum  = to_uint32(line1.substr(2,5));
            if(catnum){
                ret.catalog = *catnum;
            } else
                return unexpected(catnum.error());
                
            ret.classification  = line1[7];
            auto lyear  = to_uint8(line1.substr(9,2));
            if(lyear){
                ret.launchYear  = *lyear;
            } else
                return unexpected(lyear.error());
        }
        
        if(!line2.empty()){
            if(!verify_checksum(line2))
                return errors::checksum_failure();
        }
        
        return ret;
    }
    
    Expect<SatelliteTLE>  SatelliteTLE::parse( std::string_view line1, std::string_view line2)
    {
        return parse({}, line1, line2 );
    }

    bool     SatelliteTLE::verify_checksum(std::string_view line)
    {
        if(line.size() < 69)
            return false;
        
        size_t      sum = 0;
        for(size_t i=0;i<68;++i){
            if(line[i] == '-')
                ++sum;
            if(is_digit(line[i]))
                sum += (line[i]-'\0');
        }
        
        return line[68] == (char)('\0' + (sum % 10));
    }
}
