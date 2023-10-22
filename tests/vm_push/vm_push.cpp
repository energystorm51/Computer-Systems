#include <string>
#include <iostream>

using namespace std;

string vm_push(string segment, int offset){

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

    // LOCAL
    if(segment == "local"){
        assembly = "@" + to_string(offset) + "\n";
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
        assembly = "@" + to_string(offset) + "\n";
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
        assembly = "@" + to_string(offset) + "\n";
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
        assembly = "@" + to_string(offset) + "\n";
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
        assembly = "@" + to_string(offset) + "\n";
        assembly += "D = A\n";
        assembly += "@TEMP\n";
        assembly += "A = M + D\n";
        assembly += "D = M\n";
        assembly += "@SP\n";
        assembly += "AM = M + 1\n";
        assembly += "A = A - 1\n";
        assembly += "M = D\n";
    }

    // POINTER
    if(segment == "pointer"){
        if(offset == 0){
            assembly = "@THIS\n";
            assembly += "D = M";
            assembly += "@SP\n";
            assembly += "AM = M + 1\n";
            assembly += "A = A - 1\n";
            assembly += "M = D\n";
        }
        else{
            assembly = "@THAT\n";
            assembly += "D = M";
            assembly += "@SP\n";
            assembly += "AM = M + 1\n";
            assembly += "A = A - 1\n";
            assembly += "M = D\n";
        }
    }

    return assembly;
}

int main(){
    string result = vm_push("local", 0);
    cout << result;
    return 0;
}