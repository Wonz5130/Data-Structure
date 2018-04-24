#include<cstdio>
int main(){
    int i,j,n;
    int a[8]={0};
    int b[8]={0};
    int c[8]={0};
    scanf("%d",&n);
    for(i = 0;i < n;i ++){
        scanf("%d",&a[i]);
    }
    for(i = 0;i < n; i++){
        for(j = 0;j < n;j ++){
            if(a[j]<a[i]){
                b[i]++;
            }
        }
    }
    for(i = 0;i < n;i ++){
        c[b[i]] = a[i];
    }
    for(i = 0;i < n;i ++){
        a[i]=c[i];
        printf("%d ",a[i]);
    }
    return 0;
}