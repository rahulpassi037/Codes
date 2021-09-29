#include <bits/stdc++.h>

using namespace std;

// Function for merging two sorted arrays
// Since the arrays to be merged will always be continuous
// The two arrays are seperated by mid
// We create a temporary array to store result of merged arrays
void merge(vector<int>& arr, int lo, int mid, int hi)
{
    vector<int> tmp(hi+1);
    int l1, l2, i;

    // Merge two sorted arrays
    for(l1=lo, l2=mid+1, i=lo; l1<=mid && l2<=hi; i++)
    {
        if(arr[l1] <= arr[l2]) tmp[i]=arr[l1++];
        else tmp[i] = arr[l2++];
    }

    // If one array is empty then copy the other array
    while(l1 <= mid) tmp[i++] = arr[l1++];
    while(l2 <= hi) tmp[i++] = arr[l2++];

    // Copy from temp array to original array
    for(i=lo; i<=hi; i++) arr[i] = tmp[i];
}

// Function to do mergesort
// Divides the array into two halves and 
// calls mergesort on individual arrays
// Then it merges the two sorted arrays
void mergesort(vector<int>& arr,int lo, int hi)
{
    // If array has size greater than 1, then only call mergesort
    if(lo < hi)
    {
        int mid = lo + (hi-lo)/2;
        mergesort(arr, lo, mid);
        mergesort(arr, mid+1, hi);
        merge(arr, lo, mid, hi);
    }
}

// Driver function
int main()
{
    vector<int> arr = {11, 23, 3, 2, 12, 89, 100, 122, 1, -10};

    mergesort(arr, 0, arr.size()-1);

    for(int i=0; i<arr.size(); i++) cout<<arr[i]<<" ";
    cout<<endl;

    return 0;
}