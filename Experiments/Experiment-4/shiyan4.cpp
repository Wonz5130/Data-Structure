#include<iostream>
using namespace std;
#include<time.h>
#include<algorithm>
#include<stdlib.h>
#include <cstdio>
#include <cstring>
#include<windows.h>
#include<Mmsystem.h>
#define random(x) (rand()%x)
#define NUM 500

clock_t start,stop;
double duration;

//简单选择排序
void SelectSort(int A[],int n)
{
    int small;
    for(int i =0;i<n-1;i++)
    {
        small = i;
        for(int j = i+1;j<n;j++)
        {
            if(A[j]<A[small])
            small = j;
            swap(A[i],A[small]);
        }
    }
}

//直接插入排序
void InsertSort(int A[],int n)
{
    for(int i=1;i<n;i++)
    {
        int j=i;
        int temp=A[j];
        while(j>0&&temp<A[j-1])
        {
            A[j]=A[j-1];
            j--;
        }
        A[j]=temp;
    }
}

//冒泡排序
void BubbleSort(int A[],int n)
{
    int i,j,last;
    i=n-1;
    while(i>0)
    {
        last=0;
        for(j=0;j<i;j++)
            if(A[j+1]<A[j])
            {
                swap(A[j],A[j+1]);
                last=j;
            }
        i=last;
    }
}

void QSort(int A[],int left,int right)
{
    int i,j;
    if(left<right)
    {
        i=left;
        j=right+1;
        do
        {
            do i++;while (A[i]<A[left]);
            do j--;while (A[j]>A[left]);
            if(i<j)
                swap(A[i],A[j]);
        }while(i<j);
        swap(A[left],A[j]);
        QSort(A,left,j-1);
        QSort(A,j+1,right);
    }
}

//快速排序
void QuickSort(int A[],int n)
{
    QSort(A,0,n-1);
}

void GQSort(int A[],int left,int right)
{
    int i,j;
    if(right>=9)
    {
    if(left<right)
    {
        i=left;
        j=right+1;
        do
        {
            do i++;while (A[i]<A[left]);
            do j--;while (A[j]>A[left]);
            if(i<j)
                swap(A[i],A[j]);
        }while(i<j);
        swap(A[left],A[j]);
        QSort(A,left,j-1);
        QSort(A,j+1,right);
    }
    }
    else
    {
        InsertSort(A,right-left+1);
        return ;
    }
}

//改进的快速排序
void GQuickSort(int A[],int n)
{
    GQSort(A,0,n-1);
}

//两路合并排序
void Merge(int A[],int i1,int j1,int i2,int j2)
{
    int* Temp=new int[j2-i1+1];
    int i=i1,j=i2,k=0;
    while(i<=j1&&j<=j2)
    {
        if(A[i]<=A[j])
            Temp[k++]=A[i++];
        else Temp[k++]=A[j++];
    }
    while (i<=j1)
        Temp[k++]=A[i++];
    while(j<=j2)
        Temp[k++]=A[j++];
    for(i=0;i<k;i++)
        A[i1++]=Temp[i];
    delete[] Temp;
}
void MergeSort(int A[],int n)
{
    int i1,j1,i2,j2;
    int size=1;
    while(size<n)
    {
        i1=0;
        while(i1+size<n)
        {
            i2=i1+size;
            j1=i2-1;
            if(i2+size-1>n-1)
                j2=n-1;
            else
                j2=i2+size-1;
            Merge(A,i1,j1,i2,j2);
            i1=j2+1;
        }
        size*=2;
    }
}


//堆排序
void AdjustDown(int A[],int r,int j)
{
    int child=2*r+1;
    int temp=A[r];
    while (child<=j)
    {
        if((child<j)&&(A[child]<A[child+1]))
            child++;
        if(temp>=A[child])
            break;
        A[(child-1)/2]=A[child];
        child=2*child+1;
    }
    A[(child-1)/2]=temp;
}


void HeapSort(int A[],int n)
{
    for(int i=(n-2)/2;i>-1;i--)
        AdjustDown(A,i,n-1);
    for(int i=n-1;i>0;i--)
    {
        swap(A[0],A[i]);
        AdjustDown(A,0,i-1);
    }
}

void Output(int A[],int n){
    for(int i = 0;i < n;i ++){
        printf("%d ",A[i]);
    }
}

void TimeOfSelectSort(int A[],int n){
    //SelectSort
    start = clock();
    //start = timeGetTime();
    SelectSort(A,n);
    stop = clock();
    //stop = timeGetTime();
    //printf("\nThe List after SelectSort is:\n");
    //Output(a,NUM);
    printf("The time of SelectSort is:\n");
    duration = (double)(stop-start)/(CLOCKS_PER_SEC);  //强制类型转换
    printf("%f",duration);
    //cout<<duration<<endl;
}

int main()
{
    int *a,*b,*c,*d,*e,*f,*g;
    //long long NUM;
    //printf("Please enter the size of List:");
    //scanf("%lld",&NUM);
    a = (int*)malloc(NUM * sizeof(int));
    b = (int*)malloc(NUM * sizeof(int));
    c = (int*)malloc(NUM * sizeof(int));
    d = (int*)malloc(NUM * sizeof(int));
    e = (int*)malloc(NUM * sizeof(int));
    f = (int*)malloc(NUM * sizeof(int));
    g = (int*)malloc(NUM * sizeof(int));
    /*
    //不用malloc的话,随机生成100000个数时,会出现停止运行
    int a[NUM];//乱序 
    int b[NUM];
    int c[NUM];
    int d[NUM];//乱序 
    int e[NUM];
    int f[NUM];
    int g[NUM];//乱序 
    */
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    memset(d,0,sizeof(d));
    memset(e,0,sizeof(e));
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    srand((int)time(0));
    for(int x = 0;x < NUM;x ++){
        a[x]=random(NUM);
        b[x]=a[x];
        c[x]=a[x];
        d[x]=a[x];
        e[x]=a[x];
        f[x]=a[x];
        g[x]=a[x];
        //cout<<a[x]<<endl;
    }
    //Output
    //printf("The initial List is:\n");
    //Output(a,NUM);
    TimeOfSelectSort(a,NUM);
    //InsertSort
    start = clock();
    InsertSort(b,NUM);
    stop = clock();
    //printf("\nThe List after SelectSort is:\n");
    //Output(a,NUM);
    printf("\nThe time of InsertSort is:\n");
    duration = (double)(stop-start)/(CLOCKS_PER_SEC);
    printf("%f",duration);
    //cout<<duration<<endl;
    //BubbleSort
    start = clock();
    BubbleSort(c,NUM);
    stop = clock();
    //printf("\nThe List after SelectSort is:\n");
    //Output(a,NUM);
    printf("\nThe time of BubbleSort is:\n");
    duration = (double)(stop-start)/(CLOCKS_PER_SEC);
    printf("%f",duration);
    //cout<<duration<<endl;
    //QuickSort
    start = clock();
    QuickSort(d,NUM);
    stop = clock();
    //printf("\nThe List after SelectSort is:\n");
    //Output(a,NUM);
    printf("\nThe time of QuickSort is:\n");
    duration = (double)(stop-start)/(CLOCKS_PER_SEC);
    printf("%f",duration);
    //cout<<duration<<endl;
    /*
    //ImproveQuickSort
    start = clock();
    GQuickSort(e,NUM);//改进的快速排序
    stop = clock();
    printf("The time of ImproveQuickSort is:\n");
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    */
    //MergeSort
    start = clock();
    MergeSort(f,NUM);
    stop = clock();
    //printf("\nThe List after SelectSort is:\n");
    //Output(a,NUM);
    printf("\nThe time of MergeSort is:\n");
    duration = (double)(stop-start)/(CLOCKS_PER_SEC);
    printf("%f",duration);
    //cout<<duration<<endl;
    /*
    start = clock();
    HeapSort(g,NUM);
    stop = clock();
    printf("The time of HeapSort is:\n");
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    */
    return 0;
} 