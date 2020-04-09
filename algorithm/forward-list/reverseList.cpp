#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int val):val(val),next(nullptr){}
};

Node *reverseList(Node* head){
    Node *pre = nullptr, *cur = head, *nxt = nullptr;
    while(cur){
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

void printList(Node* head){
    Node *cur = head;
    for(Node *cur=head; cur!=nullptr; cur=cur->next)cout<<cur->val<<",";
    cout<<endl;
}

int main(){
    Node *head = new Node(1);
    head->next = new Node(2);
    printList(reverseList(head));
    return 0;
}
