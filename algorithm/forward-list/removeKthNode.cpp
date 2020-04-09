#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int val):val(val),next(nullptr){}
};
Node *removeKthNode(Node *head, int k){
    if(head==nullptr || k<1)return head;
    if(k==1){
        Node *del = head;
        head = head->next;
        delete del;
        del = nullptr;
        return head;
    }
    Node *cur = head;
    for(int i=1; i<k-1; i++){
        if(cur)cur = cur->next;
        else return head;
    }
    if(cur==nullptr || cur->next==nullptr)return head;
    Node *del = cur->next;
    cur->next = del->next;
    delete del;
    del = nullptr;
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
    n1->next->next = new Node(3);

    printList(removeKthNode(n1, 1));

    return 0;
}
