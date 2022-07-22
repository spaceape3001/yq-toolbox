////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
//  Simple utilitiy for seeing how the XML file is being intpretted by rapidxml
//
////////////////////////////////////////////////////////////////////////////////

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <iostream>
#include <string_view>

using namespace rapidxml;
using namespace std;

using XB    = xml_base<char>;
using XN    = xml_node<char>;
using XD    = xml_document<char>;
using XA    = xml_attribute<char>;
using XF    = file<char>;

const char*     ntype(node_type nt)
{
    switch(nt){
    case node_document:
        return "doc";
    case node_element:
        return "ele";
    case node_data:
        return "txt";
    case node_cdata:
        return "cda";
    case node_comment:
        return "cmt";
    case node_declaration:
        return "dcl";
    case node_doctype:
        return "doc";
    case node_pi:
        return "pi ";
    default:
        return "unk";
    };
}


string_view name(const XB* xn)
{
    return string_view(xn->name(), xn->name_size());
}

string_view value(const XB* xn)
{
    return string_view(xn->value(), xn->value_size());
}

void    write(const XA* xa, int depth=0)
{
    cout << string(depth, ' ') << "[att] '" << name(xa) << "': " << value(xa) << "\n";
}

void    write(const XN*xn, int depth=0)
{
    cout << string(depth, ' ') << '[' << ntype(xn->type()) << "] '" << name(xn) << "': " << value(xn) << "\n";
    for(const XA* xa=xn->first_attribute();  xa; xa = xa -> next_attribute())
        write(xa, depth+1);
    for(const XN* cn=xn->first_node(); cn; cn = cn -> next_sibling())
        write(cn, depth+1);
}

int main(int argc, char*argv[])
{
    if(argc < 2){
        std::cout << "Usage: xmlread (file)\n";
        return 0;
    }
    
    XF          theFile(argv[1]);
    XD          theDoc;
    try {
        theDoc.parse<0>(theFile.data());
    } catch(const parse_error& ex){
        cerr << "Parse failure " << (ex.where<char>()-theFile.data()) << " bytes in: " << ex.what() << "\n";
        return -1;
    }
    
    write(&theDoc);
    return 0;
}
