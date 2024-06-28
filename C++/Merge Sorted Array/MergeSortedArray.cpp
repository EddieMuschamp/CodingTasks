#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (n == 0)
            return nums1;
        if (m == 0) {
            nums1 = nums2;
            return nums1;
        }
        int totalLen = nums1.size();
        while (n > 0 && m > 0) {
            if (nums1[m - 1] >= nums2[n - 1]) {
                nums1[totalLen - 1] = nums1[m - 1];
                m--;
            } else {
                nums1[totalLen - 1] = nums2[n - 1];
                n--;
            }
            totalLen--;
        }
        while (n > 0) {
            nums1[totalLen-1] = nums2[n-1];
            n--;
            totalLen--;
        }
        return nums1;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums1 = {2, 3, 8, 10, 0, 0, 0};
    int m = 4;
    vector<int> nums2 = {3, 7, 11};
    int n = 3;
    Solution test1;
    nums1 = test1.merge(nums1, m, nums2, n);
    for(int i = 0; i < nums1.size(); i++){
        cout<<nums1[i]<<",";
    }
    return 0;
}

//Test
