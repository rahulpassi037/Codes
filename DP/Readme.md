## Dynamic Programming

### LIS (n^2)
```
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        /*
            Q. Find length of longest increasing subsequence in  array
            
            We create a new LIS array of size n and initialize it to all 1s
            Then do O(n^2) traversal and fill the array if LIS[j] < LIS[i]
            LIS[i] = max(LIS[i], 1+LIS[j])
            Then find the max value in the array
        */
        vector<int> lis(nums.size(), 1);
        for(int i=1; i<nums.size(); i++)
        {
            for(int j=0; j<i; j++)
            {
                if(nums[j]<nums[i]) lis[i] = max(lis[i], 1+lis[j]);
            }
        }
        int ans = 0;
        for(int i=0; i<nums.size(); i++) if(lis[i]>ans) ans = lis[i];
        return ans;
    }
};
```

### LIS (nlogn)
```
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        /*
            Q. This is an O(nlogn) approach for finding LIS, we cannot find actual LIS, only length
            
            We create a new LIS array and traverse over all elements and find the correct position
            they can be inserted into and then insert them
            A new number can make existing LIS better or can increase length of LIS
            Keep updating the ans whenever the length increases
        */
        int ans = 0;
        int n = nums.size();
        vector<int> lis(n, 0);
        for(int i=0; i<n; i++)
        {
            int lo=0, hi=ans;
            while(lo<hi)
            {
                int mid = lo + (hi-lo)/2;
                if(lis[mid]<nums[i]) lo = mid+1;
                else hi = mid;
            }
            lis[lo] = nums[i];
            if(lo==ans) ans++;
        }
        return ans;
    }
};
```

### Gap Strategy
```
for(int gap=1; gap<n; gap++)
{
    for(int left=0; left<n-gap; left++)
    {
        int right = left+gap;
        // Fill the table
    }
}
```

### Egg dropping approach 1
```
class Solution
{
    public:
    /*
        Q. Min no of moves to determine the critical floor
        
        Approach - dp[i][j] stores ans when there are i eggs and j floors
        
        Base cases
        When there is 0 egg, min no of moves is 0
        When there is 1 egg, min no of moves = no of floors
        When there are 0 floors, then min no of moves = 0
        When there is 1 floor, then min no of moves = 0
        
        We try to find worst case of all entries and then find the min
    */
    int eggDrop(int n, int k) 
    {
        int dp[n+1][k+1];
        for(int i=0; i<=k; i++) dp[0][i] = 0;
        for(int i=1; i<=k; i++) dp[1][i] = i;
        for(int i=0; i<=n; i++) dp[i][0] = 0;
        for(int i=1; i<=n; i++) dp[i][1] = 1;
        
        for(int i=2; i<=n; i++)
        {
            for(int j=2; j<=k; j++)
            {
                dp[i][j] = INT_MAX;
                for(int x=1; x<=j; x++)
                {
                    int temp = max(dp[i][j-x], dp[i-1][x-1])+1;
                    dp[i][j] = min(dp[i][j], temp);
                }
            }
        }
        return dp[n][k];
    }
};
```

### Egg dropping approach 2
```
class Solution
{
    public:
    /*
        Q. Find min no of moves to find the critical floor
        
        dp[i][j] denotes no of floors for which we can find the ans
        when there are i no of moves and j no of eggs
    */
    int eggDrop(int n, int k) 
    {
        int dp[k][n];
        for(int i=0; i<n; i++) dp[0][i] = 1;
        for(int i=0; i<k; i++) dp[i][0] = i+1;
        for(int i=1; i<k; i++)
        {
            for(int j=1; j<n; j++)
            {
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + 1;
                if(dp[i][j] >= k) return i+1;
            }
        }
        return k;
    }
};
```

### LCS
```
class Solution {
public:
    /*
        Q. Find longest common subsequence of given 2 strings
        
        Approach
        Base cases - If any of the 2 strings is of length 0, then length of LCS is 0
        If characters match for both strings then we call recursively for i-1, j-1
        Else we take max of i-1, j and i, j-1
        Ans is dp[m][n]
    */
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        int dp[m+1][n+1];
        
        for(int i=0; i<=n; i++) dp[0][i] = 0;
        for(int i=0; i<=m; i++) dp[i][0] = 0;
        
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(text1[i-1] == text2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        
        return dp[m][n];
    }
};
```

### Longest Palindromic subsequence
```
class Solution {
public:
    /*
        Q. Find length of longest palindromic subsequence
        
        Approach - String is length 1 is palindrome and its length is 1
        We check is characters match, then do 2+(i-1, j-1)
        Else take max(i+1, j) and (i, j-1)
    */
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        int dp[n][n];
        
        for(int i=1; i<n; i++) dp[i][i-1] = 0;
        for(int i=0; i<n; i++) dp[i][i] = 1;
        
        for(int gap=1; gap<n; gap++)
        {
            for(int left=0; left<n-gap; left++)
            {
                int right = left+gap;
                if(s[left] == s[right]) dp[left][right] = 2 + dp[left+1][right-1];
                else dp[left][right] = max(dp[left+1][right], dp[left][right-1]);
            }
        }
        
        return dp[0][n-1];
    }
};
```

### Edit distance
```
class Solution {
public:
    /*
        Q. Given 2 strings, we need to find min no of operations to convert one string to another
        
        Approach - For strings of length 0, we need i no of operations to convert strings
        For bigger strings : If characters match, we call for i-1, j-1
        Else we take min of insert, delete and replace operations and add 1
    */
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        int dp[m+1][n+1];
        
        for(int i=0; i<=n; i++) dp[0][i] = i;
        for(int i=0; i<=m; i++) dp[i][0] = i;
        
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
                else dp[i][j] = 1 + min(dp[i][j-1], min(dp[i-1][j], dp[i-1][j-1]));
            }
        }
        
        return dp[m][n];
    }
};
```