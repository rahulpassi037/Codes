#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node * next;
};

void swapNodes(Node** head, int x, int y)
{
    // If x and y are same, do nothing
    if(x == y) return;

    // Search for x
    Node *prevX=NULL, *currX=*head;
    while(currX && currX->data!=x)
    {
        prevX = currX;
        currX = currX->next;
    }

    // Search for y
    Node *prevY=NULL, *currY=*head;
    while(currY && currY->data!=y)
    {
        prevY = currY;
        currY = currY->next;
    }

    // If x or y is not present
    if(currX==NULL || currY==NULL) return;

    // Change previous pointers
    if(prevX!=NULL) prevX->next = currY;
    else *head = currY;
    if(prevY!=NULL) prevY->next = currX;
    else *head = currX;

    // Change next pointers
    Node* temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

int main()
{
    
    return 0;
}