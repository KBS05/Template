#include<bits/stdc++.h>
using namespace std;
#define int long long int

class binaryTree{
private:
    class Node{
    public:
        int data;
        Node *left,*right;
        Node(){
            data=-1;
            left=NULL;
            right=NULL;
        }
        Node(int x){
            data=x;
            left=NULL;
            right=NULL;
        }
    };

    // Create root Node
    Node* root;

    Node* insertNode_(Node* cur,int x){
        if(cur==NULL){
            cur=new Node(x);
            return cur;
        }
        queue<Node*>qe;
        qe.push(cur);
        while(!qe.empty()){
            Node* tmp=qe.front();
            qe.pop();
            if(tmp->left)   qe.push(tmp->left);
            else{
                tmp->left=new Node(x);
                return cur;
            }
            if(tmp->right)  qe.push(tmp->right);
            else{
                tmp->right=new Node(x);
                return cur;
            }
        }
        return cur;
    }
    // Recursive Traversal
    void inorder_traverse(Node* cur){
        if(!cur)    return;
        if(cur->left)   inorder_traverse(cur->left);
        cout << (cur->data) << " ";
        if(cur->right)  inorder_traverse(cur->right);
    }
    void preorder_traverse(Node* cur){
        if(!cur)    return;
        cout << (cur->data) << " ";
        if(cur->left)   preorder_traverse(cur->left);
        if(cur->right)  preorder_traverse(cur->right);
    }
    void postorder_traverse(Node* cur){
        if(!cur)    return;
        if(cur->left)   postorder_traverse(cur->left);
        if(cur->right)  postorder_traverse(cur->right);
        cout << (cur->data) << " ";
    }
    void levelorder_traverse(vector<int>&res,Node* cur){
        if(!cur)   return;
        queue<Node*>qe;
        qe.push(cur);
        while(!qe.empty()){
            int t=qe.size();
            while(t--){
                cur=qe.front();
                qe.pop();
                res.push_back(cur->data);
                if(cur->left)   qe.push(cur->left);
                if(cur->right)  qe.push(cur->right);
            }
        }
    }
    // Iterative Traversal
    vector<int> inorder_iterative(TreeNode* root) {
        vector<int>ans;
        if(root == NULL)    return ans;
        
        stack<TreeNode*>st;
        TreeNode *curr = root;
        
        while(true){
            if(curr != NULL){
                st.push(curr);
                curr = curr->left;
            }
            else{
                if(st.empty()){
                    break;
                }
                curr = st.top();
                st.pop();
                ans.push_back(curr->val);
                curr = curr->right;
            }
        }
        
        return ans;
    }
    vector<int> preorder_iterative(TreeNode* root) {
        vector<int>ans;
        if(!root){
            return ans;
        }
        
        stack<TreeNode*>st;
        st.push(root);
        
        while(!st.empty()){
            TreeNode *curr = st.top();
            st.pop();
            
            ans.push_back(curr->val);
            // first push right node into the stack then left node, as we have to access first left one then right (so left should be on the top)
            if(curr->right) st.push(curr->right);
            if(curr->left)  st.push(curr->left);
        }
        
        return ans;
    }
    void postorder_iterative(vector<int>&res,Node* cur){
        // using 2 stack
        if(!cur)    return;
        stack<Node*>st1,st2;
        st1.push(cur);
        Node* tmp;
        while(!st1.empty()){
            tmp=st1.top();
            st1.pop();
            st2.push(tmp);
            if(tmp->left)   st1.push(tmp->left);
            if(tmp->right)  st1.push(tmp->right);
        }
        while(!st2.empty()){
            tmp=st2.top();
            st2.pop();
            res.push_back(tmp->data);
        }
    }
    void postorder_iterative1(vector<int>&res,Node* cur){
        // using 1 stack
        if(!cur)    return;
        stack<Node*>st;
        do{
            while(cur!=NULL){
                if(cur->right)  st.push(cur->right);
                st.push(cur);
                cur=cur->left;
            }
            cur=st.top();
            st.pop();
            // If poped node has a right child and is not processed yet, then first process it then current node
            if((curr->right!=NULL) && (!st.empty()) && (st.top()==curr->right)){
                st.pop();
                st.push(cur);
                cur=cur->right;
            }
            else{
                res.push_back(root->data);
                cur=NULL;
            }
        }while(!st.empty());
    }
public:
    binaryTree(){ root=NULL; }
    void insertNode(int x){ root=insertNode_(root,x); }
    void inorder(){ inorder_traverse(root); }
    void preorder(){ preorder_traverse(root); }
    void postorder(){ postorder_traverse(root); }
    vector<int> levelorder(){
        vector<int>res;
        levelorder_traverse(res,root);
        return res;
    }
    vector<int> inorder_iterative(){
        vector<int>res;
        inorder_iterative(res,root);
        return res;
    }
    vector<int> preorder_iterative(){
        vector<int>res;
        preorder_iterative(res,root);
        return res;
    }
    vector<int> postorder_iterative(){
        vector<int>res;
        postorder_iterative(res,root);
        return res;
    }
};
/******************************************************************************************************************/
// Construct Tree from Pre-Order and Post-Order Traversal
Problem Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/

// first find index in post-order traversal for each node in pre-order traversal;
unordered_map<int,int>index;
void storeIndex(vector<int>&v){
    int id=0;
    for(int x:v){
        index[x]=id;id++;
    }
}
TreeNode* construct(vector<int>&pre,vector<int>&post,int l1,int r1,int l2,int r2){
        TreeNode* tmp=new TreeNode(pre[l1]);
        if(l1==r1)  return tmp;
        int nxt=pre[l1+1];
        int postId=index[nxt];
        int rem=postId-l2+1;
        tmp->left=construct(pre,post,l1+1,l1+rem,l2,l2+rem-1);
        if(postId+1==r2)    return tmp;
        tmp->right=construct(pre,post,l1+rem+1,r1,postId+1,r2-1);
        return tmp;
}
TreeNode* constructFromPrePost(vector<int>& preOrder, vector<int>& postOrder) {
        storeIndex(postOrder);
        const int n=preOrder.size();
        return construct(preOrder,postOrder,0,n-1,0,n-1);
}

/******************************************************************************************************************/
// Construct Tree from Pre-Order and In-Order Traversal
Problem Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

class Solution {
    unordered_map<int,int>idIn;
    int pre;
public:
    TreeNode* fun(int l,int r,vector<int>& preorder, vector<int>& inorder){
        if(l>r){
            return NULL;
        }
        if(l==r){
            TreeNode *root = new TreeNode(preorder[pre++]);
            return root;
        }
        int x = preorder[pre++];
        TreeNode *root = new TreeNode(x);
        root->left = fun(l,idIn[x]-1,preorder,inorder);
        root->right = fun(idIn[x]+1,r,preorder,inorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        idIn.clear();
        for(int i=0;i<inorder.size();i++){
            idIn[inorder[i]]=i;
        }
        pre=0;
        return fun(0,inorder.size()-1,preorder,inorder);
    }
};

/******************************************************************************************************************/
// Construct Tree from Post-Order and In-Order Traversal
Problem Link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

class Solution {
    unordered_map<int,int>inId;
    int post;
public:
    TreeNode* fun(int l,int r,vector<int>& inorder, vector<int>& postorder){
        if(l>r){
            return NULL;
        }
        if(l==r){
            TreeNode *root = new TreeNode(postorder[post--]);
            return root;
        }
        int x = postorder[post--];
        TreeNode *root = new TreeNode(x);
        root->right = fun(inId[x]+1,r,inorder,postorder);
        root->left = fun(l,inId[x]-1,inorder,postorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for(int i=0;i<inorder.size();i++){
            inId[inorder[i]]=i;
        }
        post=inorder.size()-1;
        return fun(0,inorder.size()-1,inorder,postorder);
    }
};

/******************************************************************************************************************/
int32_t main(){

    binaryTree bt;
    int t;
    cin >> t;
    // t=7, {10,11,9,7,12,5,8};
    while(t--){
        int x;
        cin >> x;
        bt.insertNode(x);
    }
    vector<int>v1=bt.inorder_iterative();
    vector<int>v2=bt.preorder_iterative();
    vector<int>v3=bt.postorder_iterative();
    vector<int>v4=bt.levelorder();
    bt.inorder();cout<<endl;
    for(int x:v1)   cout<<x<<" ";cout<<endl;
    bt.preorder();cout<<endl;
    for(int x:v2)   cout<<x<<" ";cout<<endl;
    bt.postorder();cout<<endl;
    for(int x:v3)   cout<<x<<" ";cout<<endl;
    for(int x:v4)   cout<<x<<" ";cout<<endl;
    return 0;
}
