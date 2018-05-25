#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef int ElemType;
typedef int Status;

typedef struct {
	int n;               // 顺序表的长度
	int maxLength;       // 顺序表的最大长度
	ElemType *element;   // 存放动态分配一维数组首地址
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
	if (i<-1 || i>L->n - 1)                  // 判断下标i是否越界
		return ERROR;
	if (L->n == L->maxLength)                // 判断顺序表存储空间是否已满
		return ERROR;
	for (j = L->n - 1; j > i; j--) {
		L->element[j + 1] = L->element[j];   // 从后往前逐个后移元素
	}
	L->element[i + 1] = x;                   // 将新元素放入下标为i+1的位置
	L -> n = L->n + 1;                       // 长度+1
	return OK;
}


// 顺序表的删除
Status Delete(SeqList *L, int i){
    int j;
    if(i<0||i>L->n-1){                   // 下标i是否越界
        return ERROR;
    }
    if(!L->n){                           // 顺序表是否为空
        return ERROR;
    }
    for(j=i+1;j<L->n;j++){
        L->element[j-1]=L->element[j];   // 从前往后逐个前移元素
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
	Init(&list, 10);               // 对线性表初始化
	for (i = 0; i < 9; i++) {
		Insert(&list, i - 1, i);   // 将0-8插入到顺序表中
	}
	Output(list);
    printf("\n");
    Delete(&list,0);               // 删除0
	Output(list);
    Destroy(&list);
}
