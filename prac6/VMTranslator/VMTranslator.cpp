#include <string>
#include <sstream>
#include <iostream>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){

    string assembly = "";

    // CONSTANT
    if(segment == "constant"){
        assembly = "@";
        assembly += to_string(offset); 
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // STATIC
    if(segment == "static"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@16\n";
        assembly += "A = A + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // LOCAL
    if(segment == "local"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@LCL\n";
        assembly += "A = M + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // ARGUMENT
    if(segment == "argument"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@ARG\n";
        assembly += "A = M + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // THIS 
    if(segment == "this"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@THIS\n";
        assembly += "A = M + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // THAT
    if(segment == "that"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@THAT\n";
        assembly += "A = M + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // TEMP
    if(segment == "temp"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@5\n";
        assembly += "A = A + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // POINTER
    if(segment == "pointer"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@3\n";
        assembly += "A = A + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    return assembly;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){    
    string assembly = "";

    // LOCAL
    if(segment == "local"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n"; 
        assembly += "@LCL\n";
        assembly += "D = D + M\n";
        assembly += "@TEMP\n";
        assembly += "M = D\n";       // store the dest. local address in TEMP
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";  // decrement SP
        assembly += "D = M\n";       // pop value onto D-register
        assembly += "@TEMP\n";
        assembly += "A = M\n";       // load address at TEMP onto A-register
        assembly += "M = D\n";       // store popped value into LCL offset
    }

    // STATIC
    if(segment == "static"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n"; 
        assembly += "@16\n";
        assembly += "D = D + A\n";
        assembly += "@TEMP\n";
        assembly += "M = D\n";       // store the dest. argument address in TEMP
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";  // decrement SP
        assembly += "D = M\n";       // pop value onto D-register
        assembly += "@TEMP\n";
        assembly += "A = M\n";       // load address at TEMP onto A-register
        assembly += "M = D\n";       // store popped value into STATIC offset
    }

    // ARGUMENT
    if(segment == "argument"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n"; 
        assembly += "@ARG\n";
        assembly += "D = D + M\n";
        assembly += "@TEMP\n";
        assembly += "M = D\n";       // store the dest. argument address in TEMP
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";  // decrement SP
        assembly += "D = M\n";       // pop value onto D-register
        assembly += "@TEMP\n";
        assembly += "A = M\n";       // load address at TEMP onto A-register
        assembly += "M = D\n";       // store popped value into ARG offset
    }

    // THIS 
    if(segment == "this"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n"; 
        assembly += "@THIS\n";
        assembly += "D = D + M\n";
        assembly += "@TEMP\n";
        assembly += "M = D\n";       // store the dest. this address in TEMP
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";  // decrement SP
        assembly += "D = M\n";       // pop value onto D-register
        assembly += "@TEMP\n";
        assembly += "A = M\n";       // load address at TEMP onto A-register
        assembly += "M = D\n";       // store popped value into THIS offset
    }

    // THAT
    if(segment == "that"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n"; 
        assembly += "@THAT\n";
        assembly += "D = D + M\n";
        assembly += "@TEMP\n";
        assembly += "M = D\n";       // store the dest. THAT address in TEMP
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";  // decrement SP
        assembly += "D = M\n";       // pop value onto D-register
        assembly += "@TEMP\n";
        assembly += "A = M\n";       // load address at TEMP onto A-register
        assembly += "M = D\n";       // store popped value into THAT offset
    }

    // TEMP
    if(segment == "temp"){
        /*
        @TEMP
        "D=M";
        @offset;
        D=D+A;
        */

        assembly = "@5\n";
        assembly += "D = A\n";
        assembly += "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A + D\n";
        assembly += "@13\n";
        assembly += "M = D\n";
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";
        assembly += "D = M\n";
        assembly += "@13\n";
        assembly += "A = M\n";
        assembly += "M = D\n";
    }

    // POINTER
    if(segment == "pointer"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n"; 
        assembly += "@3\n";
        assembly += "D = D + A\n";
        assembly += "@TEMP\n";
        assembly += "M = D\n";       // store the dest. argument address in TEMP
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";  // decrement SP
        assembly += "D = M\n";       // pop value onto D-register
        assembly += "@TEMP\n";
        assembly += "A = M\n";       // load address at TEMP onto A-register
        assembly += "M = D\n";       // store popped value into POINTER offset
    }

    return assembly;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    string result = "";

    // pop a value off the stack and store in RAM[16]
    result = "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";
    result += "@TEMP\n";
    result += "M = D\n";       // RAM[16] = D

    // pop 2 off stack and calculate sum
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";       // D-register stores second value
    result += "@TEMP\n"; 
    result += "D = D + M\n";   // D = value + RAM[16] 

    // push sum onto stack
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";

    return result;
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    string result = "";

    // pop a value off the stack and store in RAM[16]
    result = "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";

    // pop second value off stack and compare
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M - D\n";        // D = second value - top value  
    result += "@EQUAL\n";
    result += "D;JEQ\n";     // jump to EQUAL if D = 0

    // otherwise, push FALSE (0) onto stack
    result += "D = 0\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";
    result += "@END\n";
    result += "0;JMP\n";

    result += "(EQUAL)\n";
    // push TRUE (-1) onto stack
    result += "@EQUAL\n";
    result += "D = -1\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";
    result += "@END\n";
    result += "0;JMP\n";

    return result;
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    string result = "";

    // pop a value off the stack and store in RAM[16]
    result = "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";

    // pop second value off stack and compare
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M - D\n";        // D = second value - top value  
    result += "@GT\n";
    result += "D;JGT\n";     // jump to GT if D > 0

    // otherwise, push FALSE (0) onto stack
    result += "D = 0\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";
    result += "@END\n";
    result += "0;JMP\n";

    result += "(GT)\n";
    // push TRUE (-1) onto stack
    result += "@GT\n";
    result += "D = -1\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";
    result += "@END\n";
    result += "0;JMP\n";

    return result;
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    string result = "";

    // pop a value off the stack and store in RAM[16]
    result = "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";

    // pop second value off stack and compare
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M - D\n";        // D = second value - top value  
    result += "@LT\n";
    result += "D;JLT\n";     // jump to LT if D < 0

    // otherwise, push FALSE (0) onto stack
    result += "D = 0\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";
    result += "@END\n";
    result += "0;JMP\n";

    result += "(LT)\n";
    // push TRUE (-1) onto stack
    result += "@LT\n";
    result += "D = -1\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";
    result += "@END\n";
    result += "0;JMP\n";

    return result;
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    string result = "";

    result = "@SP\n";
    result += "A = M - 1\n";
    result += "D = M\n";
    result += "D = !D\n";
    result += "M = D\n";

    return result;
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    string result = "(";
    result += label;
    result += ")\n";
    return result;
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    string result = "@";
    result += label;
    result += "\n";
    result += "0;JMP\n";
    return result;
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    string result = "";

    // pop top value off stack
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";       // D-register stores top value

    // jump to END if D = FALSE (0)
    result += "@";
    result += label;
    result += "\n";
    result += "D;JNE\n";

    return result;
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string result = "(";
    result += function_name;
    result += ")\n";

    /*
    while(counter < n_vars){
        push constant 0
    }
     */

    for(int i = n_vars; i > 0; i--){
        result += "@SP\n";
        result += "AM = M + 1\n";
        result += "A = A - 1\n";
        result += "M = 0\n";
    }

    return result;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    string result = "";

    // push return-address onto the stack
    result = "@RETURN\n";
    result += "D = A\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";

    // save LCL of calling function
    result += "@LCL\n";
    result += "D = M\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";

    // save ARG of calling function
    result += "@ARG\n";
    result += "D = M\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";

    // save THIS of calling function
    result += "@THIS\n";
    result += "D = M\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";

    // save THAT of calling function
    result += "@THAT\n";
    result += "D = M\n";
    result += "@SP\n";
    result += "AM = M + 1\n";
    result += "A = A - 1\n";
    result += "M = D\n";

    // reposition ARG (n = number of arguments)
    result += "@SP\n";
    result += "D = M\n";
    result += "@5\n";
    result += "D = D - A\n";
    result += "@";
    result += to_string(n_args);
    result += "\n";
    result += "D = D - A\n";
    result += "@ARG\n";
    result += "M = D\n";

    // reposition LCL
    result += "@SP\n";
    result += "D = M\n";
    result += "@LCL\n";
    result += "M = D\n";

    // transfer control
    result += "@";
    result += function_name;
    result += "\n";
    result += "0;JMP\n";

    // declare label for return-address
    result += "(RETURN)\n";

    return result;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    string result = "";

    // set temporary RAM[13] to LCL
    result += "@LCL\n";
    result += "D = M\n";
    result += "@R13\n";
    result += "M = D\n";

    // store return-address in temporary RAM[14]
    result += "@R13\n";
    result += "D = M\n";
    result += "@5\n";
    result += "A = D - A\n";
    result += "D = M\n";
    result += "@R14\n";
    result += "M = D\n";

    // reposition return value for caller
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";
    result += "@ARG\n";
    result += "A = M\n";
    result += "M = D\n";

    // restore SP of caller
    result += "@ARG\n";
    result += "D = M + 1\n";
    result += "@SP\n";
    result += "M = D\n";

    // restore THAT of caller
    result += "@R13\n";
    result += "A = M - 1\n";
    result += "D = M\n";
    result += "@THAT\n";
    result += "M = D\n";

    // restore THIS of caller
    result += "@R13\n";
    result += "D = M\n";
    result += "@2\n";
    result += "A = D - A\n";
    result += "D = M\n";
    result += "@THIS\n";
    result += "M = D\n";

    // restore ARG of caller
    result += "@R13\n";
    result += "D = M\n";
    result += "@3\n";
    result += "A = D - A\n";
    result += "D = M\n";
    result += "@ARG\n";
    result += "M = D\n";

    // restore LCL of caller
    result += "@R13\n";
    result += "D = M\n";
    result += "@4\n";
    result += "A = D - A\n";
    result += "D = M\n";
    result += "@LCL\n";
    result += "M = D\n";

    // goto return-address
    result += "@R14\n";
    result += "A = M\n";
    result += "0;JMP\n";

    return result;
}