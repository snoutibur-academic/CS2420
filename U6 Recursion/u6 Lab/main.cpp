#include <iostream>
#include "Subsequence.h"

using namespace std;

void checkCase(string, string, string, bool);

int main()
{
    /**
        Add several more test cases to thoroughly test your data
        checkCase takes the following parameters (name, word, possible subsequence, true/false it would be a subsequence)
    **/
    checkCase("Case: First Letter", "pin", "programming", true);
    checkCase("Case: Skipping Letters", "ace", "abcde", true);
    checkCase("Case: Out of order", "bad", "abcde", false);
    checkCase("Case: Spaces", "sad sam", "salad samon", true);
    checkCase("Case: Backwards", "god", "dog", false);
    checkCase("Case: Backwards 2", "speedrun", "nurdeeps", false);

    return 0;
}


void checkCase(string testCaseName, string sub, string sentence, bool correctResponse){
    Subsequence s(sentence);
    if(s.isSubsequence(sub) == correctResponse){
        cout << "Passed " << testCaseName << endl;
    }
    else{
        cout << "Failed " << testCaseName << ": " << sub << " is " << (correctResponse? "": "not ") << "a subsequence of " << sentence << endl;
    }
}
