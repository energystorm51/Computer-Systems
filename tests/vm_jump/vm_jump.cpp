#include <string>
#include <iostream>

using namespace std;

string vm_label(string label){
    string result = "(";
    result += label;
    result += ")\n";
    return result;
}

/** Generate Hack Assembly code for a VM goto operation */
string vm_goto(string label){
    string result = "@";
    result += label;
    result += "\n";
    result += "0;JMP\n";
    return result;
}

/** Generate Hack Assembly code for a VM if-goto operation */
string vm_if(string label){
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

int main(){
    string result = vm_if("LOOP");
    cout << result;
    cout << vm_label("LOOP");
    cout << vm_goto("LOOP");
    return 0;
}