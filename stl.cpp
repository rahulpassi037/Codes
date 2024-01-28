#include <bits/stdc++.h>

using namespace std;

// The custom function returns true if a and b are in correct order
// In this case we want to sort in reverse order based on second parameter
class customComparator {
public:
    bool operator()(pair<int, int>& a, pair<int, int>& b) const
    {
        return a.second > b.second;
    }
};

int main()
{
    int n = 10;

    // vector - dynamic arrays
    cout<<"Vector: "<<endl;
    vector<int> vec(n, 1); // vector of n integers with value 1
    cout<<vec.size()<<endl; // For getting size of vector
    vec.resize(20); // To resize vector to new size
    cout<<vec.empty()<<endl; // To check if vector is empty
    cout<<vec[0]<<endl; // To access ith element
    cout<<vec.front()<<endl; // to access front element
    cout<<vec.back()<<endl; // tp access back element
    vec.push_back(100); // insert element at end
    vec.pop_back(); // remove element from end
    vec.clear(); // remove all elements of array
    cout<<endl;

    // list - doubly linked list - similar to vector

    // stack
    cout<<"Stack: "<<endl;
    stack<int> s; // to create stack
    s.push(1); // to insert element
    s.push(2); // to insert element
    s.push(3); // to insert element
    cout<<s.size()<<endl; // to check size
    cout<<s.top()<<endl; // to access top element
    cout<<s.empty()<<endl; // to check if stack is empty
    s.pop(); // to pop topmost element
    cout<<endl;

    // queue - STL functions same as stack
    cout<<"Queue: "<<endl;
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout<<q.front()<<endl; // to access front element
    cout<<endl;

    // deque
    cout<<"Deque: "<<endl;
    deque<int> dq; // to create deque
    dq.push_front(1); // push element to front
    dq.push_back(2); // push element to back
    cout<<dq.size()<<endl; // to check size of deque
    cout<<dq.front()<<endl; // to check front of deque
    cout<<dq.back()<<endl; // to check end of deque
    dq.pop_back(); // to remove last element
    dq.pop_front(); // to remove first element
    cout<<dq.empty()<<endl; // to check if queue is empty
    dq.clear(); // to clear contents of queue
    cout<<endl;

    // priority_queue - similar to heap - default sorting order - descending
    cout<<"Priority queue: "<<endl;
    priority_queue<int> pq; // to create priority queue
    pq.push(5); // to push element to priority queue
    pq.push(4); // to push element to priority queue
    pq.push(3); // to push element to priority queue
    pq.push(2); // to push element to priority queue
    pq.push(1); // to push element to priority queue
    cout<<pq.top()<<endl; // to display top element of priority queue
    pq.pop(); // to pop element from priority queue
    // Standard operations empty and size available
    cout<<endl;

    // Min heap
    cout<<"Min priority queue: "<<endl;
    priority_queue<int, vector<int>, greater<int>> minPriorityQueue; // creating a min priority queue
    minPriorityQueue.push(5); // to push element to priority queue
    minPriorityQueue.push(4); // to push element to priority queue
    minPriorityQueue.push(3); // to push element to priority queue
    minPriorityQueue.push(2); // to push element to priority queue
    minPriorityQueue.push(1); // to push element to priority queue
    cout<<minPriorityQueue.top()<<endl; // to display top element of priority queue
    cout<<endl;
    
    // Make a min heap of pair class with comparator
    cout<<"Min priority queue with custom comparator: "<<endl;
    priority_queue<pair<int, int>, vector<pair<int, int>>, customComparator> customPriorityQueue; // declaring priority queue for custom sorting
    customPriorityQueue.push(make_pair(1, 1)); // insert elements to priority queue
    customPriorityQueue.push(make_pair(2, 2)); // insert elements to priority queue
    customPriorityQueue.push(make_pair(3, 3)); // insert elements to priority queue
    customPriorityQueue.push(make_pair(4, 4)); // insert elements to priority queue
    customPriorityQueue.push(make_pair(5, 5)); // insert elements to priority queue
    cout<<customPriorityQueue.top().first<<" "<<customPriorityQueue.top().second<<endl; // display top element of priority queue
    cout<<endl;

    // set
    cout<<"Set: "<<endl;
    set<int> st; // create a set of integers
    st.insert(1); // insert an element into set
    st.insert(2); // insert an element into set
    st.insert(3); // insert an element into set
    st.insert(4); // insert an element into set
    st.erase(3); // erase an element from set
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
    st.clear(); // clear the contents of a set
    cout<<endl<<endl;

    // descending set
    cout<<"Descending set: "<<endl;
    set<int, greater<int>> descendingSet; // declare a descending set
    descendingSet.insert(1); // insert element
    descendingSet.insert(2); // insert element
    descendingSet.insert(4); // insert element
    for(auto it:descendingSet) {
        cout<<it<<" ";
    }
    cout<<endl<<endl;

    // map
    cout<<"Map: "<<endl;
    map<int, int> m; // create a map
    m[1] = 1; // Key is 1 and value is 1 (RHS)
    m.insert(make_pair(2, 2));
    m.erase(2); // erase via key
    for(auto it:m) {
        cout<<i.first<<" "<<i.second<<endl;
    }
    m.clear(); // clear contents of the map
    // other operations like size, empty, find, count available
    cout<<endl;

    // unordered_set
    cout<<"Unordered set: "<<endl;
    // internal functions same, faster than set
    cout<<endl;

    // unordered_map
    cout<<"Unordered map: "<<endl;
    // internal functions same, faster than map
    cout<<endl;

    // custom sort
    cout<<"Custom sort on array: "<<endl;
    vector<pair<int,int>> customvec;
    customvec.push_back(make_pair(1,1));
    customvec.push_back(make_pair(2,2));
    customvec.push_back(make_pair(3,3));
    customvec.push_back(make_pair(4,4));
    customvec.push_back(make_pair(5,5));
    sort(customvec.begin(), customvec.end(), customComparator());
    for(auto it:customvec) {
        cout<<it.first<<" ";
    }
    cout<<endl;
    cout<<endl;

    // auto iterator
    cout<<"Auto iterator: "<<endl;
    vector<int> a(n, 0);
    for(auto it=a.begin(); it != a.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;

    for(auto element:a) {
        cout<<element<<" ";
    }
    cout<<endl;
    cout<<endl;

    // variety of for loops
    cout<<"Variety of for loops: "<<endl;
    cout<<endl;


    return 0;
}