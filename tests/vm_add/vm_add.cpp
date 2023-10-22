#include <string>
#include <iostream>

using namespace std;

string vm_add(){
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

int main(){
    string result = vm_add();
    cout << result;
    return 0;
}