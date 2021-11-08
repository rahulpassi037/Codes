## Hashmap, Heap, Searching, Sorting

### Subarray sum equals K
```
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        /*
            Q. We need to find total number of continuous subarrays with sum == k
            
            If all positive -> sliding window
            
            Create prefix sum array
            If sum of subarray from i to j == k
            Then prefixsum(j) - prefixsum(i-1) == k
            
            Or prefixsum(i-1) == prefixsum(j) - k
            Also there is subarray if prefixsum(i) == k, so push 0 in map
            For whichever prefixsum i and j, the above condition is satisfied ans++
            O(n^2) approach
            
            In hashmap keep putting prefixsum(i) (start point, for future ans)
            If prefixsum(i)-k exists in map add it (how many starting points can i be added to)
            map has mapping of prefisum -> no of occurences
        */
        
        int ans = 0;
        vector<int> prefixsum(nums.size(), 0);
        unordered_map<int, int> m;
        
        prefixsum[0]=nums[0];
        for(int i=1; i<nums.size(); i++) prefixsum[i]=prefixsum[i-1]+nums[i];
        
        m[0] = 1;
        for(int i=0; i<prefixsum.size(); i++)
        {
            ans += m[prefixsum[i]-k];
            m[prefixsum[i]]++;
        }
        
        return ans;
    }
};
```

### Subarray sum divisible by K
```
class Solution{

	public:
	long long subCount(long long arr[], int N, long long K)
	{
	    /*
	        Q. We need to count all subarrays where subarray sum is divisible by k
	        
	        If subarray[i..j] is divisible by k
	        Create a prefix array for the array
	        
	        Then, (prefixsum(j) - prefixsum(i-1)) % k ==  0    -   1
	        PS(j) = q1*k + r1
	        PS(i-1) = q2*k + r2
	        Therefore 1 can be reduced to (r1-r2)%k == 0
	        r1 = PS(j)%k and r2 = PS(i-1)%k
	        PS(j)%k - PS(i-1)%k == 0
	        PS(j) == PS(i-1)
	        
	        Create prefixsum % k array, check how negative numbers were handled
	        
	        Keep pushing prefixsum(i) to map and keep adding to ans
	        We also need to add for case where prefixsum(i) % k == 0
	        In that case add m[0] = 1
	    */
	    long long cs[N];
	    long long ans = 0;
	    unordered_map<int,int> m;
	    
	    
	    cs[0] = arr[0]%K;
	    for(int i=1; i<N; i++) 
	    {
	        cs[i] = (cs[i-1] + arr[i]) % K;
	        if(cs[i] < 0) cs[i] += K;
	    }
	    if(cs[0] < 0) cs[0] += K;
	    
	    m[0] = 1;
	    for(int i=0; i<N; i++)
	    {
            ans += m[cs[i]];
            m[cs[i]]++;
	    }
	    
	    return ans;
	}
};
```

### Subarrays with equal no of 0, 1 and 2
```
class Solution {
  public:
    long long getSubstringWithEqual012(string str) {
        /*
        Q. We need to count number of subarrays with equal number of 0s, 1s and 2s
            
        Consider a subarray i+1 to j, we can say that a subarray with equal
        no of 0s, 1s and 2s exists between them if 
        (prefixcount of 1s - prefixcount of 0s) at index i equals to 
        (prefixcount of 1s - prefixcount of 0s) at index j
        (prefixcount of 2s - prefixcount of 0s) at index i equals to 
        (prefixcount of 2s - prefixcount of 0s) at index j
        Net growth of all numbers was cancelled by each other
        
        We just keep 3 variables countof0, countof1 and countof2 and keep counting 
        the difference in map by making a pair
        Also we need to handle case when subarray[0-i] has equal no of 0s, 1s and 2s
        Keep adding the count of same values to ans
    */
        long long ans = 0;
        int zc = 0, oc = 0, tc = 0, n = str.size();
        map<pair<int,int>,int> mapping;
        
        mapping[make_pair(0,0)]=1;
        for(int i=0; i<n; i++)
        {
            if(str[i]=='0') zc++;
            else if(str[i]=='1') oc++;
            else tc++;
            pair<int,int> temp = make_pair(oc-zc, tc-oc);
            ans += mapping[temp];
            mapping[temp]++;
        }
        
        return ans;
    }
};
```

### Min no of refueling stops
```
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        /*
            Q. Find min no refueling stops given start fuel and target and vector of stations
            
            Car has infinite gas tank, its efficiency is 1mpl
            startFuel contains the current fuel that car has
            
            We try to reach as many stations as we can with the current fuel
            We also keep pushing reachable stations in a priority queue
            When we are not able to reach next station, we pick the station with the most fuel
            from reachable stations
            
            If we cannot reach next station we return -1
            When all stations are exhausted, we keep utilising the fuel from priority queue
            until the target is reached or fuel is exhausted
        */
        priority_queue<int>pq;
        int index = 0;
        int ans = 0;
        
        while(index<stations.size())
        {
            if(stations[index][0] <= startFuel) pq.push(stations[index][1]);
            else
            {
                while(stations[index][0] > startFuel && !pq.empty())
                {
                    ans++;
                    startFuel += pq.top();
                    pq.pop();
                }
                if(stations[index][0] > startFuel) return -1;
                else pq.push(stations[index][1]);
            }
            index++;
        }
        
        while(target>startFuel && !pq.empty())
        {
            ans++;
            startFuel += pq.top();
            pq.pop();
        }
        
        if(target>startFuel) return -1;
        else return ans;
    }
};
```

### Longest consecutive sequence
```
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        /*
            Q. Find length of longest consecutive sequence
            
            Sort and find - O(nlogn)
            
            In a map we keep val->len, where val is array element and len is length of sequence
            formed by it
            When a new val is found in array, there are possibilities for val-1 and val+1
            Update lengths according to these 4 criterion and update ans as well
            If you get duplicates in array then skip the duplicate
        */
        unordered_map<int,int> mapping; int ans = 0;
        
        for(int i=0; i<nums.size(); i++)
        {
            int val = nums[i];
            if(mapping.find(val)!=mapping.end()) continue;
            
            bool l = mapping.find(val-1)!=mapping.end(); 
            bool r = mapping.find(val+1)!=mapping.end();
            
            if(!l && !r)
            {
                mapping[val]=1;
                ans = max(ans, 1);
            }
            else if(l && !r)
            {
                int start = val - mapping[val-1];
                mapping[val] = mapping[start]+1;
                mapping[start]++;
                ans = max(ans, mapping[start]);
            }
            else if(!l && r)
            {
                int end = val + mapping[val+1];
                mapping[val] = mapping[end]+1;
                mapping[end]++;
                ans = max(ans, mapping[end]);
            }
            else
            {
                int start = val - mapping[val-1];
                int end = val + mapping[val+1];
                int len = end - start + 1;
                mapping[start] = len;
                mapping[end] = len;
                mapping[val] = len;
                ans = max(ans, len);
            }
        }
        
        return ans;
    }
};
```

### Rearrange characters such that no 2 are same
```
class Solution
{
    public:
    string rearrangeString(string str)
    {
        string ans;
        unordered_map<char, int> m;
        priority_queue<pair<int, char>> pq;
        pair<int, char> temp, t2;
        
        // Create frequency map and push to priority queue using frequency
        for(auto i:str) m[i]++;
        for(auto i:m) pq.push(make_pair(i.second, i.first));
        
        // Put the first element in temp before processing
        temp = pq.top();
        pq.pop();
        
        // Do work while the queue is not empty
        while(!pq.empty())
        {
            // Get the topmost element in queue
            t2 = pq.top();
            pq.pop();
            
            // Add temp character to the ans
            ans += temp.second;
            
            // Decrease frequency and push to queue if decreased frequency is <= 0
            temp.first--;
            if(temp.first > 0) pq.push(temp);
            
            // Swap the two pairs
            temp = t2;
        }
        
        // At last there will be one character left, process that
        temp.first--;
        ans += temp.second;
        
        // If character still remains, arrangement is not possible, else return ans
        if(temp.first > 0) return "-1";
        return ans;
    }
    
};
```

### Trapping Rain water
```
class Solution {
public:
    int trap(vector<int>& height) {
        /*
            Q. Given elevation map, find out water that can be trapped
            
            We can create 2 arrays of left max and right max, ans for each index will be
            max(0, min(lmax[i], rmax[i]) - height[i])
            
            We can also do this using 4 variables
            On first and last elevations we cannot keep anything
            We keep left and right max and left and right indices
            Keep updating lmax and rmax and keep updating indices based on which is smaller
            Also keep adding to ans
        */
        if(height.size() < 3) return 0;
        
        int lmax = height[0], rmax = height[height.size()-1];
        int lin = 1, rin = height.size()-2, ans = 0;
        
        while(lin <= rin)
        {
            if(lmax < rmax)
            {
                ans += max(0, lmax-height[lin]);
                lmax = max(lmax, height[lin]);
                lin++;
            }
            else
            {
                ans += max(0, rmax-height[rin]);
                rmax = max(rmax, height[rin]);
                rin--;
            }
        }
        
        return ans;
    }
};
```

### Length of largest subarray with continuous elements
```
int findLength(int arr[], int n)
{
    int max_len = 1;
    for (int i=0; i<n-1; i++)
    {
        // Initialize min and max for all subarrays starting with i
        int mn = arr[i], mx = arr[i];
 
        // Consider all subarrays starting with i and ending with j
        for (int j=i+1; j<n; j++)
        {
            // Update min and max in this subarray if needed
            mn = min(mn, arr[j]);
            mx = max(mx, arr[j]);
 
            // If current subarray has all contiguous elements
            if ((mx - mn) == j-i) max_len = max(max_len, mx-mn+1);
        }
    }
    return max_len;
}
```

### Employee Free Time
```
class Solution {
public:
    typedef pair<Interval, pair<int,int>> pi;
    // Comparator for priority queue is different than sorting comparator
    class Comparison
    {
        public:
        bool operator() (pi a, pi b)
        {
            if(a.first.start==b.first.start) return a.first.end < b.first.end;
            return a.first.start > b.first.start;
        }
    };
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        /*
            Q. Find the employee free time as schedule
            
            We push all employees starting schedules in priority queue, this is sorted based 
            on start time
            Then we take the most recent schedule and check if the start time of next person is 
            more, then push the empty time to queue
            After this push the next slot for the same employee
        */
        priority_queue<pi, vector<pi>, Comparison>pq; 
        vector<Interval> ans; 
        int endtime;
        for(int i=0; i<schedule.size(); i++) pq.push(make_pair(schedule[i][0], make_pair(i, 0)));
        endtime = pq.top().first.end;
        
        while(!pq.empty())
        {
            pi temp = pq.top();
            pq.pop();
            if(temp.first.start > endtime) ans.push_back(Interval(endtime, temp.first.start));
            endtime = max(endtime, temp.first.end);
            int x = temp.second.first; int y = temp.second.second;
            if(y<schedule[x].size()-1) pq.push(make_pair(schedule[x][y+1], make_pair(x, y+1)));
        }
        
        return ans;
    }
};
```

### Skyline Problem
```
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        /*
            Q. Find the skyline from the given vector of buildings
            
            O(n^2) approach not passing
            
            We store all buildings starting or ending at a given point in a map
            Multiset contains all buildings that are currently present at a given point
            Map contains points in sorted order
            First put building end points in map
            Then traverse on map and keep adding or removing buildings for that point
            After that check if there is no building in set, height will be 0
            Else get the building with max height, if height is same, then don't update
            Else update and set last height
        */
        map<int, vector<int>>m;
        vector<vector<int>>skyline;
        
        for(int i=0; i<buildings.size(); i++)
        {
            m[buildings[i][0]].push_back(buildings[i][2]);
            m[buildings[i][1]].push_back(-buildings[i][2]);
        }
        
        multiset<int>s;
        int last_height = 0;
        for(auto it=m.begin(); it!=m.end(); it++)
        {   
            for(auto newOrEnded:it->second)
            {
                if(newOrEnded>0) s.insert(newOrEnded);
                else s.erase(s.find(-newOrEnded));
            }
            int height;
            if(!s.empty())
            {
                height=*(s.rbegin());
                if(height==last_height) continue;
            }
            else height=0;
            last_height=height;
            skyline.push_back({it->first,height});
        }
        return skyline;
    }
};
```

### Find all anagrams in a string
```
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        /*
            Q. Find all anagrams in a string
            
            Create frequency map for p
            Matchcount indicates how many useful characters we have got
            Process the first window of length p seperately
            Then we just acquire and release single characters at a time
            If we add a useful character, then increment matchcount
            If we remove useful character, then decrement matchcount
            Whenever matchcount==p.size we can say this sustring is anagram of p
        */
        vector<int> ans; unordered_map<char,int> pmap; unordered_map<char,int> cmap;
        if(p.size()>s.size()) return ans;
        int i = 0, j = 0, matchcount = 0;
        
        for(auto ch:p) pmap[ch]++;
        for(; j<p.size(); j++)
        {
            cmap[s[j]]++;
            if(cmap[s[j]]<=pmap[s[j]]) matchcount++;
        }
        if(matchcount == p.size()) ans.push_back(0);
        
        for(j--; j<s.size();)
        {
            j++;
            cmap[s[j]]++;
            if(cmap[s[j]]<=pmap[s[j]]) matchcount++;
            cmap[s[i]]--;
            if(cmap[s[i]]<pmap[s[i]]) matchcount--;
            i++;
            if(matchcount == p.size()) ans.push_back(i);
        }
        
        return ans;
    }
};
```

### Minimum Window Substring
```
class Solution {
public:
    string minWindow(string s, string t) {
        /*
            Q. Find minimum window substring of t in s
            
            Create frequency map for p
            Matchcount indicates how many useful characters we have got
            Acquire till we get all useful characters and then release till there are useful chars
            If we add a useful character, then increment matchcount
            If we remove useful character, then decrement matchcount
            Whenever matchcount==p.size we can say this sustring is potential ans
        */
        string ans; unordered_map<char,int> tmap; unordered_map<char,int> cmap; int ss=-1, se=1e7;
        if(t.size()>s.size()) return ans;
        int i = 0, j = 0, matchcount = 0;
        
        for(auto ch:t) tmap[ch]++;
        
        while(j<s.size())
        {
            while(j<s.size() && matchcount<t.size())
            {
                cmap[s[j]]++;
                if(cmap[s[j]]<=tmap[s[j]]) matchcount++;
                j++;
            }
            
            while(matchcount==t.size())
            {
                if(j-i < se-ss)
                {
                    ss = i;
                    se = j;
                }
                cmap[s[i]]--;
                if(cmap[s[i]]<tmap[s[i]]) matchcount--;
                i++;
            }
        }
        
        if(se <= s.size()) ans = s.substr(ss, se-ss);
        
        return ans;
    }
};
```

### Binary search questions
```
class Solution {
public:
    /*
        Do a binary search over all capacities and if possible with a given capacity then update ans
    */
    bool possible(vector<int>& weights, int capacity, int days)
    {
        int d = 1; int loaded = 0;
        for(int i=0; i<weights.size();)
        {
            // If curr weight is greater than capacity then return false
            if(weights[i]>capacity) return false;
            // If curr box can be loaded on ship
            if(loaded+weights[i]<=capacity)
            {
                loaded += weights[i];
                i++;
            }
            // Current weight cannot be loaded, schedule it for next day
            else 
            {
                loaded = 0;
                d++;
            }
        }
        return d<=days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int s = 0, e = INT_MAX; int ans;
        while(s<=e)
        {
            int mid = s + (e-s)/2;
            if(possible(weights, mid, days))
            {
                ans = mid;
                e = mid-1;
            }
            else s = mid+1;
        }
        return ans;
    }
};
```

### Search in sorted rotated array duplicates
```
class Solution {
public:
    /*
        Duplicacy in rotated sorted array
    */
    bool bs(vector<int>&nums, int target)
    {
        int s = 0, e = nums.size()-1, mid;
        while(s<e)
        {
            mid = s + (e-s)/2;
            if(nums[mid]==target) return true;
            if(nums[mid]>nums[e])
            {
                if(nums[mid]>target && nums[s] <= target) e = mid;
                else s = mid + 1;
            }
            else if(nums[mid] < nums[e])
            {
              if(nums[mid]<target && nums[e] >= target) s = mid + 1;
              else e = mid;
            }
            else e--;
        }
        return nums[s] == target ? true : false;
    }
    bool search(vector<int>& nums, int target) {
        return bs(nums, target);
    }
};
```

### Heapsort
```
#include <bits/stdc++.h>

using namespace std;

void heapify(int arr[], int n, int i)
{
    // Initialize largest as root and find left and right children
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    // If left is larger than root, assign largest to this
    if(left < n && arr[left]>arr[largest]) largest = left;

    // If right is larger than largest found till now, assign it
    if(right < n && arr[right]>arr[largest]) largest = right;

    // If largest is not root, then swap both indices and call heapify for subtrees
    if(largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n)
{
    // We don't need to heapify all elements as the leaf nodes already follow heap property
    // Just heapify all non leaf nodes
    // Find the index of the first non leaf node in opposite direction
    int startidx = n/2-1;

    for(int i=startidx; i>=0; i--)
    {
        heapify(arr, n, i);
    }
}

void heapSort(int arr[], int n)
{
    // Build the heap in O(n) time
    buildHeap(arr, n);

    // Heapify the swapped element with reduced size
    for(int i=n-1; i>=0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    int arr[] = {1, 4, 7, 2, 19, 1, -1, 23, 45, 65, 73, 56, 100, 0};
    int n = sizeof(arr)/sizeof(int);

    heapSort(arr, n);

    for(int i=0; i<n; i++) cout<<arr[i]<<" ";
    cout<<endl;

    return 0;
}
```

### Mergesort on arrays
```
#include <bits/stdc++.h>

using namespace std;

// Function for merging two sorted arrays
// Since the arrays to be merged will always be continuous
// The two arrays are seperated by mid
// We create a temporary array to store result of merged arrays
void merge(vector<int>& arr, int lo, int mid, int hi)
{
    vector<int> tmp(hi+1);
    int l1, l2, i;

    // Merge two sorted arrays
    for(l1=lo, l2=mid+1, i=lo; l1<=mid && l2<=hi; i++)
    {
        if(arr[l1] <= arr[l2]) tmp[i]=arr[l1++];
        else tmp[i] = arr[l2++];
    }

    // If one array is empty then copy the other array
    while(l1 <= mid) tmp[i++] = arr[l1++];
    while(l2 <= hi) tmp[i++] = arr[l2++];

    // Copy from temp array to original array
    for(i=lo; i<=hi; i++) arr[i] = tmp[i];
}

// Function to do mergesort
// Divides the array into two halves and 
// calls mergesort on individual arrays
// Then it merges the two sorted arrays
void mergesort(vector<int>& arr,int lo, int hi)
{
    // If array has size greater than 1, then only call mergesort
    if(lo < hi)
    {
        int mid = lo + (hi-lo)/2;
        mergesort(arr, lo, mid);
        mergesort(arr, mid+1, hi);
        merge(arr, lo, mid, hi);
    }
}

// Driver function
int main()
{
    vector<int> arr = {11, 23, 3, 2, 12, 89, 100, 122, 1, -10};

    mergesort(arr, 0, arr.size()-1);

    for(int i=0; i<arr.size(); i++) cout<<arr[i]<<" ";
    cout<<endl;

    return 0;
}
```

### Mergesort on Linked List
```
#include <bits/stdc++.h>

using namespace std;

// Node structure and constructors to create Nodes
struct Node
{
    int data;
    Node* next;

    Node()
    {
        this->data = 0;
        this->next = NULL;
    }

    Node(int val)
    {
        this->data = val;
        this->next = NULL;
    }

    Node(int val, Node* nextref)
    {
        this->data = val;
        this->next = nextref;
    }
};

Node* merge(Node* l1, Node* l2)
{
    if(l1==NULL && l2==NULL) return NULL;
        
    Node* head=NULL; Node* tail=NULL;
    
    while(l1!=NULL && l2!=NULL)
    {
        Node* temp = new Node(min(l1->data, l2->data));
        
        if(l1->data < l2->data) l1 = l1->next;
        else l2 = l2->next;
        
        if(head == NULL) {head = tail = temp;}
        else {tail->next = temp; tail=tail->next;}
    }
    
    while(l1!=NULL)
    {
        Node* temp = new Node(l1->data);
        l1 = l1->next;
        
        if(head == NULL) {head = tail = temp;}
        else {tail->next = temp; tail=tail->next;}
    }
    
    while(l2!=NULL)
    {
        Node* temp = new Node(l2->data);
        l2 = l2->next;
        
        if(head == NULL) {head = tail = temp;}
        else {tail->next = temp; tail=tail->next;}
    }
    
    return head;
}

void mergesort(Node ** head)
{
    if(*head==NULL || (*head)->next==NULL) return;

    Node *a, *b, *slow=*head, *fast=(*head)->next;

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    a = *head;
    b = slow->next;
    slow->next = NULL;

    mergesort(&a);
    mergesort(&b);

    *head = merge(a, b);
}

int main()
{
    // Create a new linked list
    Node * head = new Node(5, new Node(4, new Node(3, new Node(2, new Node(1)))));

    mergesort(&head);

    // Print the new linked list
    while(head)
    {
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;

    return 0;
}
```