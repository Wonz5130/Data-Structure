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
Status Min(SingleList *L, int mSize);
Status Insert(SingleList *L, int i, ElemType x);
// Status Delete(SeqList *L,int i);
// void Destory(SeqList *L);


// 单链表的初始化
Status Init(SingleList *L) {
	L->first = NULL;
	L->n = 0;
	return OK;
}



Status Min(SingleList *L, int n){
	Node *r,*q,*p=L->first;
	int i,x=0;
    q=p;
    r=L->first;
    for(i=1;i<n;i++){
        q=q->link;
        if(q->element<p->element){  // 查找min返回下标i到x中
            p=q;
			x=i;
        }
    }
	if(x==0){
		return OK;  // 本来第一位就是min
	}
	else if(x==1){  // 第二位是min
		L->first=p;
		r->link=p->link;
		L->first->link=r;
	}
	else{
		for(i=0;i<x-1;i++){
			r=r->link;  // 找到min的前一个位置
		}
		r->link=p->link;
    	p->link=L->first;
    	L->first=p;
		return OK;
	}
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
	int i, x, nn;
	SingleList list;
	scanf("%d", &nn);
	printf("\n");
	Init(&list);
	for (i = 0; i < nn; i++) {
		scanf("%d", &x);
		Insert(&list, i - 1, x);
	}
	Output(list);
	Min(&list,nn);
	printf("\n");
	Output(list);
	printf("\n");
}