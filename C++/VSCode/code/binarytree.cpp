#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        for(int i = 0; i < ransomNote.length(); i++){
            size_t found = magazine.find(ransomNote[i]);
            if (found != string::npos){
                magazine.erase(found,1);
            }
            else{
                cout<<"no";
                return false;
            }
        }
        cout<<"yes";
        return true;
    }
};

int main(int argc, char const *argv[])
{
    string ransom = "ghjkl";
    string magazine = "gghglplpjl";
    Solution test1;
    test1.canConstruct(ransom, magazine);
    return 0;
}

//Test
