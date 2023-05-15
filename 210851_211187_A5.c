#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include <assert.h>

int *improvedc; // This is the temporary array used in Improved MergeSort in order to save the time to make and free the temporary array
int comparisons1, comparisons2; // These will be used to find all the number of Comparisons in QuickSort and MergeSort
int partition(int* a,int s,int e)
{
    int x=a[s]; // Defining the Pivot
    s+=1;
    for(int i=s;i<=e;)
    {
        if(a[i]>x) // Finding all the elements larger and smaller and shifting it to the right and left side of pivot
        {
            int t=a[i];
            a[i]=a[e];
            a[e]=t;
            e--;
        }
        else
        {
            i++;
        }
        comparisons2++;
    }
    a[s-1]=a[e]; // putting the pivot in between
    a[e]=x;
    return e;
}
void QS(int *a,int s,int e)
{
    if(s<e)
    {
        int i1=partition(a,s,e);
        QS(a,s,i1-1);
        QS(a,i1+1,e);
    }
}
int merge(int *a1,int s1,int *a2,int s2,int* a)
{
    int q=0,p=0,r=0; // p and q are iterators for both the arrays and r is the iterator for the final array
    while(p<s1&&q<s2)
    {
        if(a1[p]<=a2[q])
        {
            a[r]=a1[p];
            p++;r++;
        }
        else
        {
            a[r]=a2[q];
            q++;r++;
        }
        comparisons1++;
    }
    while(p<s1) // putting the leftout elements in the array
    {
        a[r]=a1[p];
        p++;r++;
    }
    while(q<s2)
    {
        a[r] = a1[q];
        q++;r++;
    }
    return 0;
}
void mergeSort(int a[],int s,int e)
{
    if(s<e)
    {
        int mid=(s+e)/2;
        mergeSort(a,s,mid); // breaking the array till only one element is left and then we start merging
        mergeSort(a,mid+1,e);
        int *c=(int *)malloc(sizeof(int)*(e-s+1)); // temporary array to store the sorted elements
        merge(a+s,mid-s+1,a+mid+1,e-mid,c);
        for(int i=s;i<=e;i++)
        {
            a[i]=c[i-s]; // copying the sorted elements in the array
        }
        free(c);
    }
}
int improvedMerge(int *a1,int s1,int *a2,int s2,int* a)
{
    int q=0,p=0,r=0;
    while(p<s1&&q<s2)
    {
        if(a1[p]<=a2[q])
        {
            a[r]=a1[p];
            p++;r++;
        }
        else
        {
            a[r]=a2[q];
            q++;r++;
        }
        comparisons1++;
    }
    while(p<s1) // we have removed the second while loop in the improved mergesort because it was not necessary
    {
        a[r]=a1[p];
        p++;r++;
    }
    return q;
}
void improvedMergeSort(int a[],int s,int e)
{
    if(s<e)
    {
        int mid=(s+e)/2;
        improvedMergeSort(a,s,mid);
        improvedMergeSort(a,mid+1,e);
        int k = improvedMerge(a+s,mid-s+1,a+mid+1,e-mid,improvedc);
        for(int i=s;i<mid+1+k;i++)
        {
            a[i]=improvedc[i-s];
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    improvedc = (int *)malloc(sizeof(int)*n); // defining the size of temporary array which will be used in improved Mergesort
    int arr[n];
    int arr2[n];
    clock_t start1, end1, start2, end2; // for measuring Time
    unsigned long long tot_time1=0, tot_time2 = 0, outperformedQS = 0, T[n]; // this array will be used in Second part of assignment
    comparisons1 = 0;
    comparisons2 = 0;
    srand(clock());
    for(int k = 0; k < 500; k++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand(); // putting random elements in array
            arr2[i]=arr[i];
        }
        start1 = clock();
        QS(arr, 0, n - 1); // measuring time for Quicksort
        end1 = clock();
        tot_time1 += (end1-start1);
        start2 = clock();
        improvedMergeSort(arr2, 0, n-1); // Measuring time for MergeSort
        end2 = clock();
        tot_time2 += (end2-start2);
        if(end2-start2 < end1-start1) outperformedQS++; // This stores how many times MergeSort outperformed QuickSort
    }
    printf("QS = %.6lf \nImproved MergeSort = %.6lf \nNumber of Times Improved MergeSort Outperformed Quicksort = %lu", (double)((tot_time1)/CLOCKS_PER_SEC)/500, (double)((tot_time2)/CLOCKS_PER_SEC)/500, outperformedQS);
    return 0;
}