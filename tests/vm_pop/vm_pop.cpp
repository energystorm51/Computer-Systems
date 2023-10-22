#include <string>
#include <iostream>

using namespace std;

string vm_pop(string segment, int offset){

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

    // ARGUMENT
    if(segment == "argument"){
        assembly = "@";
        assembly += to_string(offset);
        assembly += "\n";
        assembly += "D = A\n"; 
        assembly += "ARG\n";
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
        assembly = "@";
        assembly += to_string(offset); 
        assembly += "\n";
        assembly += "D = A\n";
        assembly += "@TEMP\n";
        assembly += "D = M + D\n";
        assembly += "@R16\n";
        assembly += "M = D\n";
        assembly += "@SP\n";
        assembly += "AM = M - 1\n";
        assembly += "D = M\n";
        assembly += "@R16\n";
        assembly += "A = M\n";
        assembly += "M = D\n";
    }

    // POINTER
    if(segment == "pointer"){
        if(offset == 0){
            assembly = "@SP\n";
            assembly += "AM = M - 1\n";  // decrement SP
            assembly += "D = M\n";       // pop value onto D-register
            assembly += "@THIS\n";
            assembly += "M = D\n";       // store popped value into THIS
        }
        else{
            assembly = "@SP\n";
            assembly += "AM = M - 1\n";  // decrement SP
            assembly += "D = M\n";       // pop value onto D-register
            assembly += "@THAT\n";
            assembly += "M = D\n";       // store popped value into THAT
        }
    }

    return assembly;
}

int main(){
    string result = vm_pop("that", 1);
    cout << result;
    return 0;
}