#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int val):val(val),next(nullptr){}
};

Node *reverseList_recurse(Node* head){// 递归实现
    if(head==nullptr || head->next==nullptr)return head;
    Node *tail = head->next;
    Node *newHead = reverseList_recurse(head->next);
    tail->next = head;
    head->next = nullptr;
    return newHead;
}

void printList(Node* head){
    Node *cur = head;
    for(Node *cur=head; cur!=nullptr; cur=cur->next)cout<<cur->val<<"->";
    cout<<endl;
}

int main(){
    Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    printList(reverseList_recurse(head));
    return 0;
}











