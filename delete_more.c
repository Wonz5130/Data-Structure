#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef int Status;
#define ERROR 0
#define OK 1

typedef struct Node {
	ElemType element;
	struct Node * link;
}Node;

typedef struct {
	struct Node* first;
	int n;
}SingleList;

Status Init(SingleList *L);
Status Output(SingleList L);
Status del(SingleList *L, int mSize,int y);
Status Insert(SingleList *L, int i, ElemType x);
// Status Delete(SeqList *L,int i);
// void Destory(SeqList *L);


// 单链表的初始化
Status Init(SingleList *L) {
	L->first = NULL;
	L->n = 0;
	return OK;
}



Status del(SingleList *L, int n,int y){
	Node *q,*p;
    int i=0;
    if(!L->n){
        return ERROR;
    }
    /*
    if(L->first->element==y){
        L->first=L->first->link;
        i=1;
    }
    */
    p=L->first;
    q=p->link;
    for(;i<n;i++){
        if(p->element==y){
            L->first=q;
            free(p);
            p=q;
            q=p->link;
        }
        else if(q->element==y){
            p->link=q->link;
            free(q);
            p=p->link;
            q=p->link;
        }
    }
    return OK;
}



Status Insert(SingleList *L, int i, ElemType x) {
	Node *p, *q;
	int j;
	if (i<-1 || i>L->n - 1)
		return ERROR;
	p = L->first;
	for (j = 0; j < i; j++) {
		p = p->link;
	}
	q = malloc(sizeof(Node));
	q->element = x;
	if (i > -1) {
		q->link = p->link;
		p->link = q;
	}
	else {
		q->link = L->first;
		L->first = q;
	}
	L->n++;
	return OK;
}


// 单链表的输出
Status Output(SingleList L) {
	Node *p;
	if (!L.n)
		return ERROR;
	p = L.first;
	while (p) {
		printf("%d ",p->element);
		p = p->link;
	}
	return OK;
}



void main()
{
	int i, x, nn,y;
	SingleList list;
	scanf("%d", &nn);
	printf("\n");
	Init(&list);
	for (i = 0; i < nn; i++) {
		scanf("%d", &x);
		Insert(&list, i - 1, x);
	}
	Output(list);
    scanf("%d",&y);
	del(&list,nn,y);
	printf("\n");
	Output(list);
	printf("\n");
}