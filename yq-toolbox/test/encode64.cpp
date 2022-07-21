////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <basic/ByteArray.hpp>
#include <basic/Encode64.hpp>
#include <basic/Logging.hpp>
#include <basic/TextUtils.hpp>
#include <cstring>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;


bool    encode_decode(std::initializer_list<uint32_t> values)
{
    ByteArray   bytes((const char*) std::data(values), sizeof(uint32_t)*values.size());
    ByteArray   result  = base64_decode(base64_encode(bytes));
    return result == bytes;
}

ut::suite tests = []{
    
    //  TEST BIT PATTERNS
    //  --------------
    //  0x78 0x56 0x32 
    //  0 1 1 1 1 0   0 0 | 0 1 0 1   0 1 1 0 | 0 0   1 1 0 0 1 0 
    //  0 1 1 1 1 0 | 0 0   0 1 0 1 | 0 1 1 0   0 0 | 1 1 0 0 1 0 
    //  0x1E 0x05 0x18 0x32
    //  --------------
    //  0x41 0xA3 0xCA
    //  0 1 0 0 0 0   0 1 | 1 0 1 0   0 0 1 1 | 1 1   0 0 1 0 1 0
    //  0 1 0 0 0 0 | 0 1   1 0 1 0 | 0 0 1 1   1 1 | 0 0 1 0 1 0
    //  0x10 0x1A 0x0F 0x0A
    //  --------------
    //  0xD1 0x48 0xDA
    //  1 1 0 1 0 0   0 1 | 0 1 0 0   1 0 0 0 | 1 1   0 1 1 0 1 0
    //  1 1 0 1 0 0 | 0 1   0 1 0 0 | 1 0 0 0   1 1 | 0 1 1 0 1 0
    //  0x34 0x14 0x23 0x1A

    "triple_in"_test = [](){
        expect( Encode64::encode64({ 0x78, 0x56, 0x32 }) == Encode64::E64{ 0x1E, 0x05, 0x18, 0x32 } );
        expect( Encode64::encode64({ 0x41, 0xA3, 0xCA }) == Encode64::E64{ 0x10, 0x1A, 0x0F, 0x0A } );
        expect( Encode64::encode64({ 0xD1, 0x48, 0xDA }) == Encode64::E64{ 0x34, 0x14, 0x23, 0x1A } );
    };
    
    "quadruple_out"_test = [](){
        expect( Encode64::decode64({ 0x1E, 0x05, 0x18, 0x32 }) == Encode64::R64{ 0x78, 0x56, 0x32 } );
        expect( Encode64::decode64({ 0x10, 0x1A, 0x0F, 0x0A }) == Encode64::R64{ 0x41, 0xA3, 0xCA } );
        expect( Encode64::decode64({ 0x34, 0x14, 0x23, 0x1A }) == Encode64::R64{ 0xD1, 0x48, 0xDA } );
    };
    
    "encode triple"_test = [](){
        expect( "eFYy"s == base64_encode({ 0x78, 0x56, 0x32 }) );
        expect( "QaPK"s == base64_encode({ 0x41, 0xA3, 0xCA }) );
        expect( "0Uja"s == base64_encode({ 0xD1, 0x48, 0xDA }) );
    };
    
    "encode two"_test = [](){
        expect( "eFY="s == base64_encode({ 0x78, 0x56 }) );
        expect( "QaM="s == base64_encode({ 0x41, 0xA3 }) );
        expect( "0Ug="s == base64_encode({ 0xD1, 0x48 }) );
    };

    "encode one"_test = [](){
        expect( "eA=="s == base64_encode({ 0x78 }) );
        expect( "QQ=="s == base64_encode({ 0x41 }) );
        expect( "0Q=="s == base64_encode({ 0xD1 }) );
    };
    
    
    "decode triple"_test = [](){
        expect( ByteArray({0x78, 0x56, 0x32}) == base64_decode("eFYy"sv));
        expect( ByteArray({0x41, 0xA3, 0xCA}) == base64_decode("QaPK"sv));
        expect( ByteArray({0xD1, 0x48, 0xDA}) == base64_decode("0Uja"sv));
    };
    
    "decode two"_test = [](){
        expect( ByteArray({0x78, 0x56}) == base64_decode("eFY="sv));
        expect( ByteArray({0x41, 0xA3}) == base64_decode("QaM="sv));
        expect( ByteArray({0xD1, 0x48}) == base64_decode("0Ug="sv));
    };
    
    "decode one"_test = [](){
        expect( ByteArray({0x78}) == base64_decode("eA=="sv));
        expect( ByteArray({0x41}) == base64_decode("QQ=="sv));
        expect( ByteArray({0xD1}) == base64_decode("0Q=="sv));
    };
    
    "encode_decode"_test = [](){
        encode_decode({0x12345678, 0x87654321});
        
        // nothing special about the numbers, randomly chosen
        encode_decode({0xA6FFEBC1, 0xDBB3D77E, 0x655C3C5A, 0x10485353 });
    };

};


int main(){

    log_to_std_error();
    return ut::cfg<>.run();
}
