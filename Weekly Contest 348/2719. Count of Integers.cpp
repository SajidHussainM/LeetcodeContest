/*

You are given two numeric strings num1 and num2 and two integers max_sum and min_sum. We denote an integer x to be good if:

num1 <= x <= num2
min_sum <= digit_sum(x) <= max_sum.
Return the number of good integers. Since the answer may be large, return it modulo 109 + 7.

Note that digit_sum(x) denotes the sum of the digits of x.

 

Example 1:

Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
Output: 11
Explanation: There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.
Example 2:

Input: num1 = "1", num2 = "5", min_sum = 1, max_sum = 5
Output: 5
Explanation: The 5 integers whose sum of digits lies between 1 and 5 are 1,2,3,4, and 5. Thus, we return 5.
 

Constraints:

1 <= num1 <= num2 <= 1022
1 <= min_sum <= max_sum <= 400


*/


class Solution {
    public:
        
        int mod = 1e9+7;
public:
    int getDigitSum(string str){
        int sum = 0;

        for(int i=0; i<str.length(); i++)
            sum += str[i]-'0';

        return sum;
    }

    int solve(string num, int minSum, int maxSum, int tight, int currSum, int index,
    vector<vector<vector<int>>> &dp){
        if(index == num.length()){
            return (currSum>=minSum && currSum<=maxSum) ? 1 : 0;
        }

        if(dp[index][currSum][tight] != -1) return dp[index][currSum][tight];

        int ans = 0;
        int end = (tight == 1)? num[index]-'0' : 9;

        for(int curr=0; curr<=end; curr++){
            int newTight = (tight==1 && curr==end) ? 1 : 0 ;
            ans = ans + solve(num,minSum,maxSum,newTight,currSum+curr,index+1,dp);
            ans %= mod;
        }

        return dp[index][currSum][tight] = ans;
        
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        int n1 = num1.length() , n2 = num2.length();
        vector<vector<vector<int>>> dp(30, vector<vector<int>> (401,vector<int>(2,-1)));

        int ans = solve(num2,min_sum,max_sum,1,0,0,dp);

        for(int i=0; i<30; i++){
            for(int j = 0; j<401; j++){
                for(int k=0; k<2; k++){
                    dp[i][j][k] = -1;
                }
            }
        }

         ans -= solve(num1,min_sum,max_sum,1,0,0,dp);


        int dig = getDigitSum(num1);

        if(dig>=min_sum && dig<=max_sum) ans++;

        ans %=  mod;

        return (ans + mod ) % mod;


    }
};
