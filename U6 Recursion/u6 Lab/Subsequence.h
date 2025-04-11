#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#include <iostream>

using namespace std;

class Subsequence {
public:
    Subsequence(string word) : word(word) {}; // Add a constructor that takes only a single word argument
    bool isSubsequence(string &sub); // Add a bool isSubsequence(string sub); a method that will return true if sub is a subsequence of the original word. This is the helper function.
    bool isSubsequence(string sub, int subPos, int wordPos); // This does the recursion.
    friend ostream& operator<< (ostream &out, Subsequence &s); // Overload the operator<< using a friend function, such that information is given about the class. This will be used for your own debugging
private:
    string word;
};

#endif //SUBSEQUENCE_H

inline bool Subsequence::isSubsequence(string &sub) {
    return isSubsequence(sub, 0, 0);
}

inline bool Subsequence::isSubsequence(string sub, int subPos, int wordPos) {
    // BASE CASES (needs 2)//
    // Everything has been checked
    if(subPos >= sub.size()) {
        return true;
    }

    // Avoid going out of bounds
    if (wordPos >= word.size()) {
        return false;
    }

    // RECURSIVE CASES //
    // Matching pair found
    if (word[wordPos] == sub[subPos]) {
        return isSubsequence(sub, subPos + 1, wordPos + 1);
    } else {
        return isSubsequence(sub, subPos, wordPos + 1);

    }
}

inline ostream& operator << (ostream& out, Subsequence &s) {
    out << "word: " + s.word << endl;
    return out;
}