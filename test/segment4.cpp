////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Segment4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{

};

int main(){
    return ut::cfg<>.run();
};
