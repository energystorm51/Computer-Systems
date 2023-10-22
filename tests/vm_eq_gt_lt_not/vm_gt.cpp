#include <string>
#include <iostream>

using namespace std;

string vm_gt(){
    string result = "";

    // pop a value off the stack and store in RAM[16]
    result = "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";
    result += "@TEMP\n";
    result += "M = D\n";       // RAM[16] = top value

    // pop second value off stack and compare
    result += "@SP\n";
    result += "AM = M - 1\n";
    result += "D = M\n";       // D-register stores second value
    result += "@TEMP\n";
    result += "D = D - M\n";   // D = second value - RAM[16] = second value - top value > 0
    result += "@GT\n";
    result += "D;JGT\n";     // jump to GT if D = 0

    // otherwise, push FALSE (0) onto stack
    result += "@0\n";
    result += "D = A\n";
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

int main(){
    string result = vm_gt();
    cout << result;
    return 0;
}