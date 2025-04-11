#ifndef PALINDROME_H
#define PALINDROME_H

#include <ostream>
#include <queue>
#include <stack>

using namespace std;

class Palindrome {
public:
    Palindrome(string sent) : sentence(sent) {};
    bool isPalindrome() const;
    friend ostream& operator<<(ostream &out, const Palindrome& p); // We use the address of P to save RAM.
private:
    string sentence;
    string stripSentence() const; // Const to ensure nothing gets modified. It means the functions it utilizes also doesn't modify anything.
};

// Removes all non letter parts of the sentence
string Palindrome::stripSentence() const {
    string clean = "";

    for (char c: sentence) {
        c = tolower(c);
        if (c >= 'a' && c <= 'z') {
            clean += c;
        }
    }

    return clean;
}

bool Palindrome::isPalindrome() const {
    string clean = stripSentence();
    stack<char> s;
    queue<char> q;

    for (char c: clean) {
        s.push(c);
        q.push(c);
    }

    while (!s.empty()) {
        if (s.top() != q.front()) {
            return false;
        }
        s.pop();
        q.pop();
    }

    return true;
}

ostream& operator<<(ostream &out, const Palindrome& p) {
    out << p.sentence << " is ";
    if (!p.isPalindrome()) {
        out << "not ";
    }
    out << "a palindrome!";

    return out;
}

#endif //PALINDROME_H
