#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <set>

using namespace std;

typedef struct Node *pNode, *pTree;

struct Node
{
    Node(int val=0):val(val),left(NULL),rigt(NULL) {}
    int val;
    pTree left, rigt;
};
bool valid(const pNode& node, const set<pNode>& visited)
{
    return (visited.find(node->rigt)!=visited.end() && visited.find(node->left)!=visited.end());
}
int treeMaxSum(const pTree& root)
{
    if(root == NULL)
        return 0;

    stack<pNode> nodes;
    stack<pNode> path;
    set<pNode> visited;
    visited.insert(NULL);
    int maxSum = 0;
    int curSum = 0;
    pNode cur=NULL;
    nodes.push(root);
    //path.push(root);

    while(!nodes.empty())
    {
        cur = nodes.top();
        nodes.pop();

        path.push(cur);
        curSum += cur->val;
        visited.insert(cur);
        if(cur->left==NULL && cur->rigt==NULL)
        {
            maxSum = curSum>maxSum?curSum:maxSum;
            while(!path.empty() && valid(path.top(), visited))
            {
                curSum -= path.top()->val;
                path.pop();
            }
        }

        if(cur->rigt)
            nodes.push(cur->rigt);
        if(cur->left)
            nodes.push(cur->left);
    }
    return maxSum;
}

pTree buildTree()
{
    pTree root = new Node(0);
    root->left = new Node(3);
    root->rigt = new Node(5);

    root->left->left = new Node(1);
    root->left->rigt = new Node(6);

    root->rigt->left = new Node(10);
    root->rigt->rigt = new Node(7);

    return root;
}
int main()
{
    cout<<"Hello World!"<<endl;
    pTree root = buildTree();
    int sum = treeMaxSum(root);
    cout<<sum<<endl;

    return 0;
}
