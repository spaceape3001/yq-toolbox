////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <basic/meta/Init.hpp>
#include <basic/Any.hpp>
#include <basic/Global.hpp>
#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int answer  = 42;

void    print(const std::string& s)
{
    std::cout << s << '\n';
}

void    list_global_variables()
{
    auto&   res = global::variable::names();
    std::cout << "There are (" << res.size() << ") global variables:\n";
    for(auto& s : res)
        std::cout << "> " << s << "\n";
}

void    list_global_methods()
{
    auto&   res = global::function::names();
    std::cout << "There are (" << res.size() << ") global functions:\n";
    for(auto& s : res)
        std::cout << "> " << s << "\n";
}


int main(){
    {
        auto g = writer<Global>();
        g.variable("42", &answer);
        g.function("print", &print).argument("string");
    }
        

    Meta::freeze();
    list_global_variables();
    list_global_methods();
    //return ut::cfg<>.run();
}
