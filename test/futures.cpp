////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/Future.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::future;

int main(){
    "Empty"_test = []{
        Promise<void>       voidPromise;
        Future<void>        voidFuture;
        voidFuture          = voidPromise.get_future();
        voidPromise.set(DONE);
        expect(voidPromise.valid() == false);
        expect(voidFuture.finished() == true);
    };
    "Bool"_test = []{
        Promise<bool>       boolP;
        Future<bool>        boolV = boolP.get_future();
        expect(boolP.valid() == true);
        expect(boolV.valid() == true);
        boolP.set(true);
        expect(boolP.valid() == false);
        expect(boolV.valid() == true);
        expect(boolV.fate() == Fate::Ready);
        expect(boolV.ready() == true);
        expect(boolV.errored() == false);
        expect(boolV.finished() == true);
        expect(boolV.get() == true);
    };
    
    "Cancel"_test = []{
        Promise<void>   voidP;
        Future<void>    voidF = voidP.get_future();
        voidF.cancel();
        expect(voidP.cancelled() == true);
        voidP.set(CANCEL);
        expect(voidF.fate() == Fate::Cancelled);
    };
    return ut::cfg<>.run();
};

