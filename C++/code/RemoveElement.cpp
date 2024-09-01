#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        for(int i = 0; i < nums.size(); i++){
            if (nums[i] == val){
                //cout<<nums[i]<<endl;
                swap(nums[i], nums[nums.size()-1]);
                nums.pop_back();
                i--;
            }
        } 
        return nums.size();
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums = {2, 3, 8, 10, 3, 9, 3};
    int val = 3;
    Solution test1;
    int output = test1.removeElement(nums, val);
    cout<<output<<endl;
}
