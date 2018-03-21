#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef int ElemType;
typedef int Status;

typedef struct {
	int n;
	int maxLength;
	ElemType *element;
}SeqList;


Status Init(SeqList *L, int mSize);
Status Output(SeqList L);
void Inverse(SeqList *L, int mSize);
Status Insert(SeqList *L, int i, ElemType x);
// Status Delete(SeqList *L,int i);
// void Destory(SeqList *L);


// 顺序表初始化
Status Init(SeqList *L, int mSize) {
	L->maxLength = mSize;
	L->n = 0;
	L->element = (ElemType*)malloc(sizeof(ElemType)*mSize);
	if(!L->element)
		return ERROR;
	return OK;
}

void Inverse(SeqList *L, int mSize) {
	int i, temp;
	for (i = 0; i < mSize / 2; i++) {
		temp = L->element[i];
		L->element[i] = L->element[mSize - 1 - i];
		L->element[mSize - 1 - i] = temp;
	}
}

Status Insert(SeqList *L, int i, ElemType x) {
	int j;
	if (i<-1 || i>L->n - 1)
		return ERROR;
	if (L->n == L->maxLength)
		return ERROR;
	for (j = L->n - 1; j > i; j--) {
		L->element[j + 1] = L->element[j];
	}
	L->element[i + 1] = x;
	L -> n = L->n + 1;
	return OK;
}


// 顺序表输出
Status Output(SeqList L) {
	int i;
	if (!L.n)
		return ERROR;
	for (i = 0; i <= L.n - 1; i++)
		printf("%d ", L.element[i]);  //从前往后逐个输出元素
	return OK;
}

/*
Status Delete(SeqList *L,int i){
	int j;
	if (i<0 || i>L->n - 1)
		return ERROR;
	if (!L->n)
		return ERROR;
	for (j =i+1; j < L->n; j++) {
		L->element[j - 1] = L->element[j];
	}
	L -> n --;
	return OK;
}
*/

/*
void Destory(SeqList *L){
	(*L).n=0;
	(*L).maxLength=0;
	free((*L).element);
}
*/

int main()
{
	int i,x,nn;
	scanf("%d",&nn);
	printf("\n");
	SeqList list;
	Init(&list, nn);  // 对线性表初始化
	for (i = 0; i < nn; i++) {
		scanf("%d",&x);
		Insert(&list, i - 1, x);
	}
	Output(list);
	Inverse(&list,nn);
	printf("\n");
	Output(list);
	printf("\n");
	// Delete(&list,0);
	// Destory(&list);
}