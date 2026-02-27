////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/config/config.hpp>
#include <yq/core/BasicApp.hpp>
#include <yq/core/BasicAppConfig.hpp>
#include <yq/core/Logging.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/process/PluginLoader.hpp>
#include <yq/text/format.hpp>
#include <yq/xg/XGUnit.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main(int argc, char* argv[])
{
    BasicAppConfig  cfg;
    cfg.log_cerr    = {};
    cfg.log_cout    = LogPriority::Debug;
    
    BasicApp    app(argc, argv, cfg);
    Meta::init();
    Resource::add_paths(config::data_dir());
    Meta::init();
    load_plugin_dir("plugin/xg");
    Meta::freeze();

    GDocumentCPtr   gdoc    = GDocument::IO::load("yq/xg/test/start_stop.g");
    GGraph          graph(READ_ONLY, gdoc);
    XGUnit       runtime;
    
    "loaded"_test = [&](){
        expect(gdoc.valid() == true);
        if(!gdoc)
            return;
            
        expect(gdoc->read_only() == true);
        expect(gdoc->kind() == "executive");

        expect(graph.document() == gdoc.ptr());
        expect(graph.valid() == true);
        expect(graph.nodes(COUNT) == 2);
        expect(graph.edges(COUNT) == 1);
    };
    
    "compile"_test = [&](){
        expect(gdoc.valid() == true);
        if(!gdoc)
            return ;
        
        std::error_code ec  = runtime.compile(graph);
        expect(ec == std::error_code());
        if(ec != std::error_code()){
            yError() << "Unable to compile executive graph runtime: " << ec.message();
            return;
        }
        
        expect(runtime.empty() == false);
    };
    

    return ut::cfg<>.run();
}
