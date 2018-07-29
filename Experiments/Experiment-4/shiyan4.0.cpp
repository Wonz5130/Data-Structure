#include<iostream>
using namespace std;
#include<time.h>
#include<algorithm>
#include<stdlib.h>
#include <cstdio>
#include <cstring>
#define random(x) (rand()%x)
#define NUM 100000 

clock_t start,stop;
double duration;
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
void InsertSort(int A[],int n)   //直接插入排序
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
void BubbleSort(int A[],int n)   //冒泡排序
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
void QuickSort(int A[],int n)     //快速排序
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
void GQuickSort(int A[],int n)     //改进的快速排序
{
    GQSort(A,0,n-1);
}
void Merge(int A[],int i1,int j1,int i2,int j2)    //两路合并排序
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
int main()
{
    int a[NUM];//乱序 
    int b[NUM];
    int c[NUM];
    int d[NUM];//乱序 
    int e[NUM];
    int f[NUM];
    int g[NUM];//乱序 
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    memset(d,0,sizeof(d));
    memset(e,0,sizeof(e));
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    srand((int)time(0));
    for(int x=0;x<NUM;x++)
    {
        a[x]=random(NUM);
        b[x]=a[x];
        c[x]=a[x];
        d[x]=a[x];
        e[x]=a[x];
        f[x]=a[x];
        g[x]=a[x];
//      cout<<a[x]<<endl;
    }
    start = clock();
    SelectSort(a,NUM);
    stop = clock();
    cout<<"简单选择法排序完成时间为："<<endl;
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    start = clock();
    InsertSort(b,NUM);   //直接插入排序
    stop = clock();
    cout<<"直接插入法排序完成时间为："<<endl;
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    start = clock();
    BubbleSort(c,NUM);  //冒泡排序
    stop = clock();
    cout<<"冒泡法排序完成时间为："<<endl;
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    start = clock();
    QuickSort(d,NUM);//快速排序
    stop = clock();
    cout<<"快速排序完成时间为："<<endl;
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    start = clock();
    GQuickSort(e,NUM);//改进的快速排序
    stop = clock();
    cout<<"改进的快速排序完成时间为："<<endl;
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    start = clock();
    MergeSort(f,NUM);
    stop = clock();
    cout<<"合并法排序完成时间为："<<endl;
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    start = clock();
    HeapSort(g,NUM);
    stop = clock();
    cout<<"堆排序完成时间为："<<endl;
    duration = (double)(stop-start)/CLK_TCK;
    cout<<duration<<endl;
    return 0;
} 
