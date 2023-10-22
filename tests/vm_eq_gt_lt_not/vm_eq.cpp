#include <string>
#include <iostream>

using namespace std;

string vm_eq(){
    string result = "";

    // pop a value off the stack and store in RAM[16]
    result = "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";
    result += "@TEMP\n";
    result += "M = D\n";       // RAM[16] = 3

    // pop 3 off stack and compare
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";       // D-register stores 3
    result += "@TEMP\n";
    result += "D = D - M\n";   // D = 3 - RAM[16] = 3 - 3 = 0
    result += "@EQUAL\n";
    result += "D;JEQ\n";     // jump to EQUAL if D = 0

    // otherwise, push FALSE (0) onto stack
    result += "@0\n";
    result += "D = A\n";
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

int main(){
    string result = vm_eq();
    cout << result;
    return 0;
}