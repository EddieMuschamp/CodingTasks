#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        nums.erase( unique( nums.begin(), nums.end() ), nums.end() );
        if(nums.size()==0){return {};}
        vector<string> ranges;
        int lowNum = nums[0], highNum = nums[0], currentNum = nums[0];

        for(int i = 1; i < nums.size(); i++){
            
            if(currentNum + 1 == nums[i]){
                highNum++;
                currentNum++;
            }
            else{
                if(lowNum != highNum){
                    ranges.push_back(to_string(lowNum)+"->"+to_string(highNum));
                }
                else{
                    ranges.push_back(to_string(lowNum));
                }
                lowNum = nums[i], highNum = nums[i], currentNum = nums[i];
            }
        }
        if(lowNum != highNum){ranges.push_back(to_string(lowNum)+"->"+to_string(highNum));}
        else{ranges.push_back(to_string(lowNum));}
        
        return ranges;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums = {0,2,2,2,3,4,6,8,9};
     vector<string> ranges;
    Solution test1;
    ranges = test1.summaryRanges(nums);
    for(int i = 0; i < ranges.size();i++){
        cout<<ranges[i]<<"  ";
    }
    return 0;
}

//Test
