#include <string>
#include <iostream>

using namespace std;

string vm_eq(){
    string result = "";

    result = "@SP\n";
    result += "A = M - 1\n";
    result += "D = M\n";
    result += "D = !D\n";
    result += "M = D\n";

    return result;
}

int main(){
    string result = vm_eq();
    cout << result;
    return 0;
}