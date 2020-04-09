#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int val):val(val),next(nullptr){}
};
// 方法 1
Node *mergeTwoSortedList(Node *n1, Node *n2){// 新建临时节点，更易理解
    Node *head = new Node(-1);
    Node *cur = head;
    while (n1 && n2) {
        if(n1->val <= n2->val){
            cur->next = n1;
            n1 = n1->next;
        }else {
            cur->next = n2;
            n2 = n2->next;
        }
        cur = cur->next;
    }
    cur->next = n1 != nullptr ? n1 : n2;
    cur = head;
    head = head->next;
    delete cur;
    cur = nullptr;
    return head;
}
// 方法 2
Node *mergeTwoSortedList1(Node *n1, Node *n2){
    if(n1==nullptr || n2==nullptr)return n1!=nullptr?n1:n2;
    Node *head = n1->val<=n2->val ? n1 : n2;
    Node *cur = head;
    if(head == n1)n1=n1->next;
    else n2 = n2->next;
    while (n1 && n2) {
        if(n1->val <= n2->val){
            cur->next = n1;
            n1 = n1->next;
        }else {
            cur->next = n2;
            n2 = n2->next;
        }
        cur = cur->next;
    }
    cur->next = n1 != nullptr ? n1 : n2;

    return head;
}

void printList(Node* head){
    Node *cur = head;
    for(Node *cur=head; cur!=nullptr; cur=cur->next)cout<<cur->val<<",";
    cout<<endl;
}

int main(){
    Node *n1 = new Node(1);

    Node *n2 = new Node(2);
    n2->next = new Node(4);

    printList(mergeTwoSortedList(n1, n2));

    return 0;
}
