#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef char T;
typedef struct BinaryTreeNode{
    T Data;
    struct BinaryTreeNode *LChild, *RChild;
}BinaryTreeNode;

// 先序遍历构建二叉树
BinaryTreeNode *PreCreateBt(BinaryTreeNode *t){
    char ch;
    ch = getchar();
    if(ch == '#'){
        t = NULL;
    }
    else{
        t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        t->Data = ch;
        t->LChild = PreCreateBt(t->LChild);
        t->RChild = PreCreateBt(t->RChild);
    }
    return t;
}


// 前序遍历
void PreOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    printf("%c",t->Data);
    PreOrderTransverse(t->LChild);
    PreOrderTransverse(t->RChild);
}


// 中序遍历
void InOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    InOrderTransverse(t->LChild);
    printf("%c",t->Data);
    InOrderTransverse(t->RChild);
}


// 后序遍历
void PostOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    PostOrderTransverse(t->LChild);
    PostOrderTransverse(t->RChild);
    printf("%c",t->Data);
}



// 求二叉树结点个数
int Size(BinaryTreeNode *t){
    if(!t) return 0;
    return Size(t->LChild) + Size(t->RChild) + 1;
}


// 求二叉树叶子结点个数
int Leaf(BinaryTreeNode *t){
    if(t==NULL) return 0;
    if((t->LChild == NULL) && (t->RChild == NULL)) return 1;
    return Leaf(t->LChild) + Leaf(t->RChild);
}


// 求二叉树的高度
int Depth(BinaryTreeNode *t){
    if(!t) return 0;
    // else return (1 + Depth(t->LChild) > Depth(t->RChild) ? Depth(t->LChild) : Depth(t->RChild));
    else return 1 + max(Depth(t->LChild) , Depth(t->RChild));
}


// 交换二叉树
void Exch(BinaryTreeNode *t){
    if(t){
        BinaryTreeNode *q = t->LChild;
        t->LChild = t->RChild;
        t->RChild = q;
        Exch(t->LChild);
        Exch(t->RChild);
    }
}

int main(){
    BinaryTreeNode *t = NULL;
    t = PreCreateBt(t);
    printf("The number of Nodes:%d\n",Size(t));
    printf("The number of LeafNodes:%d\n",Leaf(t));
    printf("The height of the tree:%d\n",Depth(t));
    Exch(t);
    printf("\nAfter exchanging the BinaryTree:\n\n");
    printf("PreOrderTransverse:\n");
    PreOrderTransverse(t);
    printf("\n\nInOrderTransverse:\n");
    InOrderTransverse(t);
    printf("\n\nPostOrderTransverse:\n");
    PostOrderTransverse(t);
    printf("\n");
    return 0;
}
