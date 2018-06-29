typedef struct ENode{
    int adjVex;
    struct ENode *nextArc;
}ENode;

typedef struct{
    int n;
    ENode **A;
}LGraph;

int Degree(LGraph g,int v){
    int i,d = 0;
    ENode *p;
    for(i = 0;i < g.n;i ++){
        for(p = g.A[i];p;p = p->nextArc){
            if(p->adjVex == v){
                d ++;
            }
        }
    }
    return d;
}