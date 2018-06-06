#include<stdio.h>
#include<stdlib.h>
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
    ElemType **a;
    int n;
    int e;
    ElemType noEdge;
}mGraph;


//邻接矩阵的初始化
Status Init(mGraph *mg,int nSize,ElemType noEdgeValue){
    int i,j;
    mg->n = nSize;  //初始化顶点数
    mg->e = 0;       //初始化时没有边
    mg->noEdge = noEdgeValue; //初始化没有边时的取值
    mg=>a = (ElemType**)malloc(nSize*sizeof(ElemType *));  //生成长度为n的一维指针数组
    if(!mg->a) return ERROR;
    for(i = 0;i < mg->n;i ++){  //动态生成二维数组
        mg->a[i] = (ElemType*)malloc(nSize*sizeof(ElemType));
        for(j = 0;j < mg->n;j ++){
            mg->a[i][j] = mg->noEdge;
        }
        mg->a[i][j] = 0;
    }
    return OK;
}


//邻接矩阵的撤销
void Destory(mGragh *mg){
    int i;
    for(i = 0;i < mg->n;i ++){
        free(mg->a[i]);  //释放n个一维数组的存储空间
    }
    free(mg->a);  //释放一维数组的存储空间
}


//邻接矩阵的边的搜索
Status Exist(mGragh *mg,int u,int v){
    if(u < 0||v < 0||u > mg->n-1||v > mg->n-1 ||u == v||mg->a[u][v] == mg->noEdge) return ERROR;
    return OK;
}


//邻接矩阵的边的插入
Status Insert(mGraph *mg,int u,int v,ElemType w){
    if(u < 0||v < 0||u > mg->n-1||v > mg->n-1 ||u == v) return ERROR;
    if(mg->a[u][v] != mg->noEdge) return Duplicate;  //若待插入边已存在,则返回出错信息
    mg->a[u][v] = w;  //插入新边
    mg->e ++;  //增加一条边
    return OK;
}


//邻接矩阵的边的删除
Status Remove(mGragh *mg,int u,int v){
    if(u < 0||v < 0||u > mg->n-1||v > mg->n-1 ||u == v) return ERROR;
    if(mg->a[u][v] == mg->noEdge) return NotPresent;  //若待删除边不存在,则返回出错信息
    mg->a[u][v] = mg->noEdge;  //删除边
    mg->e --;
    return OK;
}


int main(){
    mGraph g;
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
    //delete one edge
    printf("Please enter the deleted edge:");
    printf("\nPlease enter the u of the edge:");
    scanf("%d",&u);
    printf("Please enter the v of the edge:");
    scanf("%d",&v);
    printf("Now search the edge:");
    if(Exist(&g,u,v)) printf("OK");
    else printf("ERROR");
    printf("\nNow delete the edge:");
    //search the deleted edge
    if(Remove(&g,u,v)) printf("OK");
    else printf("ERROR");
    //remove
    printf("\nNow destory the graph:");
    if(Destory(&g)) printf("OK");
    else printf("ERROR");
    return 0;
}
}