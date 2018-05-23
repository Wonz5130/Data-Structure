#include<stdio.h>
#include<stdlib.h>
typedef char T;
typedef struct BinaryTreeNode{
    T Data;
    struct BinaryTreeNode *LChild, *RChild;
}BinaryTreeNode;


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



int main(){
    BinaryTreeNode *t = NULL;
    t = PreCreateBt(t);  //有返回值，所以前面要加个t = ，不然后面没东西输出
    printf("\nPreOrderTransverse:\n");
	PreOrderTransverse(t);
    printf("\n\nInOrderTransverse:\n");
    InOrderTransverse(t);
    printf("\n\nPostOrderTransverse:\n");
    PostOrderTransverse(t);
    printf("\n");
    return 0;
}
