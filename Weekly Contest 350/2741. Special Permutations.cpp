/*

2741. Special Permutations
User Accepted:2224
User Tried:7608
Total Accepted:2438
Total Submissions:18661
Difficulty:Medium
You are given a 0-indexed integer array nums containing n distinct positive integers. A permutation of nums is called special if:

For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or nums[i+1] % nums[i] == 0.
Return the total number of special permutations. As the answer could be large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [2,3,6]
Output: 2
Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.
Example 2:

Input: nums = [1,4,3]
Output: 2
Explanation: [3,1,4] and [4,1,3] are the two special permutations of nums.
 

Constraints:

2 <= nums.length <= 14
1 <= nums[i] <= 109

*/


class Solution {
    public : 
    int mod = 1000000007;
        int solve(vector<int>& nums, int prevInd, int currentIndex, int mask, vector<vector<int>>& dp){
            if(currentIndex == nums.size()) return 1;
            
            if(dp[prevInd+1][mask] != -1) return dp[prevInd+1][mask];
            
            int ans = 0 ;
            
            for(int j=0; j<nums.size(); j++){
                if( (mask & (1<<j)) > 0 ) continue;
                
                if(prevInd == -1 ||  nums[prevInd]%nums[j] == 0 || nums[j]%nums[prevInd] == 0){
                    ans = (ans + solve(nums,j,currentIndex+1,mask|(1<<j),dp)) % mod;
                }
            }
            
            return dp[prevInd+1][mask] = ans;
        }
    
public:
    int specialPerm(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int> (1<<14+1,-1));
        
        return solve(nums,-1,0,0,dp);
        
    }
};
