#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        nums.erase( unique( nums.begin(), nums.end() ), nums.end() );
        return nums.size();
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums = {0,2,2,2,3,4,6,8,9};
    Solution test1;
    int len;
    len = test1.removeDuplicates(nums);
    cout<<len<<endl;
    return 0;
}

//Test
