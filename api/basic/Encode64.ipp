////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/Encode64.hpp>
#include <basic/ByteArray.hpp>
#include <cassert>

namespace yq {
    Encode64::E64   Encode64::encode64(R64 i)
    {
        return {
            (uint8_t)(i.a >> 2),
            (uint8_t)(((i.a & 0x03) << 4) | ((i.b&0xF0) >> 4)),
            (uint8_t)(((i.b & 0x0F) << 2) | ((i.c&0xC0) >> 6)),
            (uint8_t)(i.c & 0x3F)
        };
    }

    Encode64::R64     Encode64::decode64(E64 i)
    {
        return {
            (uint8_t)((i.a << 2) | ((0x30 & i.b) >> 4)),
            (uint8_t)(((i.b & 0xF) << 4) | ((0x3C&i.c) >> 2)),
            (uint8_t)(((i.c & 3) << 6) | (i.d & 0x3F))
        };
    }
    

    Encode64::Encode64(const char*chars, char p) : m_pad(p)
    {
        assert(chars);
        
        memset(m_decode, 0, sizeof(m_decode));
        memset(m_encode, 0, sizeof(m_encode));
        size_t  n   = 0;
        if(chars){
            for(; (n<64) && chars[n]; ++n){
                char    c   = chars[n];
                m_encode[n]             = c;
                m_decode[(uint8_t) c]   = n;
            }
        }
        assert(n==64);
    }

    size_t          Encode64::encode_size(size_t out) const
    {
        size_t  g   = out / 3;
        size_t  ret = g * 4;
        size_t  ov  = out % 3;
        
        if(ov){
            if(m_pad){
                ret  += 4;
            } else {
                ret  += 1 + ov;
            }
        }
        return ret;
    }
    
    size_t          Encode64::decode_size(size_t out) const
    {
        size_t  g   = out / 4;
        size_t  ret = g * 3;
        switch(out & 3){
        case 0:
        case 1:
            break;
        case 2:
            ret += 1;
            break;
        case 3:
            ret += 2;
            break;
        }
        return ret;
    }
    
    inline uint8_t         Encode64::c2e(char ch) const
    {
        return m_decode[(uint8_t) ch];
    }
    
    inline char            Encode64::e2c(uint8_t i) const
    {
        return m_encode[i];
    }
    
    /*! \brief Encodes the specified data
    */
    size_t          Encode64::encode(const void* in_ptr, size_t inN, char*out, size_t outN) const
    {
        if(!in_ptr || !out || !inN || !outN)
            return 0ULL;
            
        const uint8_t*  in = (const uint8_t*) in_ptr;
            
            // limit the work to the output buffer size
        
        size_t      groups  = std::min( inN / 3, outN / 4 );
        size_t      rN      = std::min<size_t>(inN - groups*3, 3);
        size_t      rM      = std::min<size_t>(outN - groups*4, 4);
        size_t      ret     = groups * 4;
        
        for(size_t g=0;g<groups;++g, in+=3, out+=4){
            E64 e   = encode64({ in[0], in[1], in[2] });
            out[0]  = e2c(e.a);
            out[1]  = e2c(e.b);
            out[2]  = e2c(e.c);
            out[3]  = e2c(e.d);
        }
        
        //  There's a remainder
        if(rN && rM){
            E64 e = encode64({ in[0], (rN>1) ? in[1] : (uint8_t) 0, (rN>2) ? in[2] : (uint8_t) 0});
            
            // first out-chacter -- always present
            out[0]      = e2c(e.a);
            ++ret;
            
            // second out-character -- always present if there's room
            if(rM>1){ 
                out[1]  = e2c(e.b);
                ++ret;
            }
            
            // third out-character -- present if two inputs, or there's a pad character defined
            if(rM>2){
                if(rN > 1){
                    out[2]  = e2c(e.c);
                    ++ret;
                } else if(m_pad){
                    out[2]  = m_pad;
                    ++ret;
                }
            }
            
            // fourth out-character -- present if two inputs or there's a pad character defined
            if(rM>3){
                if(rN > 2){
                    out[3]  = e2c(e.d);
                    ++ret;
                } else if(m_pad){
                    out[3]  = m_pad;
                    ++ret;
                }
            }
        }
        
        return ret;
    }
    
    size_t          Encode64::decode(const char* in, size_t inN, uint8_t *out, size_t outN)  const
    {
        if(!in || !out || !inN || !outN)
            return 0ULL;

        size_t      groups  = std::min( inN / 4, outN / 3 );
        size_t      rN      = std::min<size_t>(inN - groups*4, 4);
        size_t      rM      = std::min<size_t>(outN - groups*3, 3);

        // got padding....
        if(groups && in[groups*4-1] == m_pad){
            --groups;
            if(in[groups*4+2] == m_pad){
                rN      = 2;
                rM      = 1;
            } else {
                rN      = 3;
                rM      = 2;
            }
        }

        size_t      ret     = groups * 3;

        for(size_t g=0;g<groups;++g, in+=4, out+=3){
            R64 r = decode64({ c2e(in[0]), c2e(in[1]), c2e(in[2]), c2e(in[3])});
            out[0] = r.a;
            out[1] = r.b;
            out[2] = r.c;
        }
        
        //  there's a remainder
        if(rN && rM){
            R64 r = decode64({ c2e(in[0]), (rN>1) ? c2e(in[1]) : (uint8_t) 0, (rN>2)?c2e(in[2]) : (uint8_t) 0, (rN>3)?c2e(in[3]) : (uint8_t) 0 });
            if(rM>0){   // at least one character
                out[0] = r.a;
                ++ret;
            }
            if(rM>1){   // at least two characters
                out[1] = r.b;
                ++ret;
            }
            if(rM>2){   // got all three
                out[2] = r.c;
                ++ret;
            }
        }
        return ret;
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    const Encode64&  base64()
    {
        static const Encode64   s_ret( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=' );
        return s_ret;
    }


    size_t              base64_decode_size(size_t sz)
    {
        return base64().decode_size(sz);
    }

    ByteArray           base64_decode(std::string_view sv)
    {
        if(sv.empty())
            return ByteArray();
        
        const Encode64&     b64 = base64();
        ByteArray       ret;
        ret.resize(b64.decode_size(sv.size()));
        ret.resize(b64.decode(sv.data(), sv.size(), (uint8_t*) ret.data(), ret.size()));
        return ret;
    }
    

    std::string         base64_encode(const void*ptr, size_t cnt)
    {
        if(!ptr || !cnt)
            return std::string();
            
        const Encode64&     b64 = base64();
        std::string         ret;
        ret.resize(b64.encode_size(cnt));
        ret.resize(b64.encode((const uint8_t*) ptr, cnt, ret.data(), ret.size()));
        return ret;
    }

    std::string         base64_encode(const ByteArray& buf)
    {
        return base64_encode(buf.data(), buf.size());
    }
    
    std::string         base64_encode(std::initializer_list<uint8_t>data)
    {
        return base64_encode(std::data(data), data.size());
    }


    size_t              base64_encode_size(size_t sz)
    {
        return base64().encode_size(sz);
    }
    

}
