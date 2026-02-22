////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/core/Logging.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/graph/GEdge.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/graph/GNode.hpp>
#include <yq/graph/GPort.hpp>
#include <yq/meta/Meta.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main(int argc, char* argv[])
{
    "null"_test = []() {
        GGraph       g;
        expect( !g.document().valid() );
        expect( g.id() == 0 );
        expect(g.data() == nullptr );
    };

    "blank"_test = [](){
        GGraph      g(CREATE);
        GDocumentPtr    doc = g.document();
        expect(doc.valid());
        expect(g.id() == 0 );
        expect(g.data() != nullptr );

        expect(doc->edges(COUNT) == 0);
        expect(doc->graphs(COUNT) == 1);
        expect(doc->lines(COUNT) == 0);
        expect(doc->nodes(COUNT) == 0);
        expect(doc->ports(COUNT) == 0);
        expect(doc->shapes(COUNT) == 0);
        expect(doc->texts(COUNT) == 0);
    };
    
    "node"_test = [](){
        GGraph      g(CREATE);
        expect( true == g );
        
        GDocumentPtr    doc = g.document();
        expect(doc.valid());

        GNode       n   = g.node(CREATE);
        expect( true == n);
        expect( n.id() == 1);
        expect( n.data() != nullptr );
        
        expect( g.nodes(COUNT) == 1 );
        
        expect(doc->edges(COUNT) == 0);
        expect(doc->graphs(COUNT) == 1);
        expect(doc->lines(COUNT) == 0);
        expect(doc->nodes(COUNT) == 1);
        expect(doc->ports(COUNT) == 0);
        expect(doc->shapes(COUNT) == 0);
        expect(doc->texts(COUNT) == 0);
    };
    
    "simple"_test = [](){
        GGraph  g(CREATE);
        expect( true == g );
        
        GDocumentPtr    doc = g.document();
        expect(doc.valid());

        GNode   n1  = g.node(CREATE);
        GNode   n2  = g.node(CREATE);
        GPort   p1  = n1.port(CREATE);
        GPort   p2  = n2.port(CREATE);
        GEdge   e1  = g.connect(p1,p2);
        
        expect(doc->edges(COUNT) == 1);
        expect(doc->graphs(COUNT) == 1);
        expect(doc->lines(COUNT) == 0);
        expect(doc->nodes(COUNT) == 2);
        expect(doc->ports(COUNT) == 2);
        expect(doc->shapes(COUNT) == 0);
        expect(doc->texts(COUNT) == 0);
        
        expect(n1.ports().size() == 1);
        expect(n2.ports().size() == 1);
        expect(p1.node() == n1);
        expect(p1.node() != n2);
        expect(p2.node() != n1);
        expect(p2.node() == n2);
        expect(e1.source(PORT) == p1);
        expect(e1.source(NODE) == n1);
        expect(e1.target(PORT) == p2);
        expect(e1.target(NODE) == n2);
        
        expect(g.connected(p1,p2) == true);
        expect(g.connected(p2,p1) == false);
        
        //  connected extended to nodes...?
    };


    return ut::cfg<>.run();
}
