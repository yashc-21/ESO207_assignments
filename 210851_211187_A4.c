#include<stdio.h>
#include<time.h>
#include<stdlib.h>
typedef struct node{
    int v;// stores the value at that node
    int size;// stores the size of the subtree at that node
    struct node* left;// pointer to left child
    struct node* right;// pointer to right child
}Node;
int i=0;// variable used to form array from BST
Node* notNearlyBalanced=NULL;// pointer to the node which is not nearly balaced
Node* notNearlyBalancedParent=NULL;
Node** Traversal(Node* T,Node** arr)// function to convert BST to array
{
    Node* p=T;
    if(p==NULL)return arr;
    if((p->left)!=NULL)Traversal(p->left,arr);// adding values in the subtree left(p) to array
    arr[i]=p;// adding values at p to array
    i++;
    if((p->right)!=NULL)Traversal(p->right,arr);// adding values in the subtree right(p) to array
    return arr;
}
Node* Insert(Node* T,int value,Node* parent)
{
    Node* p=T;
    if(p==NULL)
    {
        p=(Node*)malloc(sizeof(Node));// creating node p
        p->v=value;// assigning value to the node created
        p->left=NULL;
        p->right=NULL;
        p->size=1;// assigning size of subtree at p
        return p;
    }
    else p->size=(p->size)+1;// increasing size by one as due to this insertion size of the subtree at p will increase by 1
    if(value<(p->v))
    {
        if(p->left==NULL)
        {
            p->left=(Node*)malloc(sizeof(Node));// creating node left(p)
            p->left->v=value;// assigning value to the node created
            p->left->left=NULL;
            p->left->right=NULL;
            p->left->size=1;// assigning size of subtree at left(p)
        }
        else Insert(p->left,value,p);// continue searching for the place where the value is to be inserted
    }
    else
    {
        if(p->right==NULL)
        {
            p->right=(Node*)malloc(sizeof(Node));// creating node right(p)
            p->right->v=value;// assigning value to the node created
            p->right->left=NULL;
            p->right->right=NULL;
            p->right->size=1;// assigning size of subtree at left(p)
        }
        else Insert(p->right,value,p);// continue searching for the place where the value is to be inserted
    }
    if((T->left==NULL)||(T->right==NULL))
    {
        if(T->size>0)
        {
            notNearlyBalanced=T;// assigning value of the current node
            notNearlyBalancedParent=parent;// storing the parent used in makeBalanced function
        }
    }
    else if((((3*(T->size))/4)<(T->left->size))||(((3*(T->size))/4)<(T->right->size)))// if current node is not nearly balaced
    {
        notNearlyBalanced=T;// assigning value of the current node
        notNearlyBalancedParent=parent;// storing the parent used in makeBalanced function
    }
    return p;
}
Node* makeBST(Node** arr,int i1,int i2)// makes perfectally balanced BST from array
{
    if(i1>i2)return NULL;// if no value is left to make BST
    Node* p;// pointer to the BST
    int mid=(i1+i2)/2;
    p=arr[mid];// making root of tree/subtree
    p->size=i2-i1+1;// storing new size at the nodes
    p->left=makeBST(arr,i1,mid-1);// making left subtree
    p->right=makeBST(arr,mid+1,i2);// making right subtree
    return p;
}
Node* makeBalanced(Node* T)
{
    i=0;
    Node** arr=(Node**)malloc(sizeof(Node*)*(T->size));// creating array to store pointers to the nodes of BST in ascending order
    arr=Traversal(T,arr);// assigning values to array
    T=makeBST(arr,0,i-1);// making perfectly balanced BST from array
    if(notNearlyBalancedParent==NULL)
    {
        return T;// if no parent returning pointer to new root
    }
    if(notNearlyBalancedParent->v>notNearlyBalanced->v)
    {
        notNearlyBalancedParent->left=T;// connecting the subtree to parent
    }
    else
    {
        notNearlyBalancedParent->right=T;// connecting the subtree to parent
    }
    notNearlyBalanced=NULL;// now every node is nearly balanced
    notNearlyBalancedParent=NULL;
    free(arr);
    return T;
}
int main()
{
    double * Tarray = (double *)malloc(sizeof(double)*10000000);// array to store time of inserting values
    Node* T=NULL;
    clock_t start_t, end_t;
    clock_t start = clock();
    for(int j=0;j<10000000;j++)
    {
        start_t = clock();// noting start time
        T=Insert(T,j+1,NULL);
        if(notNearlyBalanced!=NULL)
        {
            if(notNearlyBalancedParent==NULL)
            {
                T=makeBalanced(notNearlyBalanced);
            }
            else
            {
                makeBalanced(notNearlyBalanced);
            }
        }
        end_t = clock();// noting end time
        Tarray[j] = (double)(end_t - start_t) / CLOCKS_PER_SEC;// storing time in array
        printf("%lf (%d)\n",Tarray[j],j);
    }
    clock_t end = clock();
    printf("%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("done without error");
    // csv realted work...
}