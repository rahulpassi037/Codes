## Trees

### Level order traversal
```
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        // Initialize variables
        vector<vector<int> > ans;
        queue<TreeNode*> q;

        // If tree is empty then return empty vector
        if(!root) return ans;
        q.push(root);
        
        // We process a single level each time
        while(!q.empty())
        {
            int size = q.size();
            vector<int> temp;
            
            while(size--)
            {
                TreeNode* tempnode = q.front();
                q.pop();
                if(tempnode->left) q.push(tempnode->left);
                if(tempnode->right) q.push(tempnode->right);
                temp.push_back(tempnode->val);
            }
            
            // Push to ans array
            ans.push_back(temp);
        }
        
        // Return ans
        return ans;
    }
};
```

### BST to GST
```
class Solution {
public:
    int sum;
    // Do a reverse inorder traversal and keep filling the nodes
    // Keep a global variable for sum
    TreeNode* bstToGst(TreeNode* root) {
        if(!root) return NULL;
        bstToGst(root->right);
        sum += root->val;
        root->val = sum;
        bstToGst(root->left);
        return root;
    }
};
```

### Right side view
```
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        
        // If tree is empty return null
        if(!root) return ans;
        
        queue<TreeNode*> q;
        q.push(root);
        
        // Normal level order traversal and print last node of each level
        while(!q.empty())
        {
            int size = q.size();
            while(size--)
            {
                TreeNode* temp = q.front();
                q.pop();
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
                if(size==0) ans.push_back(temp->val);
            }
        }
        
        return ans;
    }
};
```

### Boundary Traversal
```
class Solution {
public:
    vector<int> ans;
    
    // It adds nodes only present in left boundary, except leaves
    void leftBoundary(TreeNode* root)
    {
        // If leaf node then return else push data
        if(root->left==NULL && root->right==NULL) return;
        ans.push_back(root->val);
        // If left node is present then call it else right node
        if(root->left!=NULL) leftBoundary(root->left);
        else leftBoundary(root->right);
    }
    
    // It adds nodes only present in right boundary, except leaves
    void rightBoundary(TreeNode* root)
    {
        // If leaf node then return
        if(root->left==NULL && root->right==NULL) return;
        // If right node is present then call it else left node
        if(root->right != NULL) rightBoundary(root->right);
        else rightBoundary(root->left);
        // Push the data while returning
        ans.push_back(root->val);
    }
    
    // Normal 'inorder' traversal to push leaves
    void leaves(TreeNode* root)
    {
        if(!root) return;
        leaves(root->left);
        if(root->left==NULL && root->right==NULL) ans.push_back(root->val);
        leaves(root->right);
    }
    
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        
        // First push root
        ans.push_back(root->val);
        
        // If left subtree is non empty the call left boundary
        // Leaves are not covered in this call
        if(root->left) leftBoundary(root->left);
        
        // If root is non leaf the call leaves function
        if(root->left!=NULL || root->right!=NULL) leaves(root);
        
        // If right subtree is non empty the call right boundary
        // Leaves are not covered in this call
        if(root->right) rightBoundary(root->right);
        
        // Return ans
        return ans;
    }
};
```

### Inorder Successor
```
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        // If there is a right subtree of node
        // Then inorder successor will be leftmost node in right subtree
        // Else the inorder successor will be the nearest node from p
        // Where we take the first left turn
        // If p is rightmost node then the ans is NULL
        TreeNode * ans = NULL;
        while(root != NULL)
        {
            if(p->val >= root->val) root = root->right;
            else
            {
                ans = root;
                root = root->left;
            }
        }
        return ans;
    }
};
```

### LCA in BST
```
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // If both the nodes are in right sides then LCA is in right side
        if(root->val>p->val && root->val>q->val) return lowestCommonAncestor(root->left, p, q);
        // Else if both nodes are in left side then LCA is in left side
        else if(root->val<p->val && root->val<q->val) return lowestCommonAncestor(root->right, p, q);
        // The first node for which both nodes are on different side is LCA
        else return root;
    }
};
```

### LCA in Binary Tree
```
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        // Get answers from both sides
        TreeNode * leftans = lowestCommonAncestor(root->left, p, q);
        TreeNode * rightans = lowestCommonAncestor(root->right, p, q);
        
        // If both sides don't contain answer, then check if you yourself
        // are one of the target node or not
        if(leftans == NULL && rightans == NULL)
        {
            if(root == p || root == q) return root;
            else return NULL;
        }
        
        // If one of the two sides contain answer
        // Check if you are one of the target node
        // If that is the case then you are the LCA
        // Else just return the node you got as non NULL
        else if(leftans == NULL || rightans == NULL)
        {
            if(root == p || root == q) return root;
            if(leftans == NULL) return rightans;
            return leftans;
        }
        
        // If both sides contain answer then you are the LCA
        else return root;
    }
};
```

### Binary tree to Linked list
```
class Solution {
public:
    // This function is used to flatten the tree
    // Problem with brute force is that we need to traverse the left LL to join
    TreeNode* helper(TreeNode* root)
    {
        if(!root) return NULL;
        
        // Flatten left and right subtrees and get pointers
        TreeNode* lreturn = helper(root->left);
        TreeNode* rreturn = helper(root->right);
        
        // If the node is a leaf node then return it
        if(lreturn==NULL && rreturn==NULL)
        {
            root->left = NULL;
            root->right = NULL;
            return root;
        }
        
        // Left is non null, we need to just place left list in right side of original node
        // We return the last pointer in the left list
        // This is useful because we don't want to traverse the whole list again
        else if(lreturn!=NULL && rreturn==NULL)
        {
            swap(root->left, root->right);
            root->left = NULL;
            return lreturn;
        }
        
        // Again the right list is at correct place, we just need to return the last ptr
        else if(lreturn==NULL && rreturn!=NULL)
        {
            root->left = NULL;
            return rreturn;
        }
        
        // Since both are non null
        // We place right list at end of left list
        // Now place left list at right side of node and set left child to null
        // Finally return the last pointer of right child
        else
        {
            lreturn->right = root->right;
            root->right = root->left;
            root->left = NULL;
            return rreturn;
        }
    }
    void flatten(TreeNode* root) {
        helper(root);
    }
};
```

### Binary Tree to Circular Doubly Linked List
```
class Solution
{
  public:
    // This function concatenates 2 circular LL
    Node *concatenate(Node *leftList, Node *rightList)
    {
        // If any list is empty, simply return the other list
        if (leftList == NULL) return rightList;
        if (rightList == NULL) return leftList;
        
        // Find last nodes of each list
        Node *leftLast = leftList->left;
        Node *rightLast = rightList->left;
    
        // Connect the 2 circular LL
        leftLast->right = rightList;
        rightList->left = leftLast;
        leftList->left = rightLast;
        rightLast->right = leftList;
  
        // Return the first pointer of the new LL
        return leftList;
    }
    Node *bTreeToCList(Node *root)
    {
        if(root == NULL) return NULL;
        
        // Make left and right subtree as Circular LL
        Node * lreturn = bTreeToCList(root->left);
        Node * rreturn = bTreeToCList(root->right);

        // Make root as a single node
        root->left = root->right = root;
  
        // Concatenate left + root + right to form the complete list
        return concatenate(concatenate(lreturn, root), rreturn);
    }
};
```

### Construct from inorder and preorder
```
class Solution {
public:
    // Map denotes val->index mapping for inorder array
    unordered_map<int, int> mapping;
    TreeNode* construct(vector<int>& pre, int ps, int pe, vector<int>& in, int is, int ie)
    {
        // If there is no node to construct
        if(ps>pe || is>ie) return NULL;
        
        // Construct the node from first element of preorder
        TreeNode* root = new TreeNode(pre[ps]);
        // Get the index of this element in the inorder array
        int idx = mapping[pre[ps]];
        // No of elements that are going in the left subtree
        int count = idx - is;
        // Call for left and right subtree and append them
        root->left = construct(pre, ps+1, ps+count, in, is, idx-1);
        root->right = construct(pre, ps+count+1, pe, in, idx+1, ie);
        // Return the constructed root
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Create the mapping
        for(int i=0; i<inorder.size(); i++) mapping[inorder[i]] = i;
        
        // Construct the binary tree and return ans
        TreeNode* ans = construct(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
        return ans;
    }
};
```

### Construct from inorder and postorder
```
class Solution {
public:
    // Mapping denotes value->index mapping for the inorder array
    unordered_map<int, int> mapping;
    TreeNode* construct(vector<int>& post, int ps, int pe, vector<int>& in, int is, int ie)
    {
        // If there is no node to construct
        if(ps>pe || is>ie) return NULL;
        // Construct the new node as last node of the post order array
        TreeNode* root = new TreeNode(post[pe]);
        // Get the index of this element in the inorder array
        int idx = mapping[post[pe]];
        // No of elements that go into the left subtree
        int count = idx - is;
        // Call for both subtrees and append
        root->left = construct(post, ps, ps+count-1, in, is, idx-1);
        root->right = construct(post, ps+count, pe-1, in, idx+1, ie);
        // Return the constructed root
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // Create the mapping for inorder array
        for(int i=0; i<inorder.size(); i++) mapping[inorder[i]] = i;
        // Construct the tree and return 
        TreeNode* ans = construct(postorder, 0, postorder.size()-1, inorder, 0, inorder.size()-1);
        return ans;
    }
};
```

### BST from Postorder
```
int i;
Node* construct(int post[], int ma, int mi)
{
    // If array is over or any node goes out of bound then return null
    if(i<0 || post[i]<mi || post[i]>ma) return NULL;
    // Else create a new node from the last node of the postorder array
    Node* root = new Node(post[i]);
    i--;
    // Call for right subtree first and then call for left subtree
    root->right = construct(post, ma, root->data+1);
    root->left = construct(post, root->data-1, mi);
    // Return the root of the constructed tree
    return root;
}

Node *constructTree (int post[], int size)
{
    // last element denotes the root of the bst
    i = size-1;
    Node* ans = construct(post, INT_MAX, INT_MIN);
    return ans;
}
```

### Serialize and Deserialize
```
class Codec {
public:
    string serialstr;
    vector<string> deserial;
    int i;
    // We use preorder in this
    // Level order approach gives TLE
    void serialhelper(TreeNode* root)
    {
        if(!root)
        {
            serialstr.append("#,");
            return;
        }
        serialstr.append(to_string(root->val));
        serialstr.push_back(',');
        serialhelper(root->left);
        serialhelper(root->right);
    }
    // Encodes a tree to a single string.
    // Call serial helper and remove the extra comma that is inserted
    string serialize(TreeNode* root) {
        serialhelper(root);
        serialstr.pop_back();
        return serialstr;
    }
    // While deserialising check the value and construct nodes accordingly
    TreeNode* deserialhelper()
    {
        if(deserial[i].compare("#") == 0) 
        {
            i++;
            return NULL;
        }
        TreeNode* temp = new TreeNode(stoi(deserial[i]));
        i++;
        temp->left = deserialhelper();
        temp->right = deserialhelper();
        return temp;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // From the string you get extract the values and call deserial function
        TreeNode* root;
        stringstream ss(data);
        string word;
        
        while(ss.good())
        {
            getline(ss, word, ',');
            deserial.push_back(word);
        }
        i = 0;
        root = deserialhelper();
        
        return root;
    }
};
```