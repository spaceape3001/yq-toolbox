////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

/*
    Silly little program to drive the user expression evaluator
*/

#include <yq/core/Any.hpp>
#include <yq/core/Logging.hpp>
#include <yq/stream/StdOutput.hpp>
#include <yq/userexpr/Context.hpp>
#include <yq/userexpr/UserExpr.hpp>

#include <ctime>
#include <iostream>
#include <system_error>

using namespace yq;

int main(int argc, char* argv[])
{
    log_to_std_error();
    Meta::freeze();
    
    time_t      now;
    expr::Context       ctx;
    time(&now);
    ctx.variables[U"x"] = Any((double) now);
    
    for(int n=1;n<argc;++n){
        UserExpr    ux(argv[n]);
        if(!ux.is_good()){
            std::cout << "error: unable to parse.  (" << ux.build_error().message() << ")\n";
            continue;
        }
        auto valx    = ux.evaluate(ctx);
        if(!valx){
            std::cerr << "error: unable to evaluate.  (" << valx.error().message() << ")\n";
            continue;
        }
        
        std::error_code ec = (*valx).print(COUT);
        if(ec != std::error_code()){
            std::cerr << "error: unable to print.  (" << ec.message() << ")\n";
            continue;
        }
        std::cout << '\n';
    }
    return 0;
}
