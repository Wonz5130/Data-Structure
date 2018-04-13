/*
// 最大堆
#include<cstdio>
#define N 100
void AdjustHeap(int Heap[],int s,int m){
    int temp = Heap[s];
    for(int j = 2*s+1;j <= m; j *= 2){
        if(j < m&&Heap[j] < Heap[j+1]){
            j++;
        }
        if(temp > Heap[j]){
            break;
        }
        Heap[s] = Heap[j];
        s = j;
    }
    Heap[s] = temp;
}
void CreateHeap(int heap[],int n){
    for(int i = (n-2)/2;i >= 0;i --){
        AdjustHeap(heap,i,n);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int heap[N];
    for(int i = 0;i < n;i ++){
        scanf("%d",&heap[i]);
    }
    CreateHeap(heap,n);
    for(int i = 0;i < n;i ++){
        printf("%d ",heap[i]);
    }
    return 0;
}
*/



// 最小堆
#include<cstdio>
#define N 100
void AdjustHeap(int Heap[],int s,int m){
    int temp = Heap[s];
    for(int j = 2*s+1;j <= m; j *= 2){
        if(j < m&&Heap[j] > Heap[j+1]){
            j++;
        }
        if(temp < Heap[j]){
            break;
        }
        Heap[s] = Heap[j];
        s = j;
    }
    Heap[s] = temp;
}
void CreateHeap(int heap[],int n){
    for(int i = (n-2)/2;i >= 0;i --){
        AdjustHeap(heap,i,n);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int heap[N];
    for(int i = 0;i < n;i ++){
        scanf("%d",&heap[i]);
    }
    CreateHeap(heap,n);
    for(int i = 0;i < n;i ++){
        printf("%d ",heap[i]);
    }
    return 0;
}