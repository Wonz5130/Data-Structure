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


// 顺序表初始化
Status Init(SeqList *L, int mSize) {
	L->maxLength = mSize;
	L->n = 0;
	L->element = (ElemType*)malloc(sizeof(ElemType)*mSize);
    if(!L->element)
    return OK;
}

// 顺序表的查找
Status Find(SeqList L,int i,ElemType *x){
    if(i<0||i>L.n-1){
        return ERROR;
    }
    *x=L.element[i];
    return OK;
}

// 初始化插入
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

// 顺序表的删除
Status Delete(SeqList *L, int i){
    int j;
    if(i<0||i>L->n-1){
        return ERROR;
    }
    if(!L->n){
        return ERROR;
    }
    for(j=i+1;j<L->n;j++){
        L->element[j-1]=L->element[j];
    }
    L->n--;
    return OK;
}

// 顺序表输出
int Output(SeqList L) {
	int i;
	if (!L.n)
		return ERROR;
	for (i = 0; i <= L.n - 1; i++)
		printf("%d ", L.element[i]);  //从前往后逐个输出元素
	return OK;
}

// 顺序表的撤销
void Destroy(SeqList *L){
    (*L).n=0;
    (*L).maxLength=0;
    free((*L).element);
}

void main()
{
	int i;
	SeqList list;
	Init(&list, 10);  // 对线性表初始化
	for (i = 0; i < 9; i++) {
		Insert(&list, i - 1, i);
	}
	Output(list);
    printf("\n");
    Delete(&list,0);
	Output(list);
    Destroy(&list);
}