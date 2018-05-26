#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef int Status;
#define ERROR 0
#define OK 1

typedef struct Node {
	ElemType element;      //结点的数据域
	struct Node * link;    //结点的指针域
}Node;

typedef struct {
	struct Node* head;     //表头结点
	int n;
}HeaderList;


//带表头结点单链表的初始化
Status Init(HeaderList *h) {
    h->head=(Node*)malloc(sizeof(Node));   //生成表头结点
    if(!h->head){
        return ERROR;
    }
	h->head->link = NULL;                  //设置单链表为空表
	h->n = 0;
	return OK;
}


//带表头结点单链表的查找
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


//带表头结点单链表的插入
Status Insert(HeaderList *h, int i, ElemType x) {
	Node *p, *q;
	int j;
	if (i<-1 || i>h->n - 1)
		return ERROR;
	p = h->head;                          //从头结点开始找ai元素所在的结点p
	for (j = 0; j <= i; j++) {
		p = p->link;
	}
	q = (Node*)malloc(sizeof(Node));      //生成新结点q
	q->element = x;
	q->link = p->link;                    //新结点q插在p之后
	p->link = q;
	h->n++;
	return OK;
}


//带表头结点单链表的删除
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
    q->link=p->link;                //从单链表中删除p所指结点
    free(p);                        //释放p所指结点的存储空间
    h->n--;
    return OK;
}


//带表头结点单链表的输出
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


//带表头结点单链表的撤销
void Destroy(HeaderList *h){
    Node *p,*q;
    while(h->head->link){
        q=h->head->link;
        p=h->head->link->link;
        free(h->head->link);
        h->head=q;
    }
}


//简单选择排序：每次选择min的排到前面
Status Order(HeaderList *h){
    Node *s1,*s2,*s3,*s4,*p,*q;
    for (p=h->head;p!=NULL && p->link!=NULL;p=p->link) {     // p从指向头结点开始
        for (q=p->link;q!=NULL && q->link!=NULL;q=q->link) {
            if (p->link->element > q->link->element) {       // 如果当前结点元素值大于后面元素值，则交换
                s1=p->link;                                  // s1指向p后面的结点
                s2=p->link->link;                            // s2指向p后面的后面的结点
                s3=q->link;                                  // s2指向q后面的结点
                s4=q->link->link;                            // s4指向q后面的后面结点
 
                if (s2!=s3) {                                //如果s2不等于s3，说明交换两个结点的中间有一些其他结点数据
                    p->link=s3;
                    s3->link=s2;
                    q->link=s1;
                    s1->link=s4;
                }
                else {                                       // s2和s3指向同一个结点
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
	int i,j, x;
	HeaderList list;
	Init(&list);
	for (i = 8,j = 0; i >= 0; i--,j ++) {
		Insert(&list, j - 1, i);    //插入8~0
	}
    printf("the linklist is:");
	Output(&list);
    Order(&list);                   //非递减排序
    printf("\nthe linklist is:");
    Output(&list);
    Destroy(&list);
}
