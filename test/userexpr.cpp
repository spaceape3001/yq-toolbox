////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/expr/Grammar.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;
using namespace yq::expr;

ut::suite tests = []{
    "Parse"_test = []{
        const Grammar&  defGram = Grammar::default_grammar();
        
        expect( defGram.next_token(U"0") == Token{ 1, SymType::Value });
        expect( defGram.next_token(U"pi") == Token{ 2, SymType::Text });
        expect( defGram.next_token(U"3pi") == Token{ 1, SymType::Value });
        expect( defGram.next_token(U".3pi") == Token{ 2, SymType::Value });
        expect( defGram.next_token(U"+.3pi") == Token{ 1, SymType::Operator });
        expect( defGram.next_token(U"1e3a") == Token{ 3, SymType::Value });
        expect( defGram.next_token(U"1e+3a") == Token{ 4, SymType::Value });
        expect( defGram.next_token(U"1e-3a") == Token{ 4, SymType::Value });
        expect( defGram.next_token(U"1.e+3a") == Token{ 5, SymType::Value });
        expect( defGram.next_token(U".1e+3a") == Token{ 5, SymType::Value });
        expect( defGram.next_token(U"0.1e+3a") == Token{ 6, SymType::Value });
        expect( defGram.next_token(U"0.1e--3a") == Token{ 3, SymType::Value });
        expect( defGram.next_token(U"abc3_0.1e--3a") == Token{ 6, SymType::Text });
    
    };
};

int main(){
    return ut::cfg<>.run();
};

