#include <bits/stdc++.h>

using namespace std;

// Node structure and constructors to create Nodes
struct Node
{
    int data;
    Node* next;

    Node()
    {
        this->data = 0;
        this->next = NULL;
    }

    Node(int val)
    {
        this->data = val;
        this->next = NULL;
    }

    Node(int val, Node* nextref)
    {
        this->data = val;
        this->next = nextref;
    }
};

Node* merge(Node* l1, Node* l2)
{
    if(l1==NULL && l2==NULL) return NULL;
        
    Node* head=NULL; Node* tail=NULL;
    
    while(l1!=NULL && l2!=NULL)
    {
        Node* temp = new Node(min(l1->data, l2->data));
        
        if(l1->data < l2->data) l1 = l1->next;
        else l2 = l2->next;
        
        if(head == NULL) {head = tail = temp;}
        else {tail->next = temp; tail=tail->next;}
    }
    
    while(l1!=NULL)
    {
        Node* temp = new Node(l1->data);
        l1 = l1->next;
        
        if(head == NULL) {head = tail = temp;}
        else {tail->next = temp; tail=tail->next;}
    }
    
    while(l2!=NULL)
    {
        Node* temp = new Node(l2->data);
        l2 = l2->next;
        
        if(head == NULL) {head = tail = temp;}
        else {tail->next = temp; tail=tail->next;}
    }
    
    return head;
}

void mergesort(Node ** head)
{
    if(*head==NULL || (*head)->next==NULL) return;

    Node *a, *b, *slow=*head, *fast=(*head)->next;

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    a = *head;
    b = slow->next;
    slow->next = NULL;

    mergesort(&a);
    mergesort(&b);

    *head = merge(a, b);
}

int main()
{
    // Create a new linked list
    Node * head = new Node(5, new Node(4, new Node(3, new Node(2, new Node(1)))));

    mergesort(&head);

    // Print the new linked list
    while(head)
    {
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;

    return 0;
}