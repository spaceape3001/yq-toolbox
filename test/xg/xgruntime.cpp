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
#include <yq/xg/XGRuntime.hpp>

#ifdef gid_t
    #undef gid_t
#endif

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

    GDocumentCPtr   gdoc;
    GGraph          graph;
    XGRuntime       xg;
    
    "loadSimple"_test = [&](){
    
        gdoc        = GDocument::IO::load("yq/xg/test/start_stop.g");
        expect(gdoc.valid() == true);
        if(!gdoc)
            return;
            
        expect(gdoc->read_only() == true);
        expect(gdoc->kind() == "executive");

        graph       = GGraph(READ_ONLY, gdoc);

        expect(graph.document() == gdoc.ptr());
        expect(graph.valid() == true);
        expect(graph.nodes(COUNT) == 2);
        expect(graph.edges(COUNT) == 1);
    };
    
    "compileSimple"_test = [&](){
        expect(gdoc.valid() == true);
        if(!gdoc)
            return ;
        
        std::error_code ec  = xg.initialize(graph);
        expect(ec == std::error_code());
        if(ec != std::error_code()){
            yError() << "Unable to compile executive graph runtime: " << ec.message();
            return;
        }
        
        expect(xg.valid() == true);
    };
    
    "executeSimple"_test = [&](){
        expect(xg.valid() == true);
        if(!xg.valid())
            return ;
            
        #if 0
        using yq::gid_t;
            
        std::vector<gid_t>  history;
        XGUnitOptions       opts;
        opts.history    = [&](gid_t i, const xg_result_t&){
            history.push_back(i);
        };
        
        auto r = xg.execute(opts);
        
        expect(is_done(r) == true);

        if(auto p = std::get_if<std::error_code>(&r)){
            yError() << "Unable to execute executive graph runtime: " << p->message();
            return;
        }
        
        if(!is_done(r))
            return;
        
        expect(history.size() == 2);
        if(history.size() == 2){
            expect(history[0] == 1);
            expect(history[1] == 3);
        }
        #endif
    };
    
    return ut::cfg<>.run();
}
