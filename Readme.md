# Templates

## STL

### Vector
```
// creates vector of n integers with value 1
vector<int> vec(n, 1);

// For getting size of vector
vec.size();

// To resize vector to new size
vec.resize(20);

// To check if vector is empty
vec.empty();

// To access ith element
vec[0];

// to access front element
vec.front();

// tp access back element
vec.back();

// insert element at end
vec.push_back(100);

// remove element from end
vec.pop_back();

// remove all elements of array
vec.clear();
```

### List
```
// create list and push elements
list<int> li;
li.push_back(2);
li.push_front(1);

// reverse list and delete elements
li.reverse();
li.pop_back();
li.pop_front();

// many more functionalities available - refer - https://cplusplus.com/reference/list/list/
```

### Stack
```
// Create stack of integers
stack<int> s;

// Insert elements to stack
s.push(1);
s.push(2);
s.push(3);

// Get size of stack
s.size();

// Access top element of stack
s.top();

// to check if stack is empty
s.empty();

// to pop topmost element
s.pop();

```

### Queue
```
// Create a queue
queue<int> q;

// Push elements to queue
q.push(1);
q.push(2);
q.push(3);

// to access front element
q.front();

```

### Doubly ended queue
```
// to create deque
deque<int> dq;

// push element to front
dq.push_front(1);

// push element to back
dq.push_back(2);

// to check size of deque
dq.size();

// to check front of deque
dq.front();

// to check end of deque
dq.back();

// to remove last element
dq.pop_back();

// to remove first element
dq.pop_front();

// to check if queue is empty
dq.empty();

// to clear contents of queue
dq.clear();

```

### Priority queue
```
// Heap data structure - default sorting order - descending
// Create priority queue of integers
priority_queue<int> pq;

// Insert elements into priority queue
pq.push(5);
pq.push(4);
pq.push(3);
pq.push(2);
pq.push(1);

// to display top element of priority queue
pq.top();

// to pop element from priority queue
pq.pop();

// Standard operations empty and size available
```

### Min priority queue
```
// Creates a Min heap
priority_queue<int, vector<int>, greater<int>> minPriorityQueue;

// Push elements into priority queue
minPriorityQueue.push(5);
minPriorityQueue.push(4);
minPriorityQueue.push(3);
minPriorityQueue.push(2);
minPriorityQueue.push(1);

// to display top element of priority queue
minPriorityQueue.top();
```

### Priority queue using comparator
```
// The custom function returns true if a and b are in correct order
// In this case we want to sort in reverse order based on second parameter
class customComparator {
public:
    bool operator()(pair<int, int>& a, pair<int, int>& b) const
    {
        return a.second > b.second;
    }
};
```
```
// Make a min heap of pair class with comparator
priority_queue<pair<int, int>, vector<pair<int, int>>, customComparator> customPriorityQueue;

// Insert elements to priority queue
customPriorityQueue.push(make_pair(1, 1));
customPriorityQueue.push(make_pair(2, 2));
customPriorityQueue.push(make_pair(3, 3));
customPriorityQueue.push(make_pair(4, 4));
customPriorityQueue.push(make_pair(5, 5));

// display top element of priority queue
cout<<customPriorityQueue.top().first<<" "<<customPriorityQueue.top().second<<endl;
```

### Set
```
// create a set of integers
set<int> st;

// insert an element into set
st.insert(1);
st.insert(2);
st.insert(3);
st.insert(4);

// erase an element from set
st.erase(3);

// to find an element in set
if(st.find(4) != st.end()) {
    cout<<"Element present in set"<<endl;
}

// first element in array which will come after val
cout<<"Upper bound of set: "<<*(st.upper_bound(INT_MIN))<<endl;

// first element in array which will not go before val (either equal or after)
cout<<"Lower bound of set: "<<*(st.lower_bound(INT_MAX))<<endl;

// by default set elements are sorted in increasing order
for(auto it:st) {
    cout<<it<<" ";
}

// clear the contents of a set
st.clear();
```

### Set (descending order)
```
// creates a descending set
set<int, greater<int>> descendingSet;
```

### Map
```
// creates a map
map<int, int> m;

// insert elements to map. Key is 1 and value is 1 (RHS)
m[1] = 1;
m.insert(make_pair(2, 2));

// erase via key
m.erase(2);

// auto iterator for map
for(auto it:m) {
    cout<<i.first<<" "<<i.second<<endl;
}

// clear contents of the map
m.clear();

// other operations like size, empty, find, count available
```

### Unordered set
```
// internal functions same, faster than set
```

### Unordered map
```
// internal functions same, faster than map
```

### Custom sorting
```
// The custom function returns true if a and b are in correct order
// In this case we want to sort in reverse order based on second parameter
class customComparator {
public:
    bool operator()(pair<int, int>& a, pair<int, int>& b) const
    {
        return a.second > b.second;
    }
};
```
```
// declare vector and insert elements
vector<pair<int,int>> customvec;
customvec.push_back(make_pair(1,1));
customvec.push_back(make_pair(2,2));
customvec.push_back(make_pair(3,3));
customvec.push_back(make_pair(4,4));
customvec.push_back(make_pair(5,5));

// sort using comparator
sort(customvec.begin(), customvec.end(), customComparator());
```

### Auto iterator and for loop
```
for(auto it=a.begin(); it != a.end(); it++) {
    cout<<*it<<" ";
}


for(auto element:a) {
    cout<<element<<" ";
}
```
