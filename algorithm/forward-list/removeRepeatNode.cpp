#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int val):val(val),next(nullptr){}
};
Node *removeRepeatNode(Node *head){
    Node *first = new Node(-1);
    first->next = head;
    Node *n1, *n2, *delHead;
    n1 = first;
    n2 = first->next;

    while (n2 != nullptr) {
        if(n2->next==nullptr || n2->val!=n2->next->val){
            n1 = n2;
            n2 = n2->next;
            continue;
        }
        while (n2->next!=nullptr && n2->val==n2->next->val) {
            n2 = n2->next;
        }
        delHead = n1->next;
        n1->next = n2->next;
        n2->next = nullptr;
        n2 = n1->next;
        while (delHead) {
            Node *del = delHead;
            delHead = delHead->next;
            delete del;
            del = nullptr;
        }
    }
    head = first->next;
    delete first;
    first = nullptr;
    return head;
}
void printList(Node* head){
    Node *cur = head;
    for(Node *cur=head; cur!=nullptr; cur=cur->next)cout<<cur->val<<",";
    cout<<endl;
}

int main(){
    Node *n1 = new Node(1);
    n1->next = new Node(2);
    n1->next->next = new Node(2);

    printList(removeRepeatNode(n1));

    return 0;
}
