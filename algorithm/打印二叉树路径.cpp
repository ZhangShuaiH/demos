#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <string>

using namespace std;

typedef struct Node *pNode, *pTree;

struct Node
{
    Node(int val=0):val(val),left(NULL),rigt(NULL) {}
    int val;
    pTree left, rigt;
};
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

void printPath(vector<pNode>& path, const pTree& root, const int pos)
{
    if(root == NULL) return;

    if(root->left==NULL && root->rigt==NULL)
    {
        for(size_t i=0; i<path.size(); i++)
        {
            cout<<path[i]->val<<" ";
        }
        cout<<endl;
    }
    path.push_back(root->left);
    printPath(path, root->left, pos+1);
    path.pop_back();
    path.push_back(root->rigt);
    printPath(path, root->rigt, pos+1);
    path.pop_back();
}

int main()
{
    pTree root = buildTree();
    vector<pNode> path;
    path.push_back(root);
    printPath(path, root, 0);

    return 0;
}
