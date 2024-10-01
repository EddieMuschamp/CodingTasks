#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int subCounter = 0;
        for(int i = 0; i < t.size(); i++){
            if(t[i] == s[subCounter]){
                subCounter++;
            }
        }
        return subCounter==s.size();
    }
};

int main(int argc, char const *argv[])
{
    string sub = "abc";
    string word = "afdgbsdfc";
    Solution test1;
    bool result;
    result = test1.isSubsequence(sub, word);
    cout<<result<<endl;
    return 0;
}

//Test
