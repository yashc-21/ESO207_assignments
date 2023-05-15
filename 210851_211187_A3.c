#include<stdio.h>
#include <stdlib.h>
//using linked list for making stack
typedef struct Stack_node{
     int v;// stores the integer in the corresponding stack node
     struct Stack_node* prev;// pointer to the previous node in stack
     struct Stack_node* next;// pointer to the next node in stack
}Stack_node;
//making a structure to store the information of stack size and pointer to head node
typedef struct Stack{
     int size;// variable to store the size of the stack
     struct Stack_node* top;// pointer to head node
}Stack;
int IsEmpty(Stack* S)// this function return 1 if the stack is empty else 0
{
    if((S->size)==0)return 1;
    return 0;
}
int Top(Stack* S)// returns the value stored in the Top node of the Stack
{
    return((S->top)->v);
}
Stack * CreateEmptyStack()
{
    Stack* S=(Stack*)malloc(sizeof(Stack));// allocating memory for the structure that will be storing the details of the Stack
    S->size=0;// initialising the size of array as 0
    S->top=NULL;// initialising the pointer to head node as NULL as there is no node in the Stack currently
    return S;// returning the pointer to the structure storing the details of the Stack
}
void Push(int x,Stack* S)// inserting elements in stack
{
    if(IsEmpty(S))// inserting value in empty stack
    {
        S->top=(Stack_node*)malloc(sizeof(Stack_node));// allocating memory for 1st node and making top point to it
        S->top->v=x;// storing the integer value in stack
        S->size=1;// making size 1 as stack now has a value
        S->top->prev=NULL;// initializing previous pointer as NULL as there is no node before current node
        S->top->next=NULL;// initializing next pointer as NULL as there is no node after current node
    }
    else // inserting value to non empty Stack
    {
        // adding a node to the front of the Stack
        S->top->prev=(Stack_node*)malloc(sizeof(Stack_node));// allocating memory for the new node
        S->top->prev->v=x;// inserting value in the node(Stack)
        S->top->prev->next=S->top;// setting next pointer to point to the old top
        S->top=S->top->prev;// setting top to point to the new top of the Stack
        S->top->prev=NULL;// initializing previous pointer as NULL as there is no node before current node
        S->size=(S->size)+1;// increasing size variable of stack by 1 as we have added a new node
    }
}
int Pop(Stack* S)// deleting element at top of the stack
{
    int x=S->top->v;// storing value at the top of stack(being deleted) to be returned
    S->size=(S->size)-1;// decreasing size of stack by 1
    Stack_node* curr=S->top;// curr pointer pointing to top node of stack created
    if(curr->next!=NULL)// checking if top is not the only element in the array
    {
        S->top=curr->next;// new top is the next node to the current top
        S->top->prev=NULL;// initializing previous pointer as NULL as there is no node before current node
    }
    else// if top was only element in the stack
    {
        S->top=NULL;// now stack is empty
    }
    free(curr);// making the memory allocated by malloc for the node being deleted free
    return x;// returning the deleted value
}
/*
    we make two arrays outPriority and inPriority to store the priority
    of $,+,-,*,^,/,(
    we assign every operator a number
    $=0
    +=1
    -=2
    /=3
    *=4
    ^=5
    (=6
    now we store the priorities of corresponding operator in its numbered index
    in both arrays
    these number codes will also be used to store the operators in the O stack
*/
int powFn(int x,int n)// function to calculate the power
{
    if(n==0)
    return 1;// any number(except 0) to the power 0 is 1
    if(n==1)
    return x;// any number to the power 1 is the number itself
    int a;
    a=powFn(x,n/2);// storing x to the power int(n/2) in variable a
    if(n%2==0)
        return a*a;// if n is even x to the power n=(x to the power n/2)*(x to the power n/2)
    else
        return a*a*x;// if n is odd the n is not divisible by 2 and n/2 will get round down so an extra x has to be multiplied in this case
}
int Execute(int o,int n1,int n2)// this function returns the value of operation (n1 o n2) n1,n2 are operands and o operator
{
    switch(o)// now we have stored operator as an integer code so we are using this switch to know operation from code and returning the value
    {
        case 1:
        return(n1+n2);
        case 2:
        return(n1-n2);
        case 3:
        return(n1/n2);
        case 4:
        return(n1*n2);
        default:
        return(powFn(n1,n2));// using the function made above to calculate power
    }
}
int main()
{
    int n;
    scanf("%d\n",&n);
    Stack *N=CreateEmptyStack();// creating a stack(pointer) to store operands
    Stack *O=CreateEmptyStack();// creating a stack(pointer) to store operators
    int outPriority[]={0,1,2,4,3,6,7};// initialising array for priority of operators outside the stack
    int inPriority[]= {0,2,1,3,4,5,0};// initialising array for priority of operators inside the stack
    Push(0,O);// making the base of the operator stack
    int num=0;// variable to store a operand while scanning
    char c;// variable to store the character scanned
    int flag=0;// this variable is used to check that some false operands don't enter the operand stack(in cases having operator adjacent to parenthesis)
    for(int i=0;i<n;i++)
    {
        scanf("%c",&c);// scanning a character
        if(c>='0'&&c<='9')// checking if character is a digit
        {// making number from digits
            num=(num*10)+(c-'0');// converting character digit to integer and storing it in num at ones place
            flag=1;// flag=1 means number is read which is not yet pushed in the stack
            if(i==n-1)// if the number is the last thing in the expression we have to push it now as we will not encounter any operator afterwards
            {
                Push(num,N);
                flag=0;// flag=0 means pervious all read number is pushed in stack and no new number is read till now
            }
        }
        else if(c==')')
        {
            // encountering any thing except digit means we have completely scanned our number so we push it in operand stack N
            if(flag==1)// flag=1 ensures we have read a number
            {
                Push(num,N);
                flag=0;
                num=0;// making num as 0 again making it ready to store next number
            }
            while(Top(O)!=6)// loop will execute till we find the ( corresponding to the current )
            {
                // getting the operator
                int o=Pop(O);
                // getting the operands
                int n1=Pop(N);
                int n2=Pop(N);
                int res=Execute(o,n2,n1);// calculating value of n2 o n1
                Push(res,N);// storing the result in the operand stack as it will act as operand for some other operator
            }
            Pop(O);// deleting ( corresponding to current ) from operand stack
        }
        else
        {
            // encountering any thing except digit means we have completely scanned our number so we push it in operand stack N
            if(flag==1)// flag=1 ensures we have read a number
            {
                Push(num,N);
                flag=0;
                num=0;// making num as 0 again so it can storing next operand
            }
            int x;
            switch(c)// converting operator to the integer code so we can store it in the operator stack
            {
                case '+':
                x=1;
                break;
                case '-':
                x=2;
                break;
                case '/':
                x=3;
                break;
                case '*':
                x=4;
                break;
                case '^':
                x=5;
                break;
                default:
                x=6;
                break;
            }
            while(inPriority[Top(O)]>=outPriority[x])// executing operator whenever possible
            {
                int o=Pop(O);
                int n1=Pop(N);
                int n2=Pop(N);
                int res=Execute(o,n2,n1);
                Push(res,N);
            }
            Push(x,O);// after executing all possible operators now finally storing currently scanned operator in opertor stack
        }
    }
    if(Top(O)==0)// if we have reached the bottom of operator stack(means we exectued all operators) we print the answer stored in operand stack
    {
        printf("%d",Top(N));
    }
    else // if we have not reached the bottom of operator stack(means we have to execute some operators) we execute all operators and reach the bottom
    {
        while(inPriority[Top(O)]>outPriority[0])
            {
                int o=Pop(O);
                int n1=Pop(N);
                int n2=Pop(N);
                int res=Execute(o,n2,n1);
                Push(res,N);
            }
        printf("%d",Top(N));// now we reach the bottom of operator stack thus we can print the answer
    }
    return 0;
}