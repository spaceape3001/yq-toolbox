////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/gis/Date.hpp>
#include <0/gis/JDay.hpp>
#include <yq/basic/Logging.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

bool    jday_test(Date d, JDay j)
{
    Date        d2  = date(j);
    JDay        j2  = jday(d);
    return (d == d2) && (j == j2);
}

bool    easter_test(uint16_t y, Date d)
{
    Date    ea = easter(y);
    bool f = (ea == d);
    
    if(!f){
        yInfo() << "[" << y << "] gave " << ea << " but wanted " << d;
    }
    
    return f;
}

int main()
{

    "julian days"_test = []{
        expect(true == jday_test({ 2012, 11, 23 }, { 2456255 }));
        expect(true == jday_test({ 2012, 2, 29 }, { 2455987 }));
        expect(true == jday_test({ 2012, 2, 28 }, { 2455986 }));
        expect(true == jday_test({ 2012, 3,  1 }, { 2455988 }));
        expect(true == jday_test({ 1776, 2, 29 }, { 2369790 }));
    };
    
    "julian easter"_test = []{
    
        // test julian
        expect(true == easter_test(179, {179, 4, 12 }));
        expect(true == easter_test(711, {711, 4, 12 }));
        expect(true == easter_test(1243, {1243, 4, 12 }));
    };

    "gregorian easter"_test = []{
        // test gregorian
        expect(true == easter_test(1818, {1818, 3, 22 }));
        expect(true == easter_test(1886, {1886, 4, 25 }));
        expect(true == easter_test(1943, {1943, 4, 25 }));
        expect(true == easter_test(1954, {1954, 4, 18 }));
        expect(true == easter_test(1967, {1967, 3, 26 }));
        expect(true == easter_test(1991, {1991, 3, 31 }));
        expect(true == easter_test(1992, {1992, 4, 19 }));
        expect(true == easter_test(1993, {1993, 4, 11 }));
        expect(true == easter_test(2000, {2000, 4, 23 }));
        expect(true == easter_test(2285, {2285, 3, 22 }));
        expect(true == easter_test(2038, {2038, 4, 25 }));
    };

    log_to_std_error();
    return ut::cfg<>.run();
}

