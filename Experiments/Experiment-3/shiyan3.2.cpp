#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<queue>
#define ERROR 0
#define OK 1
#define Overflow 2  //表示上溢
#define Underflow 3  //表示下溢
#define NotPresent 4 //表示元素不存在
#define Duplicate 5  //表示有重复元素
typedef int ElemType;
typedef int Status;

//邻接矩阵的结构体定义
typedef struct{
    ElemType **a;     //邻接矩阵
    int n;            //图的当前顶点数
    int e;            //图的当前边数
    ElemType noEdge;  //两顶点间无边时的值
}mGraph;


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


//邻接矩阵的初始化
Status Init(mGraph *mg,int nSize,ElemType noEdgeValue){
    int i,j;
    mg->n = nSize;               //初始化顶点数
    mg->e = 0;                   //初始化时没有边
    mg->noEdge = noEdgeValue;    //初始化没有边时的取值
    mg->a = (ElemType**)malloc(nSize*sizeof(ElemType *));  //生成长度为n的一维指针数组
    if(!mg->a) return ERROR;
    for(i = 0;i < mg->n;i ++){   //动态生成二维数组
        mg->a[i] = (ElemType*)malloc(nSize*sizeof(ElemType));
        for(j = 0;j < mg->n;j ++){
            mg->a[i][j] = mg->noEdge;
        }
        mg->a[i][i] = 0;        //自回路设置为0
    }
    return OK;
}


//邻接矩阵的撤销(改成了int型，有返回值),先释放一维数组,再释放指针数组
int Destory(mGraph *mg){
    int i;
    for(i = 0;i < mg->n;i ++){
        free(mg->a[i]);  //释放n个一维数组的存储空间
    }
    free(mg->a);         //释放一维数组的存储空间
    return 1;
}


//邻接矩阵的边的搜索
Status Exist(mGraph *mg,int u,int v){
    if(u < 0||v < 0||u > mg->n-1||v > mg->n-1 ||u == v||mg->a[u][v] == mg->noEdge) return ERROR;
    return OK;
}


//邻接矩阵的边的插入
Status Insert(mGraph *mg,int u,int v,ElemType w){
    if(u < 0||v < 0||u > mg->n-1||v > mg->n-1 ||u == v) return ERROR;
    if(mg->a[u][v] != mg->noEdge) return Duplicate;  //若待插入边已存在,则返回出错信息
    mg->a[u][v] = w;                                 //插入新边
    mg->e ++;                                        //增加一条边
    return OK;
}


//邻接矩阵的边的删除
Status Remove(mGraph *mg,int u,int v){
    if(u < 0||v < 0||u > mg->n-1||v > mg->n-1 ||u == v) return ERROR;
    if(mg->a[u][v] == mg->noEdge) return NotPresent;  //若待删除边不存在,则返回出错信息
    mg->a[u][v] = mg->noEdge;                         //删除边
    mg->e --;
    return OK;
}


//邻接矩阵的单一顶点DFS
void DFS(int v,int visited[],mGraph g){
    int j;
    printf("%d ",v);              //访问顶点v
    visited[v] = 1;               //为顶点v打上访问标记       
    for(j = 0;j < g.n; j++){      //遍历v的邻接点
        if(!visited[j] && g.a[v][j] > 0){  //当未被访问且有权值
            DFS(j,visited,g);
        }
    }
}


//邻接矩阵的全图DFS
void DFSGraph(mGraph g){
    int i;
    int *visited = (int*)malloc(g.n * sizeof(int)); //动态生成标记数组visted
    for(i = 0;i < g.n;i ++){
        visited[i] = 0;          //visted数组初始化
    }                            //visted数组初始化
    for(i = 0;i < g.n;i ++){     //逐一检查每个顶点,若未被访问,则调用DFS
        if(!visited[i]){         //当未被访问且有权值
            DFS(i,visited,g);
        }
    }                      
    free(visited);                       //释放visted数组
}


//邻接矩阵的单一顶点BFS
void BFS(int v,int visited[],mGraph g){
    Queue q;
    Create(&q,g.n);                        //初始化队列
    visited[v] = 1;                        //为顶点v打上访问标记
    printf("%d ",v);                       //访问顶点v
    EnQueue(&q,v);                         //将顶点v放入队列
    while(!IsEmpty(&q)){
        Front(&q,&v);
        DeQueue(&q);                       //队首顶点出队列
        for(int i = 0;i < g.n;i ++){       //遍历v的每一项
            if(!visited[i] && g.a[v][i] > 0){       //若未被访问且有权值,则将其访问并放入队列,注意这里判断的是g.a[v][i]二维数组
                visited[i] = 1;
                printf("%d ",i);
                EnQueue(&q,i);
            }
        }
    }
}


//邻接矩阵的全图BFS
void BFSGraph(mGraph g){
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
    mGraph g;
    int nSize,edge,u,v,i;
    ElemType w;
    printf("Please enter the size of the mgraph:");
    scanf("%d",&nSize);
    Init(&g,nSize,-1);
    printf("Please enter the number of the edges:");
    scanf("%d",&edge);
    printf("Now init the graph.\n");
    /*
    for(i = 0;i < nSize;i ++){
        for(j = 0;j < nSize;j ++){
            printf("Please enter the edge:");
            scanf("%d%d%d",&u,&v,&w);
            Insert(&g,u,v,w);
        }
    }
    */
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