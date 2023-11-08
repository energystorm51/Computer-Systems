#include <iostream>
#include <list>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {
    /* Tokens for:
     *     class MyClass {
     *          function void myFunction (){
     * 
     *          }
     *     }
     */
    list<Token*> tokens;
    // tokens.push_back(new Token("keyword", "class"));
    // tokens.push_back(new Token("identifier", "MyClass"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("symbol", "}"));

    /* Tokens for:
     *     function void myFunction (int a) {
     *          var int b;
     *          let b = 1;
     *     }
     */
    // tokens.push_back(new Token("keyword", "function"));
    // tokens.push_back(new Token("keyword", "void"));
    // tokens.push_back(new Token("identifier", "myFunction"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "var"));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "let"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", "="));
    // tokens.push_back(new Token("integerConstant", "1"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("symbol", "{"));
    // tokens.push_back(new Token("keyword", "var"));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "var"));
    // tokens.push_back(new Token("keyword", "char"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "let"));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", "="));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("keyword", "let"));
    // tokens.push_back(new Token("identifier", "b"));
    // tokens.push_back(new Token("symbol", "="));
    // tokens.push_back(new Token("keyword", "skip"));
    // tokens.push_back(new Token("symbol", ";"));
    // tokens.push_back(new Token("symbol", "}"));

    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("identifier", "a"));
    // tokens.push_back(new Token("symbol", "+"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("integerConstant", "1"));
    // tokens.push_back(new Token("symbol", "-"));
    // tokens.push_back(new Token("identifier", "c"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", ">"));
    // tokens.push_back(new Token("integerConstant", "5"));
    // tokens.push_back(new Token("symbol", ")"));
    // tokens.push_back(new Token("symbol", "="));
    // tokens.push_back(new Token("keyword", "true"));

    tokens.push_back(new Token("identifier", "Main"));
    tokens.push_back(new Token("symbol", "."));
    tokens.push_back(new Token("identifier", "myFunc"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("integerConstant", "1"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("stringConstant", "Hello"));
    tokens.push_back(new Token("symbol", ")"));

    try {
        CompilerParser parser(tokens);
        ParseTree* result = parser.compileExpression();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }
}