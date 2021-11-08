## Arrays and Strings

### Arrays

#### Points to Remember
* Always check index before accessing
* How to traverse the array so that it is most efficient

### Max chunks to make sorted
```
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        // Since all values are from 0 to n-1
        // A chunk will be formed if max value in that chunk is equal to last index
        // Keep updating max index and check the condition
        int maxindex = INT_MIN;
        int ans = 0;
        for(int i=0; i<arr.size(); i++)
        {
            maxindex = max(maxindex, arr[i]);
            if(i == maxindex) ans++;
        }
        // Return ans
        return ans;
    }
};
```

### Max chunks to make sorted 2
```
class Solution {
public:
    // Custom min and max functions for long
    long int min(long int a, long int b) {return (a<b)?a:b;}
    long int max(long int a, long int b) {return (a>b)?a:b;}
        
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        // Max array represents max value upto index i
        // Min array represents min value from i to n-1
        vector<long int> minarr(n); vector<long int> maxarr(n);
        long int minofarr = INT_MAX; long int maxofarr = INT_MIN;
        // Fill the min array
        for(int i=n-1; i>=0; i--)
        {
            minofarr = min(minofarr, arr[i]);
            minarr[i] = minofarr;
        }
        // Fill the max array
        for(int i=0; i<n; i++)
        {
            maxofarr = max(maxofarr, arr[i]);
            maxarr[i] = maxofarr;
        }
        // If the max element upto me is smaller than smallest element of next index
        // Then i am the dividing point of 2 groups
        for(int i=0; i<n-1; i++) if(maxarr[i] <= minarr[i+1]) ans++;
        // Ans added for last array
        ans++;
        // Return ans
        return ans;
    }
};
```

### Segregate 0s 1s and 2s
```
class Solution
{
    public:
    void sort012(int a[], int n)
    {
        // i denotes first occurrence of 1
        // j is used for traversing
        // k denotes first occurrence of 2
        int i=0, j=0, k=n-1;
        // Equality condition because of error handling
        while(j<=k)
        {
            // If 1 simply move forward
            if(a[j] == 1) j++;
            // If 0, swap and advance pointers
            else if(a[j] == 0)
            {
                swap(a[i], a[j]);
                i++;
                j++;
            }
            // If 2 then swap and decrement k, but don't increment j
            // Because swap has taken place with an unknown element
            else
            {
                swap(a[j], a[k]);
                k--;
            }
        }
    }
};
```

### Sort array by parity
```
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int i=0, j=0;
        // i denotes first occurrence of odd elements
        // j is used for traversing
        while(j < A.size())
        {
            // If odd element simply increment pointers
            if(A[j] & 1) j++;
            // If even element then swap and advance pointers
            else
            {
                swap(A[i], A[j]);
                i++;
                j++;
            }
        }
        // Return array
        return A;
    }
};
```

### Two sum
```
class Solution{
public:	
	bool hasArrayTwoCandidates(int arr[], int n, int x) {
	    // Sort the array
	    sort(arr, arr+n);
	    // Two pointer approach
	    int i=0; int j=n-1;
	    // While we have 2 distinct elements
	    while(i<j)
	    {
	        // If two numbers match to target
	        if(arr[i]+arr[j] == x) return true;
	        // If they sum up to be greater then make the sum smaller
	        if(arr[i]+arr[j] > x) j--;
	        // Else make the sum larger
	        else i++;
	    }
	    // No such pair exists, return false
	    return false;
	}
};
```

### Two difference
```
bool findPair(int arr[], int size, int n){
    // Sort the array
    sort(arr, arr+size);
    int i=0, j=0;
    // Traverse on array
    while(i<size && j<size)
    {
        // If difference is equal to target
        if(arr[j]-arr[i] == n) return true;
        // Decrease the difference
        if(arr[j]-arr[i] > n) i++;
        // Increase the difference
        else j++;
    }
    return false;
}
```

### Boats to save people
```
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        // Each boat has to carry at most 2 people at the same time
        int ans=0, i=0, j=people.size()-1;
        // Sort the array
        sort(people.begin(), people.end());
        // i and j represents the 2 person that can travel together
        while(i<=j)
        {
            // If their combined weight is <= boat capacity then make them travel together
            if(people[i]+people[j] <= limit) i++;
            ans++;
            // Else let the heavier person travel
            j--;
        }
        // Return ans
        return ans;
    }
};
```

### Minimum no of platforms
```
class Solution{
    public:
    int findPlatform(int arr[], int dep[], int n)
    {
    	// For every arrival we just need to do platform++
        // And for every departure we do platform--
        // And keep competing with ans
        // We also need to sort both arrays independently 
        // As we are just concerned with time
    	int cmax=0, ans=INT_MIN, i=0, j=0;
    	sort(arr, arr+n);
    	sort(dep, dep+n);
    	// i will end first
    	while(i<n)
    	{
    	    // If there is arrival before or on departure
    	    // then increase curr no of platforms required
    	    if(arr[i]<=dep[j])
    	    {
    	        cmax++;
    	        i++;
    	    }
    	    // Else departure is before arrival 
    	    // then decrease curr no of platforms required
    	    else
    	    {
    	        cmax--;
    	        j++;
    	    }
    	    // Compete with ans every time
    	    ans = max(ans, cmax);
    	}
    	// Return ans
    	return ans;
    }
};
```

### First missing positive
```
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // Ans can only be in a range 1 to n
        // Traverse all elements and check if value is in correct range or not
        // If not in range do nothing
        // Else move it to correct index
        // Duplicacy - if element already present at an index, don't swap
        // After swapping stay at same index
        for(int i=0; i<nums.size(); i++)
        {
            if(nums[i]>=1 && nums[i]<=nums.size())
            {
                if(nums[nums[i]-1] != nums[i])
                {
                    swap(nums[i], nums[nums[i]-1]);
                    i--;
                }
            }
        }
        // Return the first person that is not equal to i+1
        for(int i=0; i<nums.size(); i++)
        {
            if(nums[i] != i+1) return i+1;
        }
        return nums.size()+1;
    }
};
```

### Strings

### Shortest Palindrome (KMP Algorithm)
```
class Solution {
public:
    string shortestPalindrome(string s) {
        /*
            KMP Algorithm
        */
        string temp = s;
        reverse(temp.begin(), temp.end());
        string s1 = s;
        s1.push_back('#');
        s1 += temp;
        vector<int> lps(s1.size(), 0);
        int i = 1; int len = 0;
        while(i<s1.size())
        {
            if(s1[i]==s1[len])
            {
                len++;
                lps[i]=len;
                i++;
            }
            else
            {
                if(len>0) len = lps[len-1];
                else{lps[i]=0; i++;}
            }
        }
        int num = lps[lps.size()-1];
        string ans;
        for(int i=num; i<s.size(); i++) ans.push_back(s[i]);
        reverse(ans.begin(), ans.end());
        ans += s;
        return ans;
    }
};
```

#### Points to Remember