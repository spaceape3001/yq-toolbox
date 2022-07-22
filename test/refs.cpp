////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <basic/Ref.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

struct TestObj : public RefCount {
    static int& counter() 
    { 
        static int  count   = 0;
        return count;
    }
    
    TestObj()
    {
        ++counter();
    }
    
    ~TestObj()
    {
        --counter();
    }
};

ut::suite tests = []{
    "Initial Count"_test = []{
        expect(TestObj::counter() == 0);
    };
    
    "Empty"_test = []{
        Ref<TestObj>    obj;
        expect(true == obj.invalid());
        expect(obj.ptr() == nullptr);
    };
    
    "Single Item"_test = []{
        expect(TestObj::counter() == 0);
        {
            Ref<TestObj>    obj;
            expect(0 == TestObj::counter());
            obj = new TestObj;
            expect(1 == TestObj::counter());
            expect(true == obj.valid());
            expect(nullptr != obj.ptr());
            expect(true == obj->unique());
            expect(1 == obj->count());
        }
        expect(0 == TestObj::counter());
    };
    
    "Many Items"_test = []{
        expect(0 == TestObj::counter());
        {
            Ref<TestObj> obj = new TestObj;
            expect(1 == TestObj::counter());
            expect(true == obj->unique());
            {
                static constexpr const size_t cnt  = 200;
                std::vector<Ref<TestObj>>       objs;
                for(size_t i=0;i<cnt;++i)
                    objs.push_back(obj);
                expect(1 == TestObj::counter());
                expect(cnt+1 == obj -> count());
                expect(false == obj->unique());
            }
            expect(true == obj->unique());
            expect(1 == obj->count());
        }
        expect(0 == TestObj::counter());
    };
};

int main(){
    return ut::cfg<>.run();
};

