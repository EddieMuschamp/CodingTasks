#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
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
};

int main(int argc, char const *argv[]){
    vector<int> arr = {37,12,28,9,100,56,80,5,12};
    vector<int> rank;
    Solution test1;
    rank = test1.arrayRankTransform(arr);
    for (int i = 0; i < rank.size(); i++){
        cout<<rank[i]<<" ";
    }
    return 0;
}

//Test
