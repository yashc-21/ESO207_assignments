#include<stdio.h>
#include<stdlib.h>

/*

 Our data structure consists of 2 spines one for rows and other for columns.
The row spine consists of nodes pointing to the next node in spine(next non empty row head) and to the first node containing 1st element of corresponding row.
Similarly column spine is made up of nodes pointing to next node in spine(next non empty column head) and to the node containing first element of the corresponding column.
Each node storing values of matrix(all nodes except nodes forming spine) point to next element in row and to the next element in the column.
Finally we have a node for matrix having two pointers one pointing towards 1st node of row spine and other to 1st node of column spine.

 */

int mat_id;
unsigned int n; // Took n and mat_id as global variable as they are needed in multiple functions

typedef struct node{
    // This data structure stores the value of the node (v), row (i), column(j) and pointers to right and bottom elements
    // Row Heads will have column number = 0, and Column heads will have Row number = 0
    int v;
    unsigned int i, j;
    struct node * c_next;
    struct node * r_next;
} NODE;

struct mat{
    NODE * col_head;
    NODE * row_head;
};

void matMultiply(struct mat m1, struct mat m2){
    int flag = 1; // Depicts if First non zero element is not found or found
    NODE * currRow = m1.row_head; // currRow signifies the current row of First matrix which is being multiplied
    int ele; // Stores values of elements of resultant matrix

    while(currRow != NULL){
        NODE * currCol = m2.col_head; // Current Column of 2nd Matrix which is being multiplied
        while(currCol != NULL){
            ele = 0;
            NODE * currEleC = currCol->c_next; // These two variable are the elements of 1st and 2nd matrix which are
            NODE * currEleR = currRow->r_next; // being iterated and multiplied
            while(currEleR != NULL && currEleC != NULL){
                if(currEleR->j == currEleC->i){ // we have to add all such elements to "ele"
                    ele += currEleR->v * currEleC->v;
                    currEleR = currEleR->r_next; // Moving both the elements forward
                    currEleC = currEleC->c_next;
                }
                else if(currEleR->j < currEleC-> i){ // if Column number of first matrix's element is less than row number of 2nd's
                    currEleR = currEleR->r_next;
                }else{ // if Row number of Less
                    currEleC = currEleC->c_next;
                }
            }
            if(ele != 0){ // if the sum of non-zero then we print it
                flag = 0; // denotes that non-zero number of elements are printed
                printf("%u %u %d\n", currRow->i, currCol->j, ele);
            }
            currCol = currCol->r_next; // For iterating to next column and keeping the row same
        }
        currRow = currRow->c_next; // Moving to next row
    }
    if(flag){
        printf("NULL MATRIX!"); // if No element was printed
    }
}

struct mat takeInput(int k){

    NODE * colArray[n];  // This array stores the column head nodes
    NODE * colHeads[n];  // This stores the pointers to bottom-most elements in each column

    for(int i = 0; i < n; i++){
        colArray[i] = NULL; // Initializing them to NULL so that we can later remove the unused ones
        colHeads[i] = NULL;
    }
    struct mat mat1; //Output

    mat1.row_head = (NODE *)calloc(1, sizeof(NODE)); // Initializing Row Head

    NODE * tempRowHead = mat1.row_head; // This variable will store current Row's Head
    NODE * currNode;
    NODE * prevNode = NULL; // This variable will store Node just left to Current Node so that we can link them horizontally
    unsigned int prevRow = 0; // Used to detect Row-Change

    while(mat_id==k) // k is 1 or 2 depending on the matrix in which input is to be taken
    {
        currNode = (NODE *)calloc(1, sizeof(NODE));
        scanf("%u %u %d", &currNode->i, &currNode->j, &currNode->v);

        if(!prevRow){ // Only applicable for first non-zero Row
            tempRowHead->i = currNode->i; // Storing the Row Number in the Row Heads
            tempRowHead->j = 0;
            prevRow = currNode->i;
        }
        if(currNode->i != prevRow){ // For Row Change
            tempRowHead->c_next = (NODE *)calloc(1, sizeof(NODE)); // Creating next Row Head
            tempRowHead = tempRowHead->c_next;
            tempRowHead->i = currNode->i; // Storing Row Number
            prevRow = currNode->i;
            prevNode = NULL; // New Row will have No Previous Node
        }

        if(prevNode == NULL){ // Connecting Nodes Horizontally
            tempRowHead->r_next = currNode;
        }else{
            prevNode->r_next = currNode;
        }
        prevNode = currNode;

        if(colArray[currNode->j - 1] == NULL){ // Depicts that this Node is first in the Column
            colHeads[currNode->j - 1] = (NODE *)calloc(1, sizeof(NODE)); // Initializing Column head for a non zero column
            colArray[currNode->j - 1] = colHeads[currNode->j - 1]; // This is the new bottom-most element since Column is empty
            colHeads[currNode->j - 1]->j = currNode->j; // Storing Column Number
        }

        colArray[currNode->j - 1]->c_next = currNode; // Connecting Nodes Vertically
        colArray[currNode->j - 1] = currNode;

        scanf("%d", &mat_id);
    }

    tempRowHead->c_next = NULL; // Last Row head will point down to NULL

    int flag = 1; // Depicts if the First Element is found or not since it will be connected to the Main Matrix's Column Head

    for(int i = 0; i < n; i++){
        if(colHeads[i] != NULL){
            if(flag){
                mat1.col_head = colHeads[i]; // Storing Column head
                prevNode = mat1.col_head; // This variable has same works as before, storing just-left element
                flag = 0; // First Element Found
            }else{
                prevNode->r_next = colHeads[i]; // Connecting column heads horizontally and not including zero columns
                prevNode = colHeads[i];
            }
        }
    }

    if(prevNode != NULL) prevNode->r_next = NULL; // Right-most column head will point right to NULL

    return mat1;
}

void printMat(struct mat mat1){
    NODE * currRow = mat1.row_head; // Row Head
    while(currRow != NULL){
        NODE * currEle = currRow->r_next; // iterates through Rows
        while(currEle != NULL){
            printf("%u %u %d\n", currEle->i, currEle->j, currEle->v);
            currEle = currEle->r_next; // Moving to next element in row
        }
        currRow = currRow->c_next; // Moving to next Row
    }
}

int main()
{
    scanf("%u %d",&n, &mat_id);

    if(mat_id == 1) {
        struct mat mat1 = takeInput(1);  //Taking Inputs in both data Structures, this if-else structure allows us to
        //print "NULL MATRIX!" without actually multiplying, if one matrix has no elements
        if (mat_id == 2) {
            struct mat mat2 = takeInput(2);

            // We can use these printMat statements to print the matrices
            // printMat(mat1);
            // printMat(mat2);

            matMultiply(mat1, mat2); // for Multiplying Matrices and printing output
            return 0;
        }
    }
    printf("NULL MATRIX!");
}