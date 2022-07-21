////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Execute.hpp"
#include <basic/ByteArray.hpp>
#include <basic/Logging.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-enum-enum-conversion"
#include <pstream.h>
#pragma GCC diagnostic pop

namespace yq {
    ByteArray       ProcessDescriptor::execute(const ByteArray& stdInput, ByteArray* stdErrors, int *exit_code) const
    {
        ByteArray ret;
        if(!args.empty()){

            redi::pstreams::pmode   mode    = redi::pstreams::pstdout;
            if(!stdInput.empty())
                mode |= redi::pstreams::pstdin;
            if(stdErrors)
                mode |= redi::pstreams::pstderr;
            const std::string&  cmd = args[0];
            redi::pstream   proc(cmd, args, mode);
            auto p = proc.rdbuf();
            if(!stdInput.empty()){
                proc.write(stdInput.data(), stdInput.size());
                p->peof();
            }
         
            //bool moreOut    = true;
            //bool moreErr    = stdErrors != nullptr;
            char buf[1024];
            std::streamsize n   = 0;
            auto& out   = proc.out();
            auto& err   = proc.err();
            
            do {
                while((n = out.readsome(buf, sizeof(buf))) > 0){
                    ret.append(buf, n);
                }
                if(stdErrors){
                    while((n = err.readsome(buf, sizeof(buf))) > 0){
                        stdErrors -> append(buf, n);
                    }
                }
            } while((!p->exited()) || !out.eof());
            
            if(exit_code)
                *exit_code   = p->status();
        }
        return ret;
    }
    
}
