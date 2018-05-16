// 计算一棵二叉树中关键字等于x的结点个数：
// count在main主函数里初始化为0
void Count(Btree *t,int *count,int x){
    if(t == NULL){
        return;
    }
    if(t->root->data == x){
        count += 1;  
    }
    Count(t->left,&count,x);  //因为把count定义为指针变量，传的是count的地址，所以要加&
    Count(t->right,&count,x);
}



//简单选择排序算法
int SelectSort(int a[],int n){
    int i,j,small,x;
    for(i = 0;i < n;i ++){
        small = i;
        for(j = i + 1;j < n;j ++){
            if(a[small] > a[j]){
                small = j;
            }
        }
        if(small != i){
            x = a[i];
            a[i] = a[small];
            a[small] = x;
        }
    }
    return 0;
}