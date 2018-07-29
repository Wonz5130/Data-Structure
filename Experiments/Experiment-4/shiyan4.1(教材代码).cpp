#include<stdio.h>
#include<windows.h>
#include<algorithm>
using namespace std;
#define MaxSize 100
#define OK 1
#define ERROR 0
typedef int KeyType;
typedef int DataType;

//typedef int Entry;

typedef struct entry{     //数据元素
    KeyType key;          //排序关键字,KeyType应该为可比较类型
    DataType data;        //data包含数据元素中的其他数据项
}Entry;

typedef struct list{      //顺序表
    int n;                //待排序数据元素数量
    Entry D[MaxSize];     //静态数组存储数据元素
}List;

/*
//简单选择排序
void SelectSort(List *list){
    int small;
    for(int i = 0;i < list->n-1;i ++){
        small = i;  //标记每次第一位元素下标
        for(int j = i+1;j < list->n;j ++){
            if(list->D[j].key < list->D[small].key){  //按非递减顺序比较大小
                small = j;
            }
        }
        if(small != i){  //判断起始位置是否为最小值
            swap(list->D[i],list->D[small]);
            i ++;
        }
    }
}
*/


//简单选择排序
void SelectSort(List *list){
    int small,i,j;
    for(i = 0;i < list->n-1;i ++){
        small = i;                                    //标记每次第一位元素下标
        for(j = i+1;j < list->n;j ++){
            if(list->D[j].key < list->D[small].key){  //按非递减顺序比较大小
                small = j;
            }
        }
        if(small != i){                               //判断起始位置是否为最小值
            swap(list->D[j].key,list->D[small].key);  //直接调用algorithm库里的swap函数
        }
    }
}


//直接插入排序
void InsertSort(List *list){
    int i,j;                                 //i标识待插入元素下标
    for(i = 1;i < list->n;i ++){
        Entry insertItem = list -> D[i];     //标记每次第一位元素
        for(j = i-1;j >= 0;j --){
            //不断将有序序列中元素向后移动,为待插入元素空出一个位置
            if(insertItem.key < list->D[j].key){
                list->D[j+1] = list->D[j];
            }
            else break;
        }
        list->D[j+1] = insertItem;          //待插入元素有序存放至有序序列中
    }
}


//冒泡排序
void BubbleSort(List *list){
    int i,j;                    //i标识每趟排序范围最后一个元素下标,每趟排序元素下标范围是0~i
    for(i = list->n-1;i > 0;i --){
        BOOL isSwap = FALSE;    //教材这里错了,应该放到第二层循环前
        for(j = 0;j < i;j ++){
            if(list->D[j].key > list->D[j+1].key){
                swap(list->D[j],list->D[j+1]);
                isSwap = TRUE;
            }
        }
        if(!isSwap) break;     //如果本趟排序没有发生元素交换,排序完成
    }
}


//序列划分方法
int Partition(List *list,int low,int high){
    int i = low,j = high + 1;
    Entry pivot = list->D[low];                 //pivot是分割元素
    do{
        do i++;
        while(list->D[i].key < pivot.key);      //i前进
        do j--;
        while(list->D[j].key > pivot.key);      //j前进
        if(i < j) swap(list->D[i],list->D[j]);
    }while(i < j);
    swap(list->D[low],list->D[j]);
    return j;                                   //此时j是分割元素下标
}


//快速排序
void QuickSort(List *list,int low,int high){   //快速排序的递归函数
    int k;
    if(low < high){                            //当前待排序序列至少包含2个元素
        k = Partition(list,low,high);
        QuickSort(list,low,k-1);
        QuickSort(list,k+1,high);
    }
}


//函数重载
void QuickSort(List *list){                   //快速排序算法的主调用函数
    QuickSort(list,0,list->n-1);
}


/*
//序列两路合并方法
//n1和n2是两个子序列长度,low是第一个子序列第一个元素下标
void Merge(List *list,Entry *temp,int low,int n1,int n2){
    int i = low,j = low + n1; //i,j初始时分别指向两个序列的第一个元素
    while(i <= low+n1-1 && j <= low+n1+n2-1){
        if(list->D[i].key <= list->D[j].key)
            *temp++ = list->D[i++];
        else *temp++ = list->D[j++];
    }
    while(i <= low+n1-1)
        *temp++ = list->D[i++];  //剩余元素直接拷贝至temp
    while(j <= low+n1+n2-1)
        *temp++ = list->D[j++];  //剩余元素直接拷贝至temp
}


//两路合并排序算法
void MergeSort(List *list){
    Entry temp[MaxSize];
    int low,n1,n2,i,size = 1;
    while(size < list->n){
        low = 0;      //low是一对待合并序列中第一个序列的第一个元素下标
        while(low+size < list->n){
            //low+size < list->n说明至少存在两个子序列需要合并
            n1 = size;
            if(low+size*2 < list->n) n2 = size;  //计算第二个序列长度
            else n2 = list->n-low-size;
            Merge(list,temp,low,n1,n2);
            low += n1+n2;  //确定下一对待合并序列中第一个序列的第一个元素下标
        }
        for(i = 0;i < list->n;i ++){
            list->D[i] = temp[i];  //复制一趟合并排序结果
        }
        size *= 2;  //子序列长度翻倍
    }
}
*/

//Merge函数,参考了陈慧南老师的《数据结构——C语言描述》教材
void Merge(List *list,int Temp[],int i1,int j1,int i2,int j2,int *k){
    int i = i1,j = i2;
    while((i <= j1)&&(j<=j2)){                       //若两个子序列都不空,则循环
        if(list->D[i].key <= list->D[j].key){
            Temp[(*k)++] = list->D[i++].key;         //将较小元素存入Temp[*k]
        }
        else Temp[(*k)++] = list->D[j++].key;
    }
    while(i <= j1) Temp[(*k)++] = list->D[i++].key;  //将子序列1中剩余元素存入Temp
    while(j <= j2) Temp[(*k)++] = list->D[j++].key;  //将子序列2中剩余元素存入Temp
}


//MergeSort函数,参考了陈慧南老师的《数据结构——C语言描述》教材
void MergeSort(List *list){
    int Temp[MaxSize];
    int i1,j1,i2,j2,i,k,size = 1;              //i1,j1和i2,j2分别是两个子序列的上,下界
    while(size < list->n){
        i1 = 0;
        k = 0;
        while(i1+size < list->n){              //若i1+size < n,则说明存在两个子序列,需要再两两合并
            i2 = i1+size;                      //确定子序列2的下界和子序列1的上界
            j1 = i2-1;
            if(i2+size-1 > list->n-1){         //设置子序列2的上界
                j2 = list->n-1;
            }
            else j2 = i2+size-1;
            Merge(list,Temp,i1,j1,i2,j2,&k);  //合并相邻两个子序列
            i1 = j2+1;                        //确定下一次合并第一个子序列的下界
        }
        for(i = 0;i < k;i ++){
            list->D[i].key = Temp[i];
        }
        size *= 2;                            //子序列长度扩大一倍
    }
}

//输出
int Output(List *list){
    if(!list->n){
        return ERROR;
    }
    for(int i = 0;i < list->n-1;i ++){
        printf("%d",list->D[i].key);
    }
    return OK;
}

int main(){
    List a[MaxSize];
    int n,func;
    printf("Please enter the size of the list:");
    scanf("%d",&n);
    printf("Please enter the list:");
    for(int i = 0;i < n;i ++){
        scanf("%d",&a[i]);
    }
    printf("Please Choose the sort algorithm:");
    scanf("%d",&func);
    switch(func){
        case 1:SelectSort(a);Output(a);break;
        case 2:InsertSort(a);Output(a);break;
        case 3:BubbleSort(a);Output(a);break;
        case 4:QuickSort(a);Output(a);break;
        case 5:MergeSort(a);Output(a);break;
        default:break;
    }
    return 0;
}
