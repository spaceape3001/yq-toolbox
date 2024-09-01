////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/io/KeyValue.hpp>
#include <0/io/FileUtils.hpp>
#include <yq/basic/Logging.hpp>
#include <yq/text/match.hpp>
#include <yq/container/ByteArray.hpp>

using namespace yq;

void    print(const KVTree& tree, unsigned int depth=0)
{
    for(auto& a : tree.subs){
        for(unsigned int i=0;i<depth;++i)
            std::cout << "    ";
        std::cout << a.key << '\t' << a.data << '\n';
        print(a, depth+1);
    }
}

int main(int argc, char* argv[])
{
    const char* zfile   = nullptr;
    bool do_body        = false;
    for(int i=1; i<argc; ++i){
        if((argv[i][0] == '-') && (argv[i][1] == '-')){
            if(is_similar(argv[i], "--body"))
                do_body = true;
        } else {
            if(!zfile)
                zfile   = argv[i];
        }
    }
    
    if(!zfile){
        std::cerr << "Usage: " << argv[0] << " [--body] [file]\n";
        return -1;
    }
    
    
    log_to_std_error();
    KVTree          tree;
    std::string    bytes   = file_string(zfile);
    unsigned int opts   = KVTree::RECURSIVE;
    if(do_body)
        opts |= KVTree::BODY;
    auto ret =tree.parse(bytes, zfile, opts);
    if(ret.ec != std::error_code())
        return -1;
    print(tree);
    if(!ret.body.empty())
        std::cout << '\n' << ret.body << '\n';
    return 0;
}
