#include <bits/stdc++.h>

using namespace std;

void heapify(int arr[], int n, int i)
{
    // Initialize largest as root and find left and right children
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    // If left is larger than root, assign largest to this
    if(left < n && arr[left]>arr[largest]) largest = left;

    // If right is larger than largest found till now, assign it
    if(right < n && arr[right]>arr[largest]) largest = right;

    // If largest is not root, then swap both indices and call heapify for subtrees
    if(largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n)
{
    // We don't need to heapify all elements as the leaf nodes already follow heap property
    // Just heapify all non leaf nodes
    // Find the index of the first non leaf node in opposite direction
    int startidx = n/2-1;

    for(int i=startidx; i>=0; i--)
    {
        heapify(arr, n, i);
    }
}

void heapSort(int arr[], int n)
{
    // Build the heap in O(n) time
    buildHeap(arr, n);

    // Heapify the swapped element with reduced size
    for(int i=n-1; i>=0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    int arr[] = {1, 4, 7, 2, 19, 1, -1, 23, 45, 65, 73, 56, 100, 0};
    int n = sizeof(arr)/sizeof(int);

    heapSort(arr, n);

    for(int i=0; i<n; i++) cout<<arr[i]<<" ";
    cout<<endl;

    return 0;
}