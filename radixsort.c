
//for printf and scanf
#include <stdio.h>

//for dynamic memory management
#include <stdlib.h>

struct Node{
    void *data;
    struct Node *next;
};

struct List{
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct List list;
typedef struct Node node;

//to create a new node
node *createNode(int d){
    node *n = (node *)malloc(sizeof(node));
    int *e = (int *)malloc(sizeof(int));
    n->data = (void *)e;
    n->next = NULL;
    return n;
}

//To create a new List which hold the nodes
list *createList(){
    list *l = (list *)malloc(sizeof(list));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

// checks whether given list is empty or not
int isListEmpty(list *l){
    return l->size == 0;
}

// Insert the given data at the end of the list
void insertAtEnd(list *l, int d){
    node *n = createNode(d);
    if(isListEmpty(l)){
        l->head = n;
        l->tail = n;
    }
    else{
        l->tail->next = n;
        l->tail = n;
    }
    l->size++;
}

// Delete the data from the starting and return the removed data value
int removeAtStart(list *l){
    if(isListEmpty(l))
        return -1;
    int *num = (int *)l->head->data;
    if(l->size == 1){
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
    }
    else{
        node *n = l->head->next;
        free(l->head);
        l->head = n;
    }
    l->size--;
    return *num;
}

//get maximum value of the given array
int getMax(int arr[], int len){
    int max = arr[0];
    for(int i = 1; i < len; i++){
        if(arr[i] > max)
            max = arr[i];
    }
    return max;
}

//checks whether all digits are same or not at particular position like 1's, 10's, 100's position
int isAllDigitsSame(int arr[], int len, int place){
    int digit = (arr[0] / place) % 10;
    for(int i = 1; i < len; i++){
        if((arr[i] / place) % 10 != digit)
            return 0;
    }
    return 1;
}

//prints the array
void printArray(int *arr, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//sorts the data based on the given place like 1's, 10's, 100's so on..
void sort(int arr[], int n, list *ListArr[], int place){
    int ind;
    for(int i = 0; i < n; i++){
        ind = (arr[i] / place) % 10;
        if(ListArr[ind] == NULL)
            ListArr[ind] = createList();
        insertAtEnd(ListArr[ind], arr[i]);
    }
    ind = 0;
    for(int i = 0; i < 10; i++){
        while(ListArr[i] != NULL && !isListEmpty(ListArr[i])){
            arr[ind] = removeAtStart(ListArr[i]);
            ind++;
        }
    }
}

//performs the sort function until total data become sorted
void radixsort(int arr[], int n){
    int max = getMax(arr, n);
    list *listArr[10];
    for(int i = 0; i < 10; i++)
        listArr[i] = NULL;
    for(int i = 1; max / i > 0; i *= 10){
        if(!isAllDigitsSame(arr, n, i))
            sort(arr, n, listArr, i);
    }
    //frees the memory which is allocated dynamically
    for(int i = 0; i < 10; i++){
        if(listArr[i] != NULL)
            free(listArr[i]);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    if(n <= 0){
        printf("INVALID INPUT");
        return 0;
    }
    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        if(arr[i] < 0){
            printf("INVALID INPUT");
            return 0;
        }
    }
    radixsort(arr, n);
    printArray(arr, n);
    return 0;
}
