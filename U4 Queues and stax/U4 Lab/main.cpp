#include <iostream>
#include "BracketCheck.h"

using namespace std;

bool check(string , string , bool );
bool checkNum(string, string, int);

int main() {
    cout << "test cases" << endl;
    check ("Easy", "()", true);
    check ("Not Matched", "(}", false);
    check ("Mixed but valid", "({}[])", true);
    check ("Too Many Closing", "({}[])]", false);
    check ("Not Matched", "({)(})", false);
    check ("Too Many Opening", "{()", false);
    check ("Code", "if (num == 7) { cout << num; }", true);

    checkNum("Number of brackets", "{}[]{}[", 7);

    return 0;
}

bool check(string name, string expression, bool shouldBe) {
    BracketCheck b(expression);

    if(shouldBe == b.isBalanced()){
        cout << "Passed: " << name << endl;
        return true;
    } else{
        cout << "Failed: " << name << " " << b << endl;
        return false;
    }
}

bool checkNum(string name, string expression, int shouldBe) {
    BracketCheck b(expression);

    if (shouldBe == b.numBrackets()) {
        cout << "Passed: " << name << endl;
        return true;
    } else {
        cout << "Failed: " << name << " " << b.numBrackets() << endl;
        return false;
    }
}
