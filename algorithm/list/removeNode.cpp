#include <iostream>

struct Node{
    int val;
    Node *pre;
    Node *next;
    Node(int val):val(val),pre(nullptr),next(nullptr){}
};

void removeNode(Node *node){
    if(node==nullptr)return;
    if(node->pre)node->pre->next = node->next;
    if(node->next)node->next->pre = node->pre;
    delete node;
    node = nullptr;
}

void printList(Node *head){
    using namespace std;
    for(Node *cur=head; cur!=nullptr; cur=cur->next)cout<<cur->val<<",";
    cout<<endl;
}

int main(){
    Node *head = new Node(1);
    head->next = new Node(2);
    head->next->pre = head;
    removeNode(head->next);
    printList(head);
}
