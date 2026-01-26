////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/core/Logging.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/graph/GNode.hpp>
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


    return ut::cfg<>.run();
}
