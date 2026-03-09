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
#include <yq/graph/GNode.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/process/PluginLoader.hpp>
#include <yq/text/format.hpp>
#include <yq/xg/XGElement.hpp>
#include <yq/xg/XGRuntime.hpp>

#ifdef gid_t
    #undef gid_t
#endif

namespace ut = boost::ut;
using namespace ut;
using namespace yq;


int main(int argc, char* argv[])
{
    using yq::gid_t;
    struct TestData {
        const char*                     file;
        size_t                          nodes;
        size_t                          edges;
        std::initializer_list<gid_t>    path;
        bool                            print = false;
    } kTestData[] = {
        { "yq/xg/test/start_stop.g", 2, 1, { 1, 3 } },
        { "yq/xg/test/true_false.g", 5, 4, { 1, 3, 12 } }
    };

    BasicAppConfig  cfg;
    cfg.log_cerr    = {};
    cfg.log_cout    = LogPriority::Debug;
    
    BasicApp    app(argc, argv, cfg);
    Meta::init();
    Resource::add_paths(config::data_dir());
    Meta::init();
    load_plugin_dir("plugin/xg");
    Meta::freeze();

    "graphTraversal"_test = [&](){
        for(auto& k : kTestData){
            
            GDocumentCPtr   gdoc    = GDocument::IO::load(k.file);
            expect(gdoc.valid() == true);
            if(!gdoc){
                yError() << k.file << "> Unable to load graph";
                continue;
            }
                
            expect(gdoc->read_only() == true);
            expect(gdoc->kind() == "executive");
            
            GGraph graph       = GGraph(READ_ONLY, gdoc);

            expect(graph.document() == gdoc.ptr());
            expect(graph.valid() == true);
            expect(graph.nodes(COUNT) == k.nodes);
            expect(graph.edges(COUNT) == k.edges);
            
            XGRuntime   xg;
            std::error_code ec = xg.initialize(graph);
            expect(ec == std::error_code());
            
            
            if(ec != std::error_code()){
                yError() << k.file << "> Unable to compile executive graph: " << ec.message();
                continue;
            }
            
            expect(xg.elements(COUNT) == k.nodes);
            expect(xg.valid() == true);
            

            std::vector<gid_t>  history;
            
            XGRuntimeOptions    opts;
            opts.history    = [&](const GNode& gn, const xg_result_t& res){
                if(k.print){
                    const XGElement* elem = xg.element(gn);
                    if(elem){
                        yInfo() << k.file << "> " << elem->metaInfo().name() << ":" << gn.id() << " => " << res;
                    }
                }
                history.push_back(gn.id());
            };
                
            auto r = xg.execute(opts);
            
            if(k.print)
                yInfo() << k.file << "> Execution result: " << r;
            
            expect(is_done(r) == true);
            if(auto p = std::get_if<std::error_code>(&r)){
                yInfo() << k.file << ">  Unable to execute executive graph runtime: " << p->message();
                continue;
            }
            
            if(!is_done(r))
                continue;
                
            expect(history.size() == k.path.size());
            if(history.size() != k.path.size()){
                yInfo() << k.file << ">  History size mismatch";
                continue;
            }

            for(size_t n = 0; n<history.size(); ++n)
                expect(history[n] == *(k.path.begin()+n));
        }
    
    };
    
    return ut::cfg<>.run();
}
