#include<stdio.h>
#include<stdlib.h>

typedef struct PNode{
    int coef;             //系数
    int exp;              //指数
    struct PNode* link;
}PNode;

typedef struct{
    struct PNode *head;
}polynominal;


//多项式的创建
void Create(polynominal *p){
    PNode *pn,*pre,*q;
    p->head = (PNode*)malloc(sizeof(PNode));
    p->head->exp = -1;
    p->head->link = p->head;               //对教材做了修改
    //p->head->link = NULL;                //教材原代码
    for(;;){
        pn=(PNode*)malloc(sizeof(PNode));
        printf("coef:\n");
        scanf("%d",&pn->coef);
        printf("exp:\n");
        scanf("%d",&pn->exp);
        if(pn->exp<0) break;
        pre = p->head;
        q = p->head->link;
        while(q && q->exp > pn->exp){
            pre = q;
            q = q->link;
        }
        pn->link = q;
        pre->link = pn;
    }
}


//多项式输出
void Output(polynominal p){
    PNode *q;
    int flag = 1;                                   //打标记,记录是否为第一项
    q = p.head->link;
    if (!q){
        return;
    }
    while(q != p.head){
        if (!flag && (q->coef > 0)) printf("+");	//在非第一项的正系数前输出+号
        flag = 0;                                   //flag置为0,表示不是第一项
        if(q->coef == 0){                           //当前项系数为0
            return;
        }
        printf("%d",q->coef);                       //当前项系数不为0
        switch(q->exp){                             //判断当前项指数
            case 0:break;                           //当前项指数为0,退出
            case 1:printf("X");break;               //当前项指数为1,输出X
            default:printf("X^%d",q->exp);break;    //当前项指数不为0,也不为1
        }
        q = q->link;
    }
}


/*
//多项式的输出
void Output(polynominal p){
    PNode *pn = p.head->link;
    printf("Poly:%dx^%d",pn->coef,pn->exp);  //这里有问题
    //printf("Poly:");
    pn = pn->link;
    while(pn){
        if(pn->coef>0) printf("+");  //如果系数为负数，不输出+
        if(pn->exp == 0){
            if(pn->coef != 1){
            printf("%d",pn->coef);
            }
            else printf("1");
        }
        else if(pn->coef == 1){
            printf("x^%d",pn->exp);
        }
        else if(pn->coef == -1){
            printf("-x^%d",pn->exp);
        }
        else printf("%dx^%d",pn->coef,pn->exp);
        pn = pn->link;
    }
    printf("\n");
}
*/


//多项式的相加,结果存入qx中
void Add(polynominal *px,polynominal *qx){
    PNode *q,*q1 = qx->head,*p, *p1,*temp;    //q1指向qx的表头结点
    p = px->head->link;                       //p指向多项式px的第一个结点
    p1 = px->head;
    q = q1->link;                             //q1是q的前驱
    while(p->exp >= 0){
        while(p->exp < q->exp){               //跳过q->exp大的项
            q1 = q;
            q = q->link;
        }
        if(p->exp == q->exp){                 //当指数相等时,系数相加
            q->coef = q->coef + p->coef;
            if(q->coef == 0){                 //若相加后系数为0
                q1->link = q->link;           //删除q
                free(q);                      //释放q的空间
                q = q1->link;                 //重置q指针
                p = p->link;
            } 
            else{                             //若相加后系数不为0
                q1 = q;                       //q1后移
                q = q->link;
                p = p->link;                  //p也后移
            }
        }
        else{                                 //p->exp > q->exp的情况
            temp = malloc(sizeof(PNode));     //以p的系数和指数生成新结点
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            q1 = q1->link;
            p = p->link;
        }
   }
}


/*
//多项式加法,书上的原代码,有问题
void Add(polynominal *px,polynominal *qx){
    PNode *q,*q1 = qx->head,*p,*temp;
    p = px->head->link;
    q = q1->link;
    while(p&&q){
        while(p->exp < q->exp){
            q1 = q;
            q = q->link;
        }
        if(p->exp == q->exp){
            q->coef = q->coef + p->coef;
            if(q->coef == 0){
                q1->link = q->link;
                free(q);
                q = q1->link;
                p = p->link;
            }
            else{
                q1 = q;
                q = q->link;
                p = p->link;
            }
        }
        else{
            temp = (PNode*)malloc(sizeof(PNode));
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            p = p->link;
        }
    }
}
*/


// 多项式减法
void Sub(polynominal *px,polynominal *qx){
    PNode *q,*q1 = qx->head,*p,*temp;
    p = px->head->link;
    q = q1->link;
    while(q){
        q->coef *= -1;   // 把q的系数都乘-1，后面再用加法
        q = q->link;
    }
    q=q1->link;
    while(p&&q){
        while(p->exp < q->exp){
            q1 = q;
            q = q->link;
        }
        if(p->exp == q->exp){
            q->coef = p->coef + q->coef;
            if(q->coef == 0){
                q1->link = q->link;
                free(q);
                q = q1->link;
                p = p->link;
            }
            else{
                q1 = q;
                q = q->link;
                p = p->link;
            }
        }
        else{
            temp = (PNode*)malloc(sizeof(PNode));
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            p = p->link;
        }
    }
}


/*
void Multiply(polynominal *px,polynominal *pn)   //多项式相乘，并将结果存入px
{
	PNode *p,*p1,*p2,*q;
	p1=px->head;
	p=(PNode*)malloc(sizeof(PNode));
	p->link=NULL;
	while(p1)
	{
		p2=pn->head;
		while(p2)
		{
			q=(PNode*)malloc(sizeof(PNode));
			q->coef=p1->coef*p2->coef;
			q->exp=p1->exp+p2->exp;
			p->link=q;
			p=q;
			p2=p2->link;
		}
		p1=p1->link;
		if(p1!=px->head->link)
		printf("%dx^%d+",p->coef,p->exp);
	}
	p->link=NULL;

}
*/


/*
//只能输出一项乘一项的结果
void Multiply(polynominal *px, polynominal *qx){
    PNode *p,*q,*temp,*s1,*s2;
    PNode *sum = (PNode*)malloc(sizeof(PNode));
    temp = (PNode*)malloc(sizeof(PNode));
    p = px->head->link;
    printf("Poly:");
    while(p){
        q = qx->head->link;
        while(q){  //p的每一项和q的每一项相乘
            temp->coef = p->coef * q->coef;
            temp->exp = p->exp + q->exp;
            s1 = sum;
            s2 = s1->link;
            while(s2 && temp->exp < s2->exp){
                s1 = s2;
                s2 = s2->link;  // s2一直移到大于temp指数的第一个位置
            }
            temp->link = s2;
            sum = temp;
            q = q->link;
        }
        p = p->link;
    }
    
    // 结果输出
    s1 = sum;
    printf("%dx^%d",s1->coef,s1->exp);
    while(s1->link){
        s1 = s1->link;
        if(s1->coef>0) printf("+");  //如果系数为负数，不输出+
        if(s1->exp == 0){
            if(s1->coef != 1){
            printf("%d",s1->coef);
            }
            else printf("1");
        }
        else if(s1->coef == 1){
            printf("x^%d",s1->exp);
        }
        else if(s1->coef == -1){
            printf("-x^%d",s1->exp);
        }
        else printf("%dx^%d",s1->coef,s1->exp);
    }
    /*
    s1 = sum->head->link;
    q = qx->head->link;  
    while(s1){
        q->coef = s1->coef;
        q->exp = s1->exp;
        q = q->link;
        s1 = s1->link;
    }
    */
   /*
}
*/


/*
void Multiply(polynominal *P1, polynominal *P2){  
    PNode *current1,*current2,*current,*pre;
    polynominal *temp;
    current1 = P1->link;  
    current2 = P2->link;  
    temp->head = (PNode*)malloc(sizeof(PNode)); 
    temp->link = NULL;  
  
//1、用多项式 1 的第一个结点 current1 与多项式二的各个节点依次相乘，结果存放在以 P1 指向的结点为头结点的链表中，current1 指向下一个结点  
//2、用多项式 1 的 current1 与多项式二的各个节点依次相乘，结果存放在以 temp 指向的结点为头结点的链表中，current1 指向下一个结点  
//3、将以上两个链表相加  
//4、循环重复步骤 2 和 3 直至 current1 指向下一个结点为空  
    for(; current1 != NULL; current1 = current1->link ){        
        for(current2 = P2->link; current2 != NULL; current2 = current2->link){  
            current->head = (PNode *)malloc(sizeof(PNode));       // 创建一个新的多项式结点  
            current->link->coef = current1->coef * current2->coef; // 给该结点赋值
            current->link->exp = current1->exp + current2->exp;  
            current->link->link = NULL;  
            if(current2 == P2->link ){
                if(current1 == P1->link ){  
                    pre = P1;  
                    P1->link = current;  
                }  
                else{  
                    pre = temp;  
                    temp->link = current;  
                }  
            }  
            else{  
                pre->link = current;  
            }  
            pre = current;  
        }  
        if(temp->link != NULL );  
            Add(&P1), &temp);  
    }  
//  free(temp);  
    temp->link = NULL;  
    P2->link = NULL;  
}
*/


/*
// 多项式相乘
void Multiply(polynominal *px,polynominal *qx){
    PNode *q,*q1 = qx->head,*p, *temp;
    polynominal *t = (polynominal*)malloc(sizeof(polynominal));
    int x,y;  //做交换用
    temp = t->head->link;
    p = px->head->link;
    //q = q1->link;

    // 每一项进行相乘
    // temp = temp->link;
    while(p){
        q = q1->link;
        while(q){
            temp->coef = p->coef * q->coef;
            temp->exp = p->exp + q->exp;
            temp = temp->link;
            q = q->link;
        }
        p = p->link;
    }

    // 冒泡排序，按指数非递减排序
    for(p = t->head->link;p;p = p->link){
        for(q = p->link;q;q = q->link){
            if(p->exp < q->exp){
                x = p->exp;
                p->exp = q->exp;
                q->exp = x;
                y = p->coef;
                p->coef = q->coef;
                q->coef = y;
            }
        }
    }
    p = qx->head->link;
    q = t->head->link;

    // 把乘完之后排好序的传进qx中
    while(q){
        p->coef = q->coef;
        p->exp = q->exp;
        p = p->link;
        q = q->link;
    }
    p = qx->head->link;

    // 指数相同进行相加
    while(p){
        if(p->exp == p->link->exp){
            p->coef += p->link->coef;
            p->link = p->link->link;
            free(p->link);
            p = p->link;
        }
        else p = p->link;
    }
}
*/


//多项式乘法,暂时没有问题
void Multiply(polynominal *px,polynominal *qx){
    polynominal qx1,qx2;
    PNode *q1,*q2,*q3,*q4,*pre,*q;
    qx1.head = (PNode*)malloc(sizeof(PNode));       //生成新多项式qx1
    qx1.head->exp = -1;
    qx1.head->link = qx1.head;                      //qx1改造成循环链表
    q1 = px->head->link;                            //q1指向px的第一项
    q2 = qx->head->link;                            //q2指向qx的第一项
    while(q2->exp != -1){                           //当q2的指数不为-1时,px先和qx的每一项相乘
        q3 = (PNode*)malloc(sizeof(PNode));         //q3存放相乘的结果
        q3->coef = q1->coef * q2->coef;
        q3->exp = q1->exp + q2->exp;
        if(qx1.head->link->exp == -1){              //q3插入到qx1多项式第一项中
            q3->link = qx1.head->link;
            qx1.head->link = q3;
            pre = qx1.head->link;
        }
        else{                                       //q3插入到qx1多项式最后一项中
            q3->link = qx1.head;
            pre->link = q3;
            pre = pre->link;
        }
        q2 = q2->link;
    }
    q1 = q1->link;                                 //q1后移一位
    while(q1->exp != -1){                          //px剩下来每一项都和qx每一项相乘
        q2 = q2->link;
        qx2.head = (PNode*)malloc(sizeof(PNode));  //生成新多项式qx2
        qx2.head->exp = -1;
        qx2.head->link = qx2.head;
        while(q2->exp != -1){   	
            q4 = (PNode*)malloc(sizeof(PNode));
            q4->coef = q1->coef * q2->coef;
            q4->exp = q1->exp + q2->exp;
            if(qx2.head->link->exp == -1){
                q4->link = qx2.head->link;
                qx2.head->link = q4;
                pre = qx2.head->link;
            }
            else{
                q4->link = qx2.head;
                pre->link = q4;
                pre = pre->link;
            }
            q2 = q2->link;
        }
        Add(&qx2,&qx1);                            //合并同类项
        q1 = q1->link;
    }
    Output(qx1);
}


//多项式的撤销
void Destroy(polynominal *p){
	PNode *pn;
	while(p->head->link)
	{
		pn = p->head->link; 
		free(p->head);
		p->head = pn;
	}
}



int main(){
    polynominal p,q;
    int x;
    //sum.head->link = NULL;
    printf("Please enter the first poly:\n");
    Create(&p);
    Output(p);
    printf("\n\nPlease enter the second poly:\n");
    Create(&q);
    Output(q);
    //Create(&sum);
    //Output(sum);
    //printf("\nAdd:\n");
    //Add(&p,&q);
    //Output(q);
    //Sub(&p,&q);
    //Output(q);
    printf("\n\nPlease choose the function:\n");
    scanf("%d",&x);
    switch(x){                                   //选择加法还是乘法功能
        case 0:printf("Add:\n");
        Add(&p,&q);
        Output(q);
        break;
        case 1:printf("Multiply:\n");
        Multiply(&p,&q);
        default:break;
    }
    //Output(q);
    //Destroy(&p);
    return 0;
}
