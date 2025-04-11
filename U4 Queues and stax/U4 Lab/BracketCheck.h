#ifndef BRACKETCHECK_H
#define BRACKETCHECK_H

#include <stack>
#include <iostream>

using namespace std;

class BracketCheck {
public:
    // Constructor
    BracketCheck(const string expression) {
        exp = expression;
    };

    void dispBrackets(); // for debugging constructor

    int numBrackets() const; // returns the number of pairs of brackets
    bool isBalanced(); // returns true if the brackets are balanced

    friend ostream & operator<< (ostream& out, BracketCheck& b); // output "Balanced" or "Not Balanced" based on the expression

private:
    string exp;
};

#endif //BRACKETCHECK_H