/*
// 利用优先权队列，未完成
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

typedef struct priQueue{
    int n, maxSize;
    ElemType *elements;
}PriQueue;

typedef struct hfmTNode{    //哈夫曼树节点结构
    ElemType Data;    //结点的数据域
    int  w;                      //结点的权值 
    HFMTNode *lChild,*rChild;  //结点的左孩子、右孩子
}HFMTNode;   

typedef struct hfmTree{    //哈夫曼树结构
    HFMTNode  *root;
}HFMTree;


int IsFull(priQueue H){
    return H->Size == H->Capacity;
}

int IsEmpty(PriQueue H){
    return H->Size == 0;
}


// 向上调整
void AdjustUp(PriQueue *PQ, int j)  //PQ为优先权队列存储数组
{
     int i=j;
     ElemType  temp = PQ->elements[i];
     while  (i>0 && temp<PQ->elements[(i-1)/2]){
	          PQ->elements[i]=PQ->elements[(i-1)/2]; 
               i = (i-1)/2;
     }
     PQ->elements[i]=temp;
}


// 插入一个新元素
void  Append(PriQueue *PQ, ElemType x){
    if(IsFull(PQ)) {
    printf("Overflow");
    return;
    }
    PQ->elements[PQ->n++]=x;
    AdjustUp(PQ, PQ->n-1);
}


// 获取优先权最高的元素
ElemType Serve(PriQueue *PQ){
    ElemType  temp;
    if(IsEmpty(PQ)){
    printf("Underflow");
    return;
    }
	temp=PQ->elements[0];
    PQ->elements[0]=PQ->elements[--(PQ->n)];
    AdjustDown (PQ, 0, n-1);
    return temp;
}


// 创建哈夫曼树
Void CreateHFMTree (HFMTree *hfmt, int W[], int n)   //W为权值数组
{
    int i;
    PriQueue *PQ;   // 空优先权队列
    HFMTree  *temp, *x, *y, *z;   // 空哈夫曼树
    for (i=0; i<n; i++) {    //初始化优先权队列
        temp = NewNode(W[i]); 
        Append(PQ, temp);
    }
    if(PQ->n >= 2)
        while(PQ->n>1){
        x=Serve(PQ); 
        y=Serve(PQ); //获取根节点权值最小的2棵树
	    MakeTree(z, (x->w + y->w), x, y);    //构造新树
        Append(PQ, z);       //将新树加入优先权队列
	}
    hfmt = Serve(PQ);    //最后生成的哈夫曼树
}


void MakeTree(BFMTree *tree,  int w, BinaryTree *left, BinaryTree *right) {
    if(tree->root || left==right)    return;
    SetNode(tree->root, w, left.root, right.root);
    left->root = right->root = NULL;
} 

void SetNode(HFMTNode *node, int w, BTNode* l, BTNode* r) { 
    node->data = w;    node->lChild = l;    node->rChild = r;
}    

HFMTNode * NewNode(int w) { 
    HFMTree *node = (HFMTree *) malloc(sizeof(HFMTree));
    node->data = w;    node->lChild = l;    node->rChild = r;
    return  node；
}
*/


// 学校课本代码，有问题
/*
#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
#define MAX 100;

// 学校课本哈夫曼树结点
typedef struct HFMTNode{
    ElementType Data;
    int w;
    int parent,lchild,rchild;
}HFMTNode;


// 构造哈夫曼树，学校课本
HFMTNode* CreateHFMTree(HFMTNode Ht[], int N){
    int i,k,lmin,rmin;
    int min1,min2;
    for(i = 1;i < 2*N;i++){
        Ht[i].parent = Ht[i].lchild = Ht[i].rchild = -1;
    }
    for(i = N+1;i < 2*N;i++){
        min1 = min2 = MAX;
        lmin = rmin = -1;
        for(k = 1;k <= i-1;k++){
            if(Ht[k].parent == -1){
                if(Ht[k].w < min1){
                    min2 = min1;
                    rmin = lmin;
                    min1 = Ht[k].w;
                    lmin = k;
                }
                else if(Ht[k].w < min2){
                    min2 = Ht[k].w;
                    rmin = k;
                }
            }
        }
        Ht[lmin].parent = i;
        Ht[rmin].parent = i;
        Ht[i].w = Ht[lmin].w + Ht[rmin].w;
        Ht[i].lchild = lmin;
        Ht[i].rchild = rmin;
    }
    // q = malloc(sizeof(HFMTNode));
    // q->Data = Ht[;
    // return q;
    return Ht;
}



// 前序遍历，有问题
void PreOrderTransverse(HFMTNode *t){
    if(t==NULL){
        return;
    }
    printf("%c ",t->Data);
    PreOrderTransverse(t->lchild);
    PreOrderTransverse(t->rchild);
}


// 求哈夫曼树的带路径长度
void WPL(HFMTNode *t,int lev,int *sum){
    if(t){
        if(!t->lchild && !t->rchild){
            (*sum) += lev * t->Data;
        }
        WPL(t->lchild,lev+1,&sum);
        WPL(t->rchild,lev+1,&sum);
    }
}


// 哈夫曼编码
// len初始化为0
void HFMCoding(HFMTNode *t,int len){
    static int a[10];  // 定义静态数组 a，保存每个叶子的编码，数组长度至少是树深度减一
    if(t){
        if(!t->lchild && !t->rchild){
            int i;
            printf("The code of HFMTNode whose weight is %d is：",t->w);
            for(i = 0;i < len;i ++){
                printf("%d",a[i]);
            }
            printf("\n");
        }
        else{
            a[len] = 0;
            HFMCoding(t->lchild,len+1);
            a[len] = 1;
            HFMCoding(t->rchild,len+1);
        }
    }
}


int main(){
    int n,i;
    ElementType *a,*sum;
    HFMTNode H[100];
    HFMTNode *t;
    printf("Please enter the number of HFMTNodes:");
    while(1){
        scanf("%d",&n);
        if(n > 1){
            break;
        }
        else printf("Please enter again:");  // 程序健壮性
    }
    a = malloc(n * sizeof(HFMTNode));
    printf("Please enter %d weights of HFMTree:",n);
    for(i = 0;i < n;i ++){
        scanf("%d",&a[i]);
    }
    t = CreateHFMTree(H,8);
    printf("\nPreOrderTransverse:\n");
    PreOrderTransverse(t);
    printf("\n\nThe WPL of HFMTree is:");
    WPL(t,0,&sum);
    printf("%d\n",sum);
    printf("\nThe codes of HFMTNodes are:\n");
    HFMCoding(t,0);
    return 0;
}
*/



// 其他代码
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int ElementType;
char s[] = {"ABCDEF"};
char temp[6][3];
typedef struct HFMTNode{
    ElementType data;  
    struct HFMTNode *lchild;  
    struct HFMTNode *rchild;  
}HFMTNode;


//输出哈夫曼树，元素类型为int  
void PrintHFMTree(HFMTNode *t){  
    if (t != NULL)  
    {  
        printf("%d ", t->data); // 输出根结点的值  
        if (t->lchild != NULL || t->rchild != NULL)  
        {  
            // printf("(");  
            PrintHFMTree(t->lchild); // 输出左子树  
            //if (BT->right != NULL)  
                // printf(",");  
            PrintHFMTree(t->rchild); // 输出右子树  
            // printf(")");  
        }
    }  
}  


// 根据数组 a 中 n 个权值建立一棵哈夫曼树，返回树根指针
// struct HFMTNode* CreateHFMTree(ElementType a[], int n)
int CreateHFMTree(ElementType a[], int n)  {  
    int i, j,k1,k2;  
    HFMTNode **b, *q;  
    b = malloc(n*sizeof(struct HFMTNode));  // 动态生成一维数组，存放哈夫曼树的结点
    for (i = 0; i < n; i++) // 初始化 b 指针数组，使每个指针元素指向 a 数组中对应的元素结点  
    {  
        b[i] = malloc(sizeof(struct HFMTNode));  
        b[i]->data = a[i];  
        b[i]->lchild = b[i]->rchild = NULL;  
    }  
    for (i = 1; i < n; i++)// n-1 次循环,建立哈夫曼树  
    {  
        //k1 表示森林中具有最小权值的树根结点的下标，k2 为次最小的下标  
        k1 = -1;
        for (j = 0; j < n; j++) // 让 k1 初始指向森林中第一棵树，k2 指向第二棵  
        {  
            if (b[j] != NULL && k1 == -1)  // 第一棵树不为空树且k1未标记
            {  
                k1 = j;  
                continue;  
            }  
            if (b[j] != NULL)  // 第一棵树不为空树
            {  
                k2 = j;  
                break;  
            }  
        }  
        for (j = k2; j < n; j++)// 从当前森林中求出最小权值树和次最小权值树
        {  
            if (b[j] != NULL)  
            {  
                if (b[j]->data < b[k1]->data)  
                {  
                    k2 = k1;  
                    k1 = j;  
                }  
                else if (b[j]->data < b[k2]->data)  
                    k2 = j;  
            }  
        }  
        // 由最小权值树和次最小权值树建立一棵新树，q 指向树根结点  
        q = malloc(sizeof(HFMTNode));  
        q->data = b[k1]->data + b[k2]->data;  
        q->lchild = b[k1];  
        q->rchild = b[k2];  
  
        b[k1] = q;// 将指向新树的指针赋给 b 指针数组中 k1 位置  
        b[k2] = NULL;//k2 位置为空  
    }  
    free(b); // 删除动态建立的数组 b  
    return q; // 返回整个哈夫曼树的树根指针  
}  
  

//求哈夫曼树的带权路径长度  
ElementType WPL(HFMTNode *t, int len){ //len 初始为 0  
    if (t == NULL)  // 空树返回 0
        return 0;  
    else{  
        if (t->lchild == NULL && t->rchild == NULL)// 访问到叶子结点  
            return t->data * len;  
        else // 访问到非叶子结点，进行递归调用，返回左右子树的带权路径长度之和，len 递增  
            return WPL(t->lchild,len+1) + WPL(t->rchild,len+1);
    }
}

/*
// 求哈夫曼树的带路径长度
void WPL(HFMTNode *t,int lev,int *sum){
    if(t){
        if(!t->lchild && !t->rchild){
            (*sum) += lev * t->Data;
        }
        WPL(t->lchild,lev+1,&sum);
        WPL(t->rchild,lev+1,&sum);
    }
}
*/


// 哈夫曼编码
// len初始化为0
void HFMCoding(HFMTNode *t,int len,ElementType *b){
    static int a[10];  // 定义静态数组 a，保存每个叶子的编码，数组长度至少是树高度减一
    if(t){
        if(!t->lchild && !t->rchild){  // 左右子树都为空
            int i,k;
            printf("The code of HFMTNode whose weight is %d is:",t->data);
            for(i = 0;i < 6;i ++){
                if(b[i] == t->data){
                    printf("%c---",s[i]); // 权重大小位置对应的字符
                    k = i;
                }
            }
            for(i = 0;i < len;i ++){
                // itoa(a[i],temp[k][i]);
                // sscanf(a[i],"%c",temp[k][i]);
                printf("%d",a[i]); // 输出编码   
            }
            sscanf(a,"%s",&temp[k]);
            // j ++;
            printf("\n");
        }
        else{  // 左右子树不为空
            a[len] = 0;
            HFMCoding(t->lchild,len+1,b);
            a[len] = 1;
            HFMCoding(t->rchild,len+1,b);
        }
    }
}



// 哈夫曼解码
void HFMDeCoding(char str1[],int len){
    int i,j,k;
    char tempt[10][2];
    /*
    char temp[6][3];
    temp[0][0] = '1';
    temp[0][1] = '0';
    temp[1][0] = '0';
    temp[1][1] = '1';
    */
   /*
    for(i = 0,j = 0;j < len/2;j ++){
        for(k = 0;k < len/2;k ++){
            tempt[j][k] = str1[i++];
        }
    }
    for(i = 0;i < len/2;i ++){
        for(j = 0;j < 6;j ++){
            if((tempt[i][0] == temp[j][0])&&(tempt[i][1] == temp[j][1])){
                printf("%c",s[j]);
            }
        }
    }
    */
    
    for(i = 0,k = 0;i < len/2;i ++,k = k + 2){
       for(j = 0;j < 6;j ++){
           if((str1[k] == temp[j][0])&&(str1[k+1] == temp[j][1])){
               printf("%c",s[j]);
           }
       }
   }
}



/*
void HFMDeCoding(HFMTNode *t,char str1,int i){
    int j;
    while(t){
        if(str1[i] == '0'){
            HFMDeCoding(t->lchild,str1,i++,j);
        }
        else
            HFMDeCoding(t->rchild,str1,i,j++);
        if(!t->lchild && !t->rchild){
            printf("%c",)
        }
    }
}
*/




void main(){
    int n,i;
    char str[100];
    // char temp[6][3];
    ElementType *a;
    struct HFMTNode *t;
    printf("Please enter the number of HFMTNodes:");
    while(1){
        scanf("%d",&n);
        if(n > 1){
            break;
        }
        else printf("\nPlease enter again:");  // 程序健壮性
    }
    a = malloc(n * sizeof(HFMTNode));
    printf("\nPlease enter %d weights of HFMTree:\n",n);
    for(i = 0;i < n;i ++){
        scanf("%d",&a[i]);
    }
    t = CreateHFMTree(a,n);
    printf("\nPrintHFMTree:\n");
    PrintHFMTree(t);
    printf("\n\nThe WPL of HFMTree is:");
    printf("%d\n",WPL(t,0));
    printf("\nThe codes of HFMTNodes are:\n");
    HFMCoding(t,0,a);
    printf("\nPlease enter the number of HFMTNodes:");
    // scanf("%d",&code);
    sscanf("1001","%s",str);  // 将输入的int型转化成字符串型
    printf("%s",str);
    printf("\nThe decodes of codes are:");
    
    HFMDeCoding(str,4);
    // return 0;
}
