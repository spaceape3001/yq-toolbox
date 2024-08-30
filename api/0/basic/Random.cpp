////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "Random.hpp"
#include <random>
#include <sys/random.h>

namespace yq {

    namespace {

        struct Rand {
            std::random_device                          dev;
            std::seed_seq                               seed;
            std::mt19937_64                             gen;
            std::uniform_real_distribution<double>      dist;
            
            Rand() : seed({
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), 
                dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev()
            }), gen(seed), dist(0.0, 1.0) {}
            
            double      operator()() 
            {
                return dist(gen);
            }
            
        };
    }

    uint64_t        randU64()
    {
        static constexpr const  uint64_t    SZ      = 32;
        static thread_local     uint64_t    buffer[SZ];
        static thread_local     uint64_t    nxt     = SZ;
        
        if(nxt >= SZ){
            (void) !getrandom(buffer, sizeof(buffer), 0);
            nxt     = 0;
        }
        
        return buffer[nxt++];
    }


    double urand()
    {
        static thread_local     Rand r;
        return r();
    }


    double      random(double minVal, double maxVal)
    {
        return minVal + (maxVal-minVal) * urand();
    }

    float       random(float minVal, float maxVal)
    {
        return (float)(minVal + (maxVal-minVal) * urand());
    }

    int8_t      random(int8_t minVal, int8_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (int8_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (int8_t) ceil((maxVal-minVal) * urand());
    }

    int16_t     random(int16_t minVal, int16_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (int16_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (int16_t) ceil((maxVal-minVal) * urand());
    }

    int32_t     random(int32_t minVal, int32_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (int32_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (int32_t) ceil((maxVal-minVal) * urand());
    }

    int64_t     random(int64_t minVal, int64_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (int64_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (int64_t) ceil((maxVal-minVal) * urand());
    }

    uint8_t     random(uint8_t minVal, uint8_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (uint8_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (uint8_t) ceil((maxVal-minVal) * urand());
    }

    uint16_t    random(uint16_t minVal, uint16_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (uint16_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (uint16_t) ceil((maxVal-minVal) * urand());
    }

    uint32_t    random(uint32_t minVal, uint32_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (uint32_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (uint32_t) ceil((maxVal-minVal) * urand());
    }

    uint64_t    random(uint64_t minVal, uint64_t maxVal)
    {
        if(maxVal >= minVal)
            return minVal + (uint64_t) floor((maxVal-minVal) * urand());
        else
            return minVal + (uint64_t) ceil((maxVal-minVal) * urand());
    }


}

