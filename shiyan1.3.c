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
    Destroy(&list);
}