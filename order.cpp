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

Status Init(HeaderList *h);
Status Output(HeaderList *h);
Status order(HeaderList *h, int mSize);
Status Insert(HeaderList *h, int i, ElemType x);
// Status Delete(SeqList *L,int i);
// void Destory(SeqList *L);


// 单链表的初始化
Status Init(HeaderList *h) {
    h->head=(Node*)malloc(sizeof(Node));
    if(!h->head){
        return ERROR;
    }
	h->head->link = NULL;
	h->n = 0;
	return OK;
}



Status order(HeaderList *h, int n){
	int flag=-1;
	Node *p = h->head->link,*q=p->link;
	while(p->link!=NULL){
		if(p->element>=q->element){
			flag=-1;
			break;
		}
		else flag=1;
		p=q;
		q=q->link;
	}
	if(flag==-1){
		printf("No");
	}
	else printf("Yes");
	return OK;
}



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


// 单链表的输出
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



int main()
{
	int i, x, nn;
	HeaderList list;
	scanf("%d", &nn);
	printf("\n");
	Init(&list);
	for (i = 0; i < nn; i++) {
		scanf("%d", &x);
		Insert(&list, i - 1, x);
	}
	Output(&list);
	printf("\n");
	order(&list,nn);
	return 0;
}
