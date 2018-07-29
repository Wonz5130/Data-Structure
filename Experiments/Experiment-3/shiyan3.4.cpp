#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2      //表示上溢
#define Underflow 3     //表示下溢
#define NotPresent 4    //表示元素不存在
#define Duplicate 5     //表示有重复元素
typedef int ElemType;
typedef int Status;


//邻接表的结构体定义
typedef struct ENode{
    int adjVex;              //任意顶点u相邻的顶点
    ElemType w;              //边的权值
    struct ENode *nextArc;   //指向下一个边结点
}ENode;

typedef struct{
    int n;           //图的当前顶点数
    int e;           //图的当前边数
    ENode **a;       //指向一维指针数组
}LGraph;


//循环队列的结构体定义
typedef struct{
    int front;
    int rear;
    int maxSize;    //最大容量
    ElemType *element;
}Queue;


//创建一个能容纳mSize个单元的空队列
void Create(Queue *Q,int mSize){
    Q->maxSize=mSize;
    Q->element=(ElemType*)malloc(sizeof(ElemType)*mSize);
    Q->front=Q->rear=0;
}


//判断队列是否为空,若是,则返回TRUE;否则返回FALSE
BOOL IsEmpty(Queue *Q){
    return Q->front==Q->rear;
}


//判断队列是否已满,若是,则返回TRUE,否则返回FALSE
BOOL IsFULL(Queue *Q){
    return (Q->rear+1)%Q->maxSize==Q->front;
}


//获取队头元素,并通过x返回.若操作成功,则返回TRUE,否则返回FALSE
BOOL Front(Queue *Q,ElemType *x){
    if(IsEmpty(Q))      //空队列处理
        return FALSE;
    *x=Q->element[(Q->front+1)%Q->maxSize];
    return TRUE;
}


//入队.在队列Q的队尾插入元素x(入队操作)。操作成功,则返回TRUE,否则返回FALSE
BOOL EnQueue(Queue *Q,ElemType x){
    if(IsFULL(Q))      //溢出处理
        return FALSE;
    Q->rear=(Q->rear+1)%Q->maxSize;
    Q->element[Q->rear]=x;
    return TRUE;
}


//出队.从队列Q中删除队头元素(出队操作)。操作成功,则返回TRUE,否则返回FALSE
BOOL DeQueue(Queue *Q){
    if(IsEmpty(Q)){   //空队列处理
        return FALSE;
    }
    Q->front=(Q->front+1)%Q->maxSize;
    return TRUE;
}


//邻接表的初始化
Status Init(LGraph *lg,int nSize){
    int  i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize*sizeof(ENode*)); //动态生成长度为n的一维指针数组
    if(!lg->a) return ERROR;
    else{
        for(i = 0;i < lg->n;i ++){
            lg->a[i] = NULL;                       //将指针数组a置空
        }
        return OK;
    }
}


//邻接表的搜索边
Status Exist(LGraph *lg,int u,int v){
    ENode *p;
    if(u < 0||v < 0||u > lg->n-1||v > lg->n-1 ||u == v) return ERROR;
    p = lg->a[u];                 //指针p指向顶点u的单链表的第一个边结点
    while(p && p->adjVex != v){
        p = p->nextArc;
    }
    if(!p) return ERROR;          //若未找到此边,则返回ERROR
    else return OK;
}


//邻接表的插入边
Status Insert(LGraph *lg,int u,int v,ElemType w){
    ENode *p;
    if(u < 0||v < 0||u > lg->n-1||v > lg->n-1 ||u == v) return ERROR;
    if(Exist(lg,u,v)) return Duplicate;       //此边已存在,返回错误
    p = (ENode*)malloc(sizeof(ENode));        //为新的边结点分配存储空间
    p->adjVex = v;
    p->w = w;
    p -> nextArc = lg->a[u];                  //将新的边结点插入单链表的最前面
    lg->a[u] = p;
    lg->e ++;                                 //边加1
    return OK;
}


//邻接表的单一顶点DFS
void DFS(int v,int visited[],LGraph g){
    ENode *w;
    printf("%d ",v);                           //访问顶点v
    visited[v] = 1;                            //为顶点v打上访问标记
    for(w = g.a[v];w;w = w->nextArc){          //遍历v的邻接点
        if(!visited[w->adjVex]){
            DFS(w->adjVex,visited,g);          //若w未被访问,则递归调用DFS
        }
    }
}


//邻接表的全图DFS
void DFSGraph(LGraph g){
    int i;
    int *visited = (int*)malloc(g.n * sizeof(int)); //动态生成标记数组visted
    for(i = 0;i < g.n;i ++){
        visited[i] = 0;                             //visted数组初始化
    }
    for(i = 0;i < g.n;i ++){                        //逐一检查每个顶点,若未被访问,则调用DFS
        if(!visited[i]){
            DFS(i,visited,g);
        }
    }
    free(visited);                                  //释放visted数组
}


//邻接表的单一顶点BFS
void BFS(int v,int visited[],LGraph g){
    ENode *w;
    Queue q;
    Create(&q,g.n);                        //初始化队列
    visited[v] = 1;                        //为顶点v打上访问标记
    printf("%d ",v);                       //访问顶点v
    EnQueue(&q,v);                         //将顶点v放入队列
    while(!IsEmpty(&q)){
        Front(&q,&v);
        DeQueue(&q);                       //队首顶点出队列
        for(w = g.a[v];w;w = w->nextArc){  //遍历v的所有邻接点
            if(!visited[w->adjVex]){       //若w未被访问,则将其访问并放入队列
                visited[w->adjVex] = 1;
                printf("%d ",w->adjVex);
                EnQueue(&q,w->adjVex);
            }
        }
    }
}


//邻接表的全图BFS
void BFSGraph(LGraph g){
    int i;
    int *visited = (int*)malloc(g.n * sizeof(int));  //动态生成visited数组
    for(i = 0;i < g.n;i ++){                         //初始化visited数组
        visited[i] = 0;
    }
    for(i = 0 ;i < g.n;i ++){                        //逐一检查每个顶点,若未被访问,则调用BFS
        if(!visited[i]){
            BFS(i,visited,g);
        }
    }
    free(visited);
}



int main(){
    LGraph g;
    int i,u,v,enode,edge;
    ElemType w;
    printf("Please enter the number of the ENodes:");
    scanf("%d",&enode);
    Init(&g,enode);
    printf("Please enter the number of the edges:");
    scanf("%d",&edge);
    printf("Now init the graph.\n");
    for(i = 0;i < edge;i ++){
        printf("Please enter the edge:");
        scanf("%d%d%d",&u,&v,&w);
        Insert(&g,u,v,w);
    }
    printf("DFS:\n");
    DFSGraph(g);
    printf("\nBFS:\n");
    BFSGraph(g);
    return 0;
}