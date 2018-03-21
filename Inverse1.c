// #include "stdafx.h"
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
//void Inverse(SingleList *L, int n);
void Inverse(SingleList *L);
Status Insert(SingleList *L, int i, ElemType x);
// Status Delete(SeqList *L,int i);
// void Destory(SeqList *L);


// �������ʼ��
Status Init(SingleList *L) {
	L->first = NULL;
	L->n = 0;
	return OK;
}

/*
void Inverse(SingleList *L, int n) {
	Node *p,*q,*t;
	int i,j;
	p=L->first;
	t=L->first;
	for(j=0;j<n-3;j++){
		p=p->link;
	}
	for(j=0;j<n-1;j++){
		t=t->link;
	}
	q=malloc(sizeof(Node));
	q->element = t->element;
	for(i=n-3;i>=0;i--){
		q->link=p->link;
		q--;
		p->link=t;
		p--;
	}
}
*/

/*
void Inverse(SingleList *L, int n){
	Node *p,*q,*t,*r;
	int i,j;
	r=L->first;  //始终指向第一个结点
	p=L->first;
	for(i=1;i<n;i++){
		t=L->first;
		for(j=0;j<i;j++){
			t=t->link;
		}
		q=t;
		L->first=q; //first结点
		p->link=q->link;
		q->link=r;
	}
}
*/

/*
void Inverse(SingleList *L, int n){
	Node *p,*q,*q1;
	p=L->first;
	q=p->link;
	p->link=NULL;
	if(n==1) return 0;
	if(n>=2){
		while(q->link!=NULL){
			q1=q->link;
			q->link=p;
			p=q;
			//p->link=NULL; 
			q=q1;
		}
		q->link=p;
		L->first=q;
	}
}
*/

void Inverse(SingleList *L){
	Node *p=L->first,*q;
	L->first = NULL;
	while(p){
		q=p->link;
		p->link=L->first;
		L->first=p;
		p=q;
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


// ���������
Status Output(SingleList L) {
	Node *p;
	if (!L.n)
		return ERROR;
	p = L.first;
	while (p) {
		printf("%d ",p->element);  //��ǰ����������Ԫ��
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
	Init(&list);  // �Ե������ʼ��
	for (i = 0; i < nn; i++) {
		scanf("%d", &x);
		Insert(&list, i - 1, x);
	}
	Output(list);
	// Inverse(&list, nn);
	Inverse(&list);
	printf("\n");
	Output(list);
	printf("\n");
}