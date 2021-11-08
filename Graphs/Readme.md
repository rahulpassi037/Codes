## Graphs

### BFS
```
class Solution
{
    public:
    //Function to return Breadth First Traversal of given graph.
	vector<int>bfsOfGraph(int V, vector<int> adj[])
	{
	    // Create visited array and queue for bfs
	    bool visited[V]; queue<int> q; vector<int> ans;
	    
	    // Mark visited as false for all nodes
	    for(int i=0; i<V; i++) visited[i]=false;
	    
	    // Push the 0th node in queue and mark its visited as true
	    q.push(0);
	    visited[0]=true;
	    
	    // While queue is not empty
	    // Find no of neighbours and process all of them one by one
	    // If a neighbour is not visited then visit it and mark it true
	    while(!q.empty())
	    {
	        int size = q.size();
	        
	        while(size--)
	        {
	            int temp = q.front();
	            q.pop();
	            
	            ans.push_back(temp);
	            
	            vector<int> tmp = adj[temp];
	            for(int i=0; i<tmp.size(); i++)
	            {
	                if(!visited[tmp[i]])
	                {
	                    q.push(tmp[i]);
	                    visited[tmp[i]]=true;
	                }
	            }
	        }
	    }
	    
	    // Return the ans array
	    return ans;
	}
};
```

### Optimize water distribution in a village
```
class Solution {
public:
    typedef pair<int,int> pi;
    // Exact prims algo
    // Prims algo is greedy approach
    // We use priority queue
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // Our graph, first is weight, second is node, there is extra dummy node
        vector<pair<int,int>> graph[n+1]; 
        // Priority queue for prims algo
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        // Visited array
        bool visited[n+1]; int ans = 0;
        
        // Create graph, graph is bidirectional
        for(int i=0; i<pipes.size(); i++)
        {
            graph[pipes[i][0]].push_back(make_pair(pipes[i][1], pipes[i][2]));
            graph[pipes[i][1]].push_back(make_pair(pipes[i][0], pipes[i][2]));
        }
        
        // Connect dummy node, dummy node is used for digging well
        for(int i=0; i<n; i++)
        {
            graph[0].push_back(make_pair(i+1, wells[i]));
            graph[i+1].push_back(make_pair(0, wells[i]));
        }
        
        // Initialize visited array
        for(int i=0; i<=n; i++) visited[i]=false;
        
        // Push the dummy node
        pq.push(make_pair(0, 0));
        while(!pq.empty())
        {
            int src = pq.top().second;
            // If node is not visited then add weight
            // This weight is minimal therefore ans is optimal
            if(!visited[src]) ans += pq.top().first;
            visited[src]=true;
            pq.pop();
            
            // If a neighbour is not visited then push it to queue
            for(auto i:graph[src]) 
                if(!visited[i.first]) pq.push(make_pair(i.second, i.first));
        }
        
        // Return ans
        return ans;
    }
};
```

### DFS
```
class Solution 
{
    public:
	//Function to return a list containing the DFS traversal of the graph.
	void helper(vector<int> adj[], vector<bool>& visited, vector<int>& ans, int src)
	{
	    // Mark the src node as visited
	    visited[src]=true;
	    // Push src node to ans
	    ans.push_back(src);
	    // Call DFS for unvisited nodes
	    for(auto i:adj[src]) if(!visited[i]) helper(adj, visited, ans, i);
	}
	vector<int>dfsOfGraph(int V, vector<int> adj[])
	{
	    // Visited array
	    vector<bool> visited(V, false);
	    // Ans array to fill
	    vector<int> ans;
	    // Do BFS
	    helper(adj, visited, ans, 0);
	    // Return ans
	    return ans;
	}
};
```

### No of enclaves
```
class Solution {
public:
    void helper(vector<vector<int>>& grid, int i, int j)
    {
        // Check out of bound condition
        if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size()) return;
        // Check if current element is already 0, then no need to proceed further
        if(grid[i][j]==0) return;
        // Make current element as 0
        grid[i][j]=0;
        // Call for 4 adjacent cells
        helper(grid, i+1, j);
        helper(grid, i-1, j);
        helper(grid, i, j+1);
        helper(grid, i, j-1);
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size(); int ans = 0;
        
        // No of enclaves are the no of cells from which we cannot reach boundary
        // So we call dfs from each boundary cell and mark elements as 0
        // Mark elements connected to row 0
        for(int i=0; i<n; i++) helper(grid, 0, i);
        // Mark elements connected to last row
        for(int i=0; i<n; i++) helper(grid, m-1, i);
        // Mark elements connected to col 0
        for(int i=0; i<m; i++) helper(grid, i, 0);
        // Mark elements connected to last col
        for(int i=0; i<m; i++) helper(grid, i, n-1);
        
        // Count no of cells that are still 1
        for(int i=0; i<m; i++) for(int j=0; j<n; j++) ans += grid[i][j];
        
        // Return ans
        return ans;
    }
};
```

### No of islands
```
class Solution {
public:
    void helper(vector<vector<char>>& grid, int i, int j)
    {
        // Check for out of bound consdition and if current cell is water
        if(i<0 || j<0 || i==grid.size() || j==grid[0].size() || grid[i][j]=='0') return;
        // Mark current cell as water cell and call for 4 adjacent cells
        grid[i][j]='0';
        helper(grid, i-1, j);
        helper(grid, i+1, j);
        helper(grid, i, j-1);
        helper(grid, i, j+1);
    }
    int numIslands(vector<vector<char>>& grid) {
        // Initialize ans as 0
        int ans = 0;
        // Traverse over all elements and check if it is not visited and is land cell
        // Then call and do ans++
        for(int i=0; i<grid.size(); i++)
            for(int j=0; j<grid[0].size(); j++) 
                if(grid[i][j]=='1') 
                {helper(grid, i, j); ans++;}
        // Return ans
        return ans;
    }
};
```

### Word ladder
```
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Set of words present in the wordlist
        unordered_set<string> mapping;
        // Queue for doing BFS
        queue<string> q;
        // We are currently at level 1
        int ans = 0; int level = 1;
        
        // Push all words in list to set
        for(int i=0; i<wordList.size(); i++) mapping.insert(wordList[i]);
        // Push the begin word in queue
        q.push(beginWord);
        
        // Do BFS
        while(!q.empty())
        {
            // Process all nodes at same level
            int size = q.size();
            while(size--)
            {
                string candidate = q.front();
                q.pop();
                // If we have found the end word then simply return level
                if(candidate == endWord) return level;
                // We try to replace each character in candidate
                // For each alphabet position try to fix all characters and
                // check if it is present in wordlist
                for(int i=0; i<candidate.size(); i++)
                {
                    string temp = candidate;
                    for(int j=0; j<26; j++)
                    {
                        temp[i] = j+'a';
                        if(mapping.find(temp)!=mapping.end())
                        {
                            q.push(temp);
                            mapping.erase(temp);
                        }
                    }
                }
            }
            // Increase the level
            level++;
        }
        
        // No sequence exists
        return 0;
    }
};
```

### Rotting Oranges
```
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        // Queue for bfs
        queue<pair<int,int>> q; int level = 0;
        
        // Push all rotten oranges to queue
        for(int i=0; i<grid.size(); i++) 
            for(int j=0; j<grid[0].size(); j++) 
                if(grid[i][j]==2) q.push(make_pair(i, j));
        
        // Do BFS
        while(!q.empty())
        {
            // Process all nodes at same level together
            int size = q.size();
            while(size--)
            {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();
                // If above orange is fresh, make it rotten and push to queue
                if(i>0 && grid[i-1][j]==1) 
                    {grid[i-1][j]=2; q.push(make_pair(i-1, j));}
                // Same as above
                if(i<grid.size()-1 && grid[i+1][j]==1) 
                    {grid[i+1][j]=2; q.push(make_pair(i+1, j));}
                // Same as above
                if(j>0 && grid[i][j-1]==1) 
                    {grid[i][j-1]=2; q.push(make_pair(i, j-1));}
                // Same as above
                if(j<grid[0].size()-1 && grid[i][j+1]==1) 
                    {grid[i][j+1]=2; q.push(make_pair(i, j+1));}
            }
            // Increment level
            level++;
        }
        
        // If there are still fresh oranges, return -1
        for(int i=0; i<grid.size(); i++) 
            for(int j=0; j<grid[0].size(); j++) 
                if(grid[i][j]==1) return -1;
        
        // If level=0, return 0, else level-1
        return (level==0)?0:level-1;
    }
};
```

### Topological Sorting
```
class Solution
{
	public:
	//Function to return list containing vertices in Topological order. 
	void solve(int V, vector<int> adj[], vector<int>& ans, bool visited[], int src)
	{
	    visited[src]=true;
	    for(auto i:adj[src]) if(!visited[i]) solve(V, adj, ans, visited, i);
	    ans.push_back(src);
	}
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    bool visited[V]; vector<int> ans;
	    for(int i=0; i<V; i++) visited[i]=false;
	    for(int i=0; i<V; i++) if(!visited[i]) solve(V, adj, ans, visited, i);
	    reverse(ans.begin(), ans.end());
	    return ans;
	}
};
```

### Kahn's Algo
```
class Solution
{
	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    // Kahn's algo
	    // Make a degree array and queue for bfs
	    int degree[V]; queue<int> q; vector<int> ans;
	    // Mark all degree to 0
	    for(int i=0; i<V; i++) degree[i]=0;
	    // Now for all incoming edges, increase degree
	    for(int i=0; i<V; i++) for(auto j:adj[i]) degree[j]++;
	    // If there is any node with degree 0, we can
	    // start topological sort from there
	    for(int i=0; i<V; i++) if(degree[i]==0) q.push(i);
	    
	    // Do BFS
	    while(!q.empty())
	    {
	        // Process all nodes of same level together
	        int size = q.size();
	        while(size--)
	        {
	            int parent = q.front();
	            q.pop();
	            ans.push_back(parent);
	            // Decrement degree of connected nodes only
	            // And after doing so, if it becomes 0, then push to queue
	            for(auto j:adj[parent])
	            {
	                degree[j]--;
	                if(degree[j]==0) q.push(j);
	            }
	        }
	    }
	    
	    // Return ans
	    return ans;
	}
};
```

### Critical Connections in a Network
```
class Solution {
public:
    vector<vector<int>> ret;
    void dfs(vector<int> graph[], int parent[], int discovery[], int low[], bool ans[], bool visited[], int src, int disc)
    {
        visited[src]=true;
        discovery[src]=disc;
        low[src] = disc;
        for(auto i:graph[src])
        {
            parent[i]=src;
            // If parent then skip
            if(i==parent[src]) continue;
            // If visited then update low
            if(visited[i]) low[src] = min(low[src], discovery[i]);
            else
            {
                // Call dfs
                dfs(graph, parent, discovery, low, ans, visited, i, disc+1);
                // If my children cannot reach above me then i am articulation point
                if(low[i]>discovery[src])
                {
                    vector<int> temp;
                    temp.push_back(src);
                    temp.push_back(i);
                    ret.push_back(temp);
                }
                // Finally update your lowest reach
                low[src] = min(low[src], low[i]);
             }
        }
    }
    // Subhesh method, revisit
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        
        bool ans[n]; int parent[n]; int discovery[n]; int low[n]; bool visited[n]; vector<int> graph[n];
        
        for(int i=0; i<connections.size(); i++) 
        {
            graph[connections[i][0]].push_back(connections[i][1]); 
            graph[connections[i][1]].push_back(connections[i][0]);
        }
        for(int i=0; i<n; i++) visited[i]=false; 
        for(int i=0; i<n; i++) ans[i]=false; 
        for(int i=0; i<n; i++) parent[i]=-1;
    
        dfs(graph, parent, discovery, low, ans, visited, 0, 0);
    
        return ret;
    }
};
```

### No of islands 2
```
class Solution {
public:
    // Functions used for DSU
    int find(vector<int>& parent, int x)
    {
        if(parent[x]==x) return x;
        int temp = find(parent, parent[x]);
        parent[x]=temp;
        return temp;
    }
    void myunion(vector<int>& parent, int x, int y, int& count)
    {
        int lox = find(parent, x);
        int loy = find(parent, y);
        if(lox != loy)
        {
            parent[loy] = lox;
            count--;
        }
    }
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        // All cells to be represented as DSU
        vector<int> parent(m*n); 
        // Visited set
        set<pair<int,int>> visited; 
        int count = 0; vector<int> ans;
        
        // Make every cell a parent of itself
        for(int i=0; i<parent.size(); i++) parent[i]=i;
        
        // For each land addition do union and push to ans
        for(int i=0; i<positions.size(); i++)
        {
            int r = positions[i][0]; int c = positions[i][1];
            // If this cell is already made as land
            if(visited.find(make_pair(r, c))!=visited.end())
            {
                ans.push_back(count);
                continue;
            }
            int cell = r*n + c;
            // A new cell of land (an island is added)
            count++;
            // Mark the new cell as visited
            visited.insert(make_pair(r,c));
            // Perform union
            if(r>0 && visited.find(make_pair(r-1, c))!=visited.end()) 
                myunion(parent, cell, cell-n, count);
            if(r<m-1 && visited.find(make_pair(r+1, c))!=visited.end()) 
                myunion(parent, cell, cell+n, count);
            if(c>0 && visited.find(make_pair(r, c-1))!=visited.end()) 
                myunion(parent, cell, cell-1, count);
            if(c<n-1 && visited.find(make_pair(r, c+1))!=visited.end()) 
                myunion(parent, cell, cell+1, count);
            // Push the count to ans
            ans.push_back(count);
        }
        
        // Return the ans array
        return ans;
    }
};
```

### Maximum Flow
```
class Solution
{
public:
bool bfs(vector<vector<int>>& adjMat, int parent[], int src)
    {
        // Queue for bfs
        // Visited array marked with false
        queue<int> q; vector<bool> visited(adjMat.size(), false);
        // Set parent of every node to -1
        for(int i=0; i<adjMat.size(); i++) parent[i]=-1;
        // Push src and mark it visited
        q.push(src); visited[src]=true;
        // Do normal bfs
        while(!q.empty())
        {
            int node = q.front(); q.pop();
            for(int nbr=0; nbr<adjMat.size(); nbr++)
            {
                if(!visited[nbr] && adjMat[node][nbr]>0)
                {
                    q.push(nbr);
                    parent[nbr]=node;
                    visited[nbr]=true;
                }
            }
        }
        // If we cannot reach the last node return false
        if(parent[adjMat.size()-1]==-1) return false;
        // Else return true
        return true;
    }
    int solve(int N,int M,vector<vector<int>> Edges)
    {
        // We use adjacency matrix here
        vector<vector<int>> adjMat(N, vector<int>(N, 0)); int parent[N]; int ans = 0;
        // Add edges to matrix
        for(int i=0; i<Edges.size(); i++) 
        {
            adjMat[Edges[i][0]-1][Edges[i][1]-1]+=Edges[i][2];
            adjMat[Edges[i][1]-1][Edges[i][0]-1]+=Edges[i][2];
        }
        
        // Run bfs till condition is satisfied
        while(bfs(adjMat, parent, 0))
        {
            int minedge = 100000;
            // Find the minimum edge in the path
            for(int i=N-1; i!=0; i=parent[i])
            {
                minedge = min(minedge, adjMat[parent[i]][i]);
            }
            // Add back edge and forward edges
            for(int i=N-1; i!=0; i=parent[i])
            {
                adjMat[parent[i]][i]-=minedge;
                adjMat[i][parent[i]]+=minedge;
            }
            // Increment ans with min edge
            ans += minedge;
        }
        
        // Return ans
        return ans;
    }
};
```