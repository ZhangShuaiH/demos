#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <iostream>

#include "mydebug.h"

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

void visit(Node* node){
    myDebug(node->data);
}

bool contains(list<Node*> visited, Node* node){
    for(list<Node*>::const_iterator itr = visited.cbegin(); itr != visited.cend(); itr++){
        if(node == (*itr))
            return true;
    }
    return false;
}
// 先序
void preErgodic(Node* root){
    list<Node*> stack;
    Node* top;
    stack.push_back(root);
    while (!stack.empty()) {
        top = stack.back();
        stack.pop_back();
        visit(top);
        if(top->right){
            stack.push_back(top->right);
        }
        if(top->left){
            stack.push_back(top->left);
        }
    }
}
// 中序
void midErgodic(Node* root){
    list<Node*> stack,visited;
    stack.push_back(root);
    while (!stack.empty()) {
        Node* top = stack.back();
        if(top->left && !contains(visited, top->left)){
            stack.push_back(top->left);
        }else{
            stack.pop_back();
            visit(top);
            visited.push_back(top);
            if(top->right){
                stack.push_back(top->right);
            }
        }
    }
}
// 后序
void postErgodic(Node* root){
    list<Node*> stack,visited;
    bool hasChidren;
    Node* top;
    stack.push_back(root);
    while(!stack.empty()){
        top = stack.back();
        hasChidren = false;
        if( top->right && !contains(visited, top->right) ){
            hasChidren = true;
            stack.push_back(top->right);
        }
        if( top->left && !contains(visited, top->left) ){
            hasChidren = true;
            stack.push_back(top->left);
        }
        if(!hasChidren){
            stack.pop_back();
            visit(top);
            visited.push_back(top);
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a123(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right->right = new Node(6);

    preErgodic(root);
//    midErgodic(root);
//    postErgodic(root);

    return a123.exec();
}
