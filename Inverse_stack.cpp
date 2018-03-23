#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define N 100
typedef int BOOL;
typedef int ElemType;

typedef struct{
    int top;
    int maxSize;
    ElemType *element;
}Stack;

/*
void Create1(Stack *S, int mSize);
BOOL IsEmpty1(Stack *S);
BOOL IsFULL1(Stack *S);
BOOL Top(Stack *S,ElemType *x);
BOOL Push(Stack *S,ElemType x);
BOOL Pop(Stack *S);
void Create2(Queue *Q,int mSize);
BOOL IsEmpty2(Queue *Q);
BOOL IsFULL2(Queue *Q);
BOOL Front2(Queue *Q,ElemType *x);
BOOL DeQueue(Queue *Q);
void Output(Stack *S,int n);
int Inverse(Stack *S,Queue *Q,int n);
*/

void Create1(Stack *S, int mSize){
    S->maxSize=mSize-1;
    S->element=(ElemType*)malloc(sizeof(ElemType)*mSize);
    S->top=-1;
}

BOOL IsEmpty1(Stack *S){
    return S->top==-1;
}

BOOL IsFULL1(Stack *S){
    return S->top==S->maxSize;
}

BOOL Top(Stack *S,ElemType *x){
    if(IsEmpty1(S))
        return FALSE;
    *x=S->element[S->top];
    return TRUE;
}

BOOL Push(Stack *S,ElemType x){
    if(IsFULL1(S))
        return FALSE;
    S->top++;
    S->element[S->top]=x;
    return TRUE;
}

BOOL Pop(Stack *S){
    if(IsEmpty1(S))
        return FALSE;
    S->top--;
    return TRUE;
}

typedef struct{
    int front;
    int rear;
    int maxSize;
    ElemType *element;
}Queue;

void Create2(Queue *Q,int mSize){
    Q->maxSize=mSize;
    Q->element=(ElemType*)malloc(sizeof(ElemType)*mSize);
    Q->front=Q->rear=0;
}

BOOL IsEmpty2(Queue *Q){
    return Q->front==Q->rear;
}

BOOL IsFULL2(Queue *Q){
    return (Q->rear+1)%Q->maxSize==Q->front;
}

BOOL Front2(Queue *Q,ElemType *x){
    if(IsEmpty2(Q))
        return FALSE;
    *x=Q->element[(Q->front+1)%Q->maxSize];
    return TRUE;
}

BOOL EnQueue(Queue *Q,ElemType x){
    if(IsFULL2(Q))
        return FALSE;
    Q->rear=(Q->rear+1)%Q->maxSize;
    Q->element[Q->rear]=x;
    return TRUE;
}

BOOL DeQueue(Queue *Q){
    if(IsEmpty2(Q)){
        return FALSE; 
    }
    Q->front=(Q->front+1)%Q->maxSize;
    return TRUE;
}

void Output(Stack *S,int n){
    int i;
    i=S->top;
    if(S->top==-1){
        printf("NULL");
    }
    while(S->top!=-1){
        printf("%d",S[i--]);
    }
    printf("\n");
}


int Inverse(Stack *S,Queue *Q,int n){
    int i;
    ElemType a[N];
    for(i=0;i<n;i++){
        if(IsEmpty1(S)){
            return FALSE;
        }
        a[i]=S->element[S->top--];
        EnQueue(Q,a[i]);
    }
    for(i=0;i<n;i++){
        if(IsEmpty2(Q)){
            return FALSE;
        }
        a[i]=Q->element[Q->front++];
        Push(S,a[i]);
    }
}

int main(){
    int n,i,x;
    Stack S;
    Queue Q;
    scanf("%d",&n);
    printf("\n");
    Create1(&S,n);
    Create2(&Q,n);
    for(i=0;i<n;i++){
        scanf("%d",&x);
        Push(&S,x);
    }
    Output(&S,n);
    Inverse(&S,&Q,n);
    Output(&S,n);
}
