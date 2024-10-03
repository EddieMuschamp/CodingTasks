#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
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

//########################################################################################################################################//

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

//########################################################################################################################################//

    vector<int> mergeSortedArray(vector<int>& nums1, int m, vector<int>& nums2, int n) {
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

//########################################################################################################################################//

    vector<int> arrayRankTransform(vector<int>& arr) {
        if(arr.size() == 0){return arr;}
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        map<int, int> arrMap;
        arrMap[sorted[0]] = 1;
        for (int i = 1; i < sorted.size(); i++) {
            if (sorted[i] > sorted[i - 1]) {
                arrMap[sorted[i]] = arrMap[sorted[i - 1]] + 1;
            }      
            else {
                arrMap[sorted[i]] = arrMap[sorted[i - 1]];
            }
        }
        vector<int> rank;
        for(int x : arr){
            rank.push_back(arrMap[x]);
        }
        return rank;
    }

//########################################################################################################################################//

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

//########################################################################################################################################//

    int removeDuplicates(vector<int>& nums) {
        nums.erase( unique( nums.begin(), nums.end() ), nums.end() );
        return nums.size();
    }

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

//########################################################################################################################################//

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

//########################################################################################################################################//

    bool isIsomorphic(string s, string t) {
        map<char, char> charMap;
        
        for (int i = 0; i < s.length(); i++){
            if(charMap.find(s[i]) == charMap.end()){
                for (auto& it : charMap) {
                    if (it.second == t[i]) {
                        return false;
                    }
                }
                charMap[s[i]] = t[i]; 
            }
            
            else if(t[i] != charMap[s[i]]){
                return false;
            }
        }
        return true;
    }

};

//########################################################################################################################################//

int main(int argc, char const *argv[])
{
    string s = "badc";
    string t = "baba";
    Solution test1;
    bool result;
    result = test1.isIsomorphic(s, t);
    cout<<result<<endl;
    return 0;
}
