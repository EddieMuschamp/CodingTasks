#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string forward = "";
        string reverse = "";
        string letter;
        for (int i = s.size()-1; i >= 0; i--) {
            letter = tolower(s[i]);
            if ((s[i] >= 'a' && s[i] <= 'z')
            ||(s[i] >= 'A' && s[i] <= 'Z')
            ||(s[i] >= '0' && s[i] <= '9')) {
                forward.insert(0, letter);
                reverse.append(letter);
            }
        }
        if(forward == reverse){
            return true;
        }
        else{
            return false;
        }
    }
};

int main(int argc, char const *argv[])
{
    string s = "A man, a plan, a canal: Panama";
    Solution test1;
    cout<<boolalpha<<test1.isPalindrome(s)<<endl;
    return 0;
}
