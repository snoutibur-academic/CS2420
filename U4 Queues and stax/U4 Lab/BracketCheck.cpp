#include "BracketCheck.h"

int BracketCheck::numBrackets() const {
    return exp.size();
}

bool BracketCheck::isBalanced() {
    stack<char> open;

    for (int i = 0; i < exp.size(); i++) {
        char c = exp[i];

        if ((c == '(') || (c == '{' )|| (c == '[')) {
                open.push(c);
        } else if (c == ')') {
            if (open.empty() || open.top() != '(') {
                return false;
            }
            open.pop();
        } else if (c == ']') {
            if (open.empty() || open.top() != '[') {
                return false;
            }
            open.pop();
        } else if (c == '}') {
            if (open.empty() || open.top() != '{') {
                return false;
            }
            open.pop();
        }
    }

    return open.empty();;
}

ostream &operator<<(ostream &out, BracketCheck &b) {
    if (b.isBalanced()) {
        out << "balanced ";
    } else {
        out << "not balanced ";
    }

    return out;
}
