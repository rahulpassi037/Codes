## Linked List, Stacks and Queues

### Linked List

#### Frequent Questions
* Standard Questions - Reverse, swap, delete, etc
* Two pointers - Find middle, Floyd's cycle
* LRU Cache
* LFU Cache
* Tree related Questions

#### Points to remember
* Always check pointer for NULL value before accessing contents
* Edge cases when list is empty or when there is only one node, sentinel head
* How answer depends on length of linked list (odd or even)
* When we start from head and move fast by 2, it only passes over even indexed nodes (0-based indexing)

### Reverse a LL recursive
```
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        
        // This is recursive approach
        // If you have reached the last node or past the last node, return the node
        // head==NULL is used for an empty list
        if(head==NULL || head->next==NULL) return head;
        
        // Otherwise call recursively and store what they return, used for returning head
        ListNode* rest = reverseList(head->next);
        
        // Attach head as the last node and make next of head as NULL
        // head is the current node, we are using the old connection to attach current node as last
        head->next->next = head;
        head->next = NULL;
        
        // Return the head
        return rest;
    }
};
```

### Reverse a LL iterative
```
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // This is the iterative approach
        // Initialize current and prev pointers
        ListNode * prev = NULL, * curr = head;
        
        // We keep changing all pointers one by one
        while(curr)
        {
            // Find the next node and change pointers accordingly
            ListNode * next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        // Return the last node
        return prev;
    }
};
```

### Floyd's cycle
```
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        /*
            Floyd's Cycle Detection Algorithm
            
            Two pointers fast and slow, keep incrementing them
            If they become equal, then cycle is present
            
            To find the start node of the loop
            When nodes become equal, throw slow to head and then keep incrementing both nodes by one
            They will again meet at the start node of the loop
            
            Proof
            All distances mean number of edges
            Start node means node where the loop starts
            
            m - distance from head to start node
            n - distance of loop
            k - distance from start node to point of meeting
            df - distance travelled by fast pointer
            ds - distance travelled by slow pointer
            
            df = m + c1*n + k
            ds = m + c2*n + k
            
            Also df = 2*ds
            
            Therefore,
            m + c1*n + k = 2*m + 2*c2*n + 2*k
            m + k = (c1-2*c2)*n
            m + k = c*n or m = c*n - k
            
            m = (c-1)*n + (n-k)
            n-k is the distance from meeting point to start node
        */
        
        ListNode * fast = head;
        ListNode * slow = head;
        
        while(fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            
            if(fast == slow)
            {
                slow = head;
                while(fast != slow)
                {
                    fast = fast->next;
                    slow = slow->next;
                }
                return fast;
            }
        }
        
        return NULL;
    }
};
```

### LRU Cache
```
class LRUCache {
public:
    // We implement lru cache using linked list and map
    // Linked list is doubly linked list
    // key is the key of the cache content and val is the value of the cache content
    // Map stores the mapping of key to address of a linked list
    // We can remove a ll node in O(1) time and place it at head in O(1)
    class node
    {
        public:
        int key;
        int val;
        node * prev;
        node * next;
        node(int key, int val)
        {
            this->key = key;
            this->val = val;
            prev = NULL;
            next = NULL;
        }
    };
    
    // Capacity is the total capacity of the LL and currentcount denotes the no of
    // elements currently present in the LL
    // We maintain 2 extra pointers head and tail
    unordered_map<int, node*> mapping;
    int capacity;
    int currentcount;
    node * head;
    node * tail;
    
    // constructor of the LRU cache
    // Set capacity and current count and also make 2 dummy nodes head and tail
    LRUCache(int capacity) {
        this->capacity = capacity;
        currentcount = 0;
        head = new node(0, 0);
        tail = new node(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    // To get a node with a given key
    int get(int key) {
        
        // If the key is not present
        if(mapping.find(key) == mapping.end()) return -1;
        
        // Move the node to correct position
        node * temp = mapping[key];
        int ans = temp->val;
        // Remove the node from current position and connect front and back nodes
        node * tempp1 = temp->next;
        node * tempm1 = temp->prev;
        tempm1->next = tempp1;
        tempp1->prev = tempm1;
        // Insert the node just before the tail and connect pointers
        node * tailp = tail->prev;
        tail->prev = temp;
        temp->next = tail;
        tailp->next = temp;
        temp->prev = tailp;
        
        // Return ans
        return ans;
    }
    
    // To put a new key value pair in the cache
    void put(int key, int value) {
        
        // If the key is already present in the cache
        if(mapping.find(key) != mapping.end())
        {
            // Get the node address and set its value
            // Also remove the node from current position
            node * temp = mapping[key];
            temp->val = value;
            node * tempp1 = temp->next;
            node * tempm1 = temp->prev;
            tempm1->next = tempp1;
            tempp1->prev = tempm1;
            // Insert the new node in the end of the LL
            node * tailp = tail->prev;
            tail->prev = temp;
            temp->next = tail;
            tailp->next = temp;
            temp->prev = tailp;
            return;
        }
        // If current count is greater than capacity then we need to evict
        if(currentcount >= capacity)
        {
            // Remove the least recently used node
            // Remove from head and also remove from the map
            node * del = head->next;
            node * headpp = head->next->next;
            head->next = headpp;
            headpp->prev = head;
            mapping.erase(del->key);
            // Decrease the current count since the node is removed
            currentcount--;
            // Also delete the node in heap memory
            del->prev = NULL;
            del->next = NULL;
            delete(del);
        }
        // Insert the node just before tail and also put in map
        // Also increase the current count
        node * tailprev = tail->prev;
        node * temp = new node(key, value);
        tailprev->next = temp;
        temp->next = tail;
        tail->prev = temp;
        temp->prev = tailprev;
        mapping[key] = temp;
        currentcount++;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

### Stacks and Queues

#### Frequent Questions
* Next Greater Element and its variants
* Paretheses questions
* K stacks and K Queues
* Adapters
* Infix, Prefix, Postfix

#### Points to remember
* Always check is stack is empty before accessing top or popping

### Next Greater Element on Right
```
class Solution
{
    public:
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        // Approach:
        // Keep storing elements on stack and traversing array
        // When you find that top element on stack is smaller than you
        // Then keep popping it and keep setting answer for it
        // We will modify the same array so we store indexes in stack
        stack<long long> s;
        // Traverse over all elements
        // If stack is empty then simply push to stack
        // Else compare till stack becomes empty or element becomes greater
        for(int i=0; i<n; i++)
        {
            while(!s.empty() && arr[s.top()] < arr[i])
            {
                arr[s.top()] = arr[i];
                s.pop();
            }
            s.push(i);
        }
        // The elements that are still on stack don't have any next greater element
        while(!s.empty())
        {
            arr[s.top()] = -1;
            s.pop();
        }
        // Return the ans array
        return arr;
    }
};
```

### Next Greater Element Circular
```
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        // Why are we creating new ans array: because we would need original array
        // for second traversal
        // We can also concatenate the array with itself and then run algo
        stack<int> s;
        vector<int> ans(nums.begin(), nums.end());
        
        // Both iterations are combined
        for(int i=0; i<2*nums.size(); i++)
        {
            while(!s.empty() && nums[s.top()]<nums[i%nums.size()])
            {
                ans[s.top()] = nums[i%nums.size()];
                s.pop();
            }
            // We don't have to push for the second iteration, we just solve the remaining elements
            if(i<nums.size()) s.push(i);
        }
        
        // The elements that are still in array do not have a NGE
        while(!s.empty())
        {
            ans[s.top()] = -1;
            s.pop();
        }
        
        // Return ans
        return ans;
    }
};
```

### Largest Area Histogram
```
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int ans = INT_MIN;
        stack<int> s;
        // Push for handling edge cases, elements that don't have nse on right
        s.push(-1);
        for(int i=0; i<heights.size(); i++)
        {
            // We need atleast 2 elements
            // We are finding next smaller element on right and solving
            while(s.size()>1 && heights[s.top()]>heights[i])
            {
                int height = heights[s.top()];
                s.pop();
                int width = i-s.top()-1;
                ans = max(ans, height*width);
            }
            s.push(i);
        }
        // For elements still in the array
        while(s.size()>1)
        {
            int height = heights[s.top()];
            s.pop();
            int width = heights.size()-s.top()-1;
            ans = max(ans, height*width);
        }
        return ans;
    }
};
```

### Asteroid Collision
```
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> s;
        // Traverse over all array elements
        for(int i=0; i<asteroids.size(); i++)
        {
            // If stack is empty then simply add
            if(s.empty()) s.push(i);
            else
            {
                // If asteroid is moving towards right, then we just store in array
                if(asteroids[i] > 0) s.push(i);
                // Else check if asteroid can be broken or not
                else
                {
                    // Our asteroid is currently not broken
                    bool broken = false;
                    // Till the time you get asteroids moving in other direction
                    while(!s.empty() && asteroids[s.top()]>0)
                    {
                        // Get the magnitude of both asteroids
                        int right = abs(asteroids[s.top()]);
                        int left = abs(asteroids[i]);
                        // Our asteroid breaks
                        if(right > left) 
                        {
                            broken = true;
                            break;
                        }
                        // Both asteroids break
                        else if(right == left)
                        {
                            s.pop();
                            broken = true;
                            break;
                        }
                        // Only the other asteroid breaks
                        else s.pop();
                    }
                    // If our asteroid is not broken then push to stack
                    if(!broken) s.push(i);
                }
            }
        }
        
        // All asteroids present in stack are not broken
        vector<int> ans;
        while(!s.empty())
        {
            ans.push_back(asteroids[s.top()]);
            s.pop();
        }
        
        // We need to reverse the answer array to get correct order
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

### Length of longest valid substring
```
class Solution {
  public:
    int findMaxLen(string s) {
        // We are storing character and index in stack for opening parenthesis
        stack<pair<char, int> > st;
        // Push this to handle edge cases (when whole string is balanced)
        // ) cannot be popped by any character
        st.push(make_pair(')', -1));
        int omax = 0;
        
        for(int i=0; i<s.size(); i++)
        {
            // If you get opening brackets, then simply push 
            if(st.empty() || s[i]=='(') st.push(make_pair(s[i], i));
            else
            {
                // If this substring is valid parentheses, then update ans
                if(st.top().first=='(')
                {
                    st.pop();
                    omax = max(omax, i-st.top().second);
                }
                else st.push(make_pair(s[i], i));
            }
        }
        return omax;
    }
};
```

### Remove k digits
```
class Solution {
public:
    string removeKdigits(string num, int k) {
        // If we have one size and we can remove more than one digits
        if(num.size()==1 && k>=1) return "0";
        
        stack<char> s;
        
        // Keep pushing to stack and if you find bigger digits are present pop them
        // Bigger digits appear at higher place value so we pop them
        for(int i=0; i<num.size(); i++)
        {
            while(!s.empty() && k>0 && s.top()>num[i]) 
            {
                s.pop();
                k--;
            }
            s.push(num[i]);
        }
        
        string ans;
        // Fill the ans string
        while(!s.empty())
        {
            ans.push_back(s.top());
            s.pop();
        }
        
        // Remove prefix zeros
        while(ans.size()>1 && ans.back()=='0') ans.pop_back();
        
        // Reverse to get actual ans
        reverse(ans.begin(), ans.end());
        
        // If we can remove more digits
        while(k>0 && ans.size()>1)
        {
            ans.pop_back();
            k--;
        }
        
        // If we can also remove the last digit
        if(k>0 && ans.size()==1) return "0";
        
        // Return ans
        return ans;
    }
};
```