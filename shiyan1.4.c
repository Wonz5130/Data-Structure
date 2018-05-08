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
	struct Node* head;
	int n;
}HeaderList;



// 带表头单链表的初始化
Status Init(HeaderList *h) {
    h->head=(Node*)malloc(sizeof(Node));
    if(!h->head){
        return ERROR;
    }
	h->head->link = NULL;
	h->n = 0;
	return OK;
}


// 带表头单链表的查找
Status Find(HeaderList *h,int i,ElemType *x){
    Node *p;
    int j;
    if(i<0||i>h->n-1){
        return ERROR;
    }
    p=h->head->link;
    for(j=0;j<i;j++){
        p=p->link;
    }
    *x=p->element;
    return OK;
}


// 带表头单链表的插入
Status Insert(HeaderList *h, int i, ElemType x) {
	Node *p, *q;
	int j;
	if (i<-1 || i>h->n - 1)
		return ERROR;
	p = h->head;
	for (j = 0; j <= i; j++) {
		p = p->link;
	}
	q = (Node*)malloc(sizeof(Node));
	q->element = x;
	q->link = p->link;
	p->link = q;
	h->n++;
	return OK;
}


// 带表头单链表的删除
Status Delete(HeaderList *h,int i){
    int j;
    Node *p,*q;
    if(!h->n){
        return ERROR;
        if(i<0||i>h->n-1){
            return ERROR;
        }
    }
    q=h->head;
    for(j=0;j<i;j++){
        q=q->link;
    }
    p=q->link;
    q->link=p->link;
    free(p);
    h->n--;
    return OK;
}


// 带表头单链表的输出
Status Output(HeaderList *h) {
	Node *p;
	if (!h->n)
		return ERROR;
	p = h->head->link;
	while (p) {
		printf("%d ",p->element);
		p = p->link;
	}
	return OK;
}


// 带表头单链表的撤销
void Destroy(HeaderList *h){
    Node *p,*q;
    while(h->head->link){
        q=h->head->link;
        p=h->head->link->link;
        free(h->head->link);
        h->head=q;
    }
}


// 带表头单链表的逆置
void Inverse(HeaderList *h){
	Node *p=h->head->link,*q;
	h->head->link = NULL;
	while(p){
		q=p->link;
		p->link=h->head->link;  //p->link=NULL
		h->head->link=p;  //为下一次逆置做准备
		p=q;
	}
}


// 每次选择min的排到前面
Status Order(HeaderList *h){
    Node *s1,*s2,*s3,*s4,*p,*q;
    for (p=h->head;p!=NULL && p->link!=NULL;p=p->link) {
        for (q=p->link;q!=NULL && q->link!=NULL;q=q->link) {
            if (p->link->element > q->link->element) {
                s1=p->link;
                s2=p->link->link;
                s3=q->link;
                s4=q->link->link;
 
                if (s2!=s3) {
                    p->link=s3;
                    s3->link=s2;
                    q->link=s1;
                    s1->link=s4;
                }
                else {
                    p->link=s3;
                    s3->link=s1;
                    q=s3;
                    s1->link=s4;
                }
            }
        }
    }
    return OK;
}


/*
Status Order(HeaderList *h, int n){
    Node *q,*r,*m,*p=h->head;
    int i,j,x=0;
    m=h->head;
    for(i=1;i<=n;i++){
        q=p->link;
        // r=p->link;
        for(j=i;j<n;j++){
            p=q;
            q=q->link;
            if(q->element<p->element){
                p=q;
                x=i;
            }
        }
        if(x==0){
            return OK;
        }
        else if(x==1){
            h->head->link=p;
            r->link=p->link;
            p->link=r;
        }
        else{
            r=h->head;
            for(i=0;i<x;i++){
                r=r->link;
            }
            r->link=p->link;
            p->link=m->link;
            m->link=p;
            m=m->link;
            return OK;
        }
    }
}
*/


void main()
{
	int i, x;
	HeaderList list;
	Init(&list);
	for (i = 0; i < 9; i++) {
		Insert(&list, i - 1, i);
	}
    printf("\nthe linklist is:");
	Output(&list);
    Inverse(&list);
    printf("\nthe linklist is:");
    Output(&list);
    Order(&list);
    printf("\nthe linklist is:");
    Output(&list);
    Destroy(&list);
}