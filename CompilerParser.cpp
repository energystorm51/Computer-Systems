#include "CompilerParser.h"
#include <iostream>


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    current_token_index = 0;
    this->tokens = tokens;
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if(tokens.empty()){
        return NULL;
    }

    if(have("keyword", "class")){
        return compileClass();
    }
    else{
        throw ParseException();
    }

    return NULL;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    // Initialiase class tree
    ParseTree* class_Tree = new ParseTree("class", "");

    // Parse 'class'
    class_Tree->addChild(mustBe("keyword", "class"));

    // Parse className
    std::string class_Name = current()->getValue();
    class_Tree->addChild(mustBe("identifier", class_Name));

    // Parse '{'
    class_Tree->addChild(mustBe("symbol", "{"));

    // Parse classVarDec
    while(have("keyword", "static") || have("keyword", "field")){
        class_Tree->addChild(compileClassVarDec());
    }

    // Parse subroutineDec
    while(have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")){
        class_Tree->addChild(compileSubroutine());
    }

    // Parse '}'
    class_Tree->addChild(mustBe("symbol", "}"));

    return class_Tree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {

    // Initialise classvardec tree
    ParseTree* class_Var_Dec_Tree = new ParseTree("classVarDec", "");

    // Parse 'static' | 'field'
    if(have("keyword", "static")){
        class_Var_Dec_Tree->addChild(mustBe("keyword", "static"));
    }
    else if(have("keyword", "field")){
        class_Var_Dec_Tree->addChild(mustBe("keyword", "field"));
    }

    // Parse type 'int' | 'char' | 'boolean' | className(identifier)
    if(have("keyword", "int")){
        class_Var_Dec_Tree->addChild(mustBe("keyword", "int"));
    }
    else if(have("keyword", "char")){
        class_Var_Dec_Tree->addChild(mustBe("keyword", "char"));
    }
    else if(have("keyword", "boolean")){
        class_Var_Dec_Tree->addChild(mustBe("keyword", "boolean"));
    }
    else if(current()->getType() == "identifier"){
        std::string class_Name = current()->getValue();
        class_Var_Dec_Tree->addChild(mustBe("identifier", class_Name));
    }

    // Parse varName
    std::string var_Name = current()->getValue();
    class_Var_Dec_Tree->addChild(mustBe("identifier", var_Name));

    // Parse (',' varName)*
    while(have("symbol", ",")){

        // Parse ','
        class_Var_Dec_Tree->addChild(mustBe("symbol", ","));

        // Parse varName
        var_Name = current()->getValue();
        class_Var_Dec_Tree->addChild(mustBe("identifier", var_Name));

    }

    // Parse ';'
    class_Var_Dec_Tree->addChild(mustBe("symbol", ";"));

    return class_Var_Dec_Tree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {

    // Initialise sub_Tree
    ParseTree* sub_Tree = new ParseTree("subroutineDec", "");

    // Parse 'constructor' | 'function' | 'method'
    if(have("keyword", "constructor")){
        sub_Tree->addChild(mustBe("keyword", "constructor"));
    }
    else if(have("keyword", "function")){
        sub_Tree->addChild(mustBe("keyword", "function"));
    }
    else if(have("keyword", "method")){
        sub_Tree->addChild(mustBe("keyword", "method"));
    }

    // Parse 'void' | type ('int' | 'char' | 'boolean' | className(identifier)
    if(have("keyword", "void")){
        sub_Tree->addChild(mustBe("keyword", "void"));
    }
    else if(have("keyword", "int")){
        sub_Tree->addChild(mustBe("keyword", "int"));
    }
    else if(have("keyword", "char")){
        sub_Tree->addChild(mustBe("keyword", "char"));
    }
    else if(have("keyword", "boolean")){
        sub_Tree->addChild(mustBe("keyword", "boolean"));
    }
    else if(current()->getType() == "identifier"){
        std::string class_Name = current()->getValue();
        sub_Tree->addChild(mustBe("identifier", class_Name));
    }

    // Parse subroutineName
    std::string sub_Name = current()->getValue();
    sub_Tree->addChild(mustBe("identifier", sub_Name));

    // Parse '('
    sub_Tree->addChild(mustBe("symbol", "("));

    // Parse parameterList
    if(!have("symbol", ")")){
        sub_Tree->addChild(compileParameterList());
    }
    
    // Parse ')'
    sub_Tree->addChild(mustBe("symbol", ")"));

    // Parse subroutineBody
    sub_Tree->addChild(compileSubroutineBody());

    return sub_Tree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {

    // Initialise param_List_Tree
    ParseTree* param_List_Tree = new ParseTree("parameterList", "");

    // Parse type ('int' | 'char' | 'boolean' | className(identifier)
    if(have("keyword", "int")){
        param_List_Tree->addChild(mustBe("keyword", "int"));
        //std::cout << "first parameter passed\n";
    }
    else if(have("keyword", "char")){
        param_List_Tree->addChild(mustBe("keyword", "char"));
    }
    else if(have("keyword", "boolean")){
        param_List_Tree->addChild(mustBe("keyword", "boolean"));
    }
    else if(current()->getType() == "identifier"){
        std::string class_Name = current()->getValue();
        param_List_Tree->addChild(mustBe("identifier", class_Name));
    }

    // Parse varName
    std::string var_Name = current()->getValue();
    param_List_Tree->addChild(mustBe("identifier", var_Name));

    // Parse ((',' type varName)*)?
    // Only if ',' exists
    if(!have("symbol", ",")){
        return param_List_Tree;
    }

    // Parse (',' type varName) repeadtedly until ')'
    while(have("symbol", ",")){

        // Parse ','
        param_List_Tree->addChild(mustBe("symbol", ","));

        // Parse type
        if(have("keyword", "int")){
            param_List_Tree->addChild(mustBe("keyword", "int"));
            //std::cout << "first parameter passed\n";
        }
        else if(have("keyword", "char")){
            param_List_Tree->addChild(mustBe("keyword", "char"));
        }
        else if(have("keyword", "boolean")){
            param_List_Tree->addChild(mustBe("keyword", "boolean"));
        }
        else if(current()->getType() == "identifier"){
            std::string class_Name = current()->getValue();
            param_List_Tree->addChild(mustBe("identifier", class_Name));
        }

        // Parse varName
        std::string var_Name = current()->getValue();
        param_List_Tree->addChild(mustBe("identifier", var_Name));
    }
        
    return param_List_Tree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {

    // Initialise sub_Body_Tree
    ParseTree* sub_Body_Tree = new ParseTree("subroutineBody", "");

    // Parse '{'
    sub_Body_Tree->addChild(mustBe("symbol", "{"));
    
    // Parse varDec*
    while(have("keyword", "var")){
        sub_Body_Tree->addChild(compileVarDec());
    }

    // Parse statements
    sub_Body_Tree->addChild(compileStatements());

    // Parse '}'
    sub_Body_Tree->addChild(mustBe("symbol", "}"));

    return sub_Body_Tree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {

    // Initialise var_Dec_Tree
    ParseTree* var_Dec_Tree = new ParseTree("varDec", "");

    // Parse 'var'
    var_Dec_Tree->addChild(mustBe("keyword", "var"));

    // Parse type
    if(have("keyword", "int")){
        var_Dec_Tree->addChild(mustBe("keyword", "int"));
    }
    else if(have("keyword", "char")){
        var_Dec_Tree->addChild(mustBe("keyword", "char"));
    }
    else if(have("keyword", "boolean")){
        var_Dec_Tree->addChild(mustBe("keyword", "boolean"));
    }
    else if(current()->getType() == "identifier"){
        std::string class_Name = current()->getValue();
        var_Dec_Tree->addChild(mustBe("identifier", class_Name));
    }

    // Parse varName (identifier)
    std::string var_Name = current()->getValue();
    var_Dec_Tree->addChild(mustBe("identifier", var_Name));

    // Parse (',' varName)*
    while(!have("symbol", ";")){

        // Parse ','
        var_Dec_Tree->addChild(mustBe("symbol", ","));

        // Parse varName
        var_Name = current()->getValue();
        var_Dec_Tree->addChild(mustBe("identifier", var_Name));

    }

    // Parse ';'
    var_Dec_Tree->addChild(mustBe("symbol", ";"));

    return var_Dec_Tree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {

    // Initialise state_Tree
    ParseTree* state_Tree = new ParseTree("statements", "");

    // Parse let | if | while | do | return Statement
    while(have("keyword", "let")){
        state_Tree->addChild(compileLet());
    }
    while(have("keyword", "if")){
        state_Tree->addChild(compileIf());
    }
    while(have("keyword", "while")){
        state_Tree->addChild(compileWhile());
    }
    while(have("keyword", "do")){
        state_Tree->addChild(compileDo());
    }
    while(have("keyword", "return")){
        state_Tree->addChild(compileReturn());
    }

    return state_Tree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {

    // Initialise let_Tree
    ParseTree* let_Tree = new ParseTree("letStatement", "");

    // Parse 'let'
    let_Tree->addChild(mustBe("keyword", "let"));

    // Parse varName (identifier)
    std::string var_Name = current()->getValue();
    let_Tree->addChild(mustBe("identifier", var_Name));

    // Parse ('[' expression ']')?
    if(have("symbol", "[")){
        let_Tree->addChild(mustBe("symbol", "["));
        let_Tree->addChild(compileExpression());
        let_Tree->addChild(mustBe("symbol", "]"));
    }

    // Parse '='
    let_Tree->addChild(mustBe("symbol", "="));

    // Parse expression
    let_Tree->addChild(compileExpression());

    // Parse ';'
    let_Tree->addChild(mustBe("symbol", ";"));

    return let_Tree;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {

    // Initialise if_Tree
    ParseTree* if_Tree = new ParseTree("ifStatement", "");

    // Parse 'if'
    if_Tree->addChild(mustBe("keyword", "if"));

    // Parse '('
    if_Tree->addChild(mustBe("symbol", "("));

    // Parse expression
    if(!have("symbol", ")")){
        if_Tree->addChild(compileExpression());
    }
    
    // Parse ')'
    if_Tree->addChild(mustBe("symbol", ")"));

    // Parse '{'
    if_Tree->addChild(mustBe("symbol", "{"));

    // Parse statements
    if_Tree->addChild(compileStatements());

    // Parse '}'
    if_Tree->addChild(mustBe("symbol", "}"));

    // Parse ('else' '{' statements '}')?
    if(have("keyword", "else")){
        if_Tree->addChild(mustBe("keyword", "else"));
        if_Tree->addChild(mustBe("symbol", "{"));
        if_Tree->addChild(compileStatements());
        if_Tree->addChild(mustBe("symbol", "}"));
    }

    return if_Tree;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {

    // Initialise while_Tree
    ParseTree* while_Tree = new ParseTree("whileStatement", "");

    // Parse 'while'
    while_Tree->addChild(mustBe("keyword", "while"));

    // Parse '('
    while_Tree->addChild(mustBe("symbol", "("));

    // Parse expression
    while_Tree->addChild(compileExpression());

    // Parse ')'
    while_Tree->addChild(mustBe("symbol", ")"));

    // Parse '{'
    while_Tree->addChild(mustBe("symbol", "{"));

    // Parse statements
    while_Tree->addChild(compileStatements());

    // Parse '}'
    while_Tree->addChild(mustBe("symbol", "}"));

    return while_Tree;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {

    // Iniatialise do_Tree
    ParseTree* do_Tree = new ParseTree("doStatement", "");

    // Parse 'do'
    do_Tree->addChild(mustBe("keyword", "do"));

    // Parse subroutineCall
    do_Tree->addChild(compileExpression());

    // Parse ';'
    do_Tree->addChild(mustBe("symbol", ";"));

    return do_Tree;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {

    // Initialise return_Tree
    ParseTree* return_Tree = new ParseTree("returnStatement", "");

    // Parse 'return'
    return_Tree->addChild(mustBe("keyword", "return"));

    // Parse expression?
    if(!have("symbol", ";")){
        return_Tree->addChild(compileExpression());
    }

    // Parse ';'
    return_Tree->addChild(mustBe("symbol", ";"));

    return return_Tree;

}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {

    // Initialise exp_Tree
    ParseTree* exp_Tree = new ParseTree("expression", "");

    // Implement 'skip'
    if(current()->getValue() == "skip"){
        exp_Tree->addChild(mustBe("keyword", "skip"));
        return exp_Tree;
    }

    // Parse term
    exp_Tree->addChild(compileTerm());

    // Parse (op term)*
    std::string value;
    if(current() != NULL){
        value = current()->getValue();
    }

    while(value == "+" || value == "-" || value == "*" || value == "/" || value == "&" || value == "|" || value == "<" || value == ">" || value == "="){
        // Parse op
        exp_Tree->addChild(mustBe("symbol", value));
        
        // Parse term
        exp_Tree->addChild(compileTerm());

        if(current() == NULL || current()->getValue() == ")" || current()->getValue() == "]"){
            break;
        }
        value = current()->getValue();
    }
    return exp_Tree;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {

    // Initialise term_Tree
    ParseTree* term_Tree = new ParseTree("term", "");

    // Parse integerConstant
    if(current()->getType() == "integerConstant"){
        int value = std::stoi(current()->getValue());

        if((value >= 0) && (value <= 32767)){
            term_Tree->addChild(mustBe("integerConstant", std::to_string(value)));
            return term_Tree;
        }
        else{
            throw ParseException();
        }
    }

    // Parse stringConstant
    if(current()->getType() == "stringConstant"){
        std::string value = current()->getValue();
        term_Tree->addChild(mustBe("stringConstant", value));
        return term_Tree;
    }

    // Parse keywordConstant
    if(current()->getType() == "keyword"){
        std::string value = current()->getValue();
        term_Tree->addChild(mustBe("keyword", value));
        return term_Tree;
    }

    // Parse varName (identifier)
    if(current()->getType() == "identifier"){
        std::string value = current()->getValue();
        term_Tree->addChild(mustBe("identifier", value));

        // Parse varName '[' expression ']'
        if(have("symbol", "[")){
            term_Tree->addChild(mustBe("symbol", "["));
            term_Tree->addChild(compileExpression());
            term_Tree->addChild(mustBe("symbol", "]"));
        }

        // Parse subroutineCall
        if(have("symbol", "(") || have("symbol", ".")){
            if(have("symbol", "(")){
                term_Tree->addChild(mustBe("symbol", "("));
                term_Tree->addChild(compileExpressionList());
                term_Tree->addChild(mustBe("symbol", ")"));
            }
            else{
                term_Tree->addChild(mustBe("symbol", "."));
                term_Tree->addChild(mustBe("identifier", current()->getValue()));
                term_Tree->addChild(mustBe("symbol", "("));
                term_Tree->addChild(compileExpressionList());
                term_Tree->addChild(mustBe("symbol", ")"));
            }
            return term_Tree;
        }

        return term_Tree;
    }

    // Parse '(' expression ')'
    if(have("symbol", "(")){
        // Parse '('
        term_Tree->addChild(mustBe("symbol", "("));

        // Parse expression
        term_Tree->addChild(compileExpression());

        // Parse ')'
        term_Tree->addChild(mustBe("symbol", ")"));
        std::cout << ") parsed\n";

        return term_Tree;
    }

    // Parse unaryOp term
    if(have("symbol", "-") || have("symbol", "~")){
        term_Tree->addChild(mustBe("symbol", current()->getValue()));
        term_Tree->addChild(compileTerm());
        return term_Tree;
    }

    return term_Tree;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {

    // Initialise exp_List_Tree
    ParseTree* exp_List_Tree = new ParseTree("expressionList", "");

    if(current() != NULL || current()->getValue() != ")"){
        exp_List_Tree->addChild(compileExpression());
    }
    else{
        return exp_List_Tree;
    }

    while(current()->getValue() == ","){
        exp_List_Tree->addChild(mustBe("symbol", ","));
        exp_List_Tree->addChild(compileExpression());
        if(current() == NULL){
            break;
        }
    }
    return exp_List_Tree;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    this->current_token_index++;
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    Token* current_token;

    if(this->current_token_index < this->tokens.size()){
        std::list<Token*>::iterator it = tokens.begin();
        std::advance(it, this->current_token_index);
        current_token = *it;
    }
    else{
        return NULL;
    }
    return current_token;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){

    if(current() != NULL){
        if((current()->getType() == expectedType) && (current()->getValue() == expectedValue)){
            return true;
        }
    }
    
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    Token* return_token;

    if(have(expectedType, expectedValue)){
        return_token = current();
        next();
    }
    else{
        throw ParseException();
    }
    return return_token;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
