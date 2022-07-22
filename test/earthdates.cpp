////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <earth/Date.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq::earth;

bool    jday_test(Date d, JulianDay j)
{
    Date        d2  = date(j);
    JulianDay   j2  = julian_day(d);
    return (d == d2) && (j == j2);
}


ut::suite tests = []{
    "julian days"_test = []{
        expect(true == jday_test({ 2012, 11, 23 }, { 2456255 }));
        expect(true == jday_test({ 2012, 2, 29 }, { 2455987 }));
        expect(true == jday_test({ 2012, 2, 28 }, { 2455986 }));
        expect(true == jday_test({ 2012, 3,  1 }, { 2455988 }));
        expect(true == jday_test({ 1776, 2, 29 }, { 2369790 }));
    };
};

int main(){
    return ut::cfg<>.run();
};

