#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2    //表示上溢
#define Underflow 3   //表示下溢
#define NotPresent 4  //表示元素不存在
#define Duplicate 5   //表示有重复元素
typedef int ElemType;
typedef int Status;

//邻接矩阵的结构体定义
typedef struct{
    ElemType **a;     //邻接矩阵
    int n;            //图的当前顶点数
    int e;            //图的当前边数
    ElemType noEdge;  //两顶点间无边时的值
}mGraph;


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
            mg->a[i][j] = mg->noEdge;  //初始化时权重都设为-1
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



int main(){
    mGraph g;
    int nSize,edge,u,v,i,j;
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
    /*插入改用这个比较简单,只插入存在的边*/
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
    //destory
    printf("\nNow destory the graph:");
    if(Destory(&g)) printf("OK");
    else printf("ERROR");
    return 0;
}