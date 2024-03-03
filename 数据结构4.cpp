#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAXLENGTH 20
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {             //表结点类型定义
        int adjvex;              	    //顶点位置编号 
     struct ArcNode  *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode{                //头结点及其数组类型定义
        VertexType data;           	   //顶点信息
     ArcNode *firstarc;                  //指向第一条弧
    } VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  		   //邻接表的类型定义
    AdjList vertices;                      //头结点数组
    int vexnum,arcnum;               //顶点数、弧数
    GraphKind  kind;                   //图的类型
   } ALGraph;
typedef struct{  	  	  //线性表的集合类型定义
     struct { char name[30];
               ALGraph G;    
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 
LISTS Lists;

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);

int visited[20];//标记访问数组，已经访问为1，为访问为0；
void DFS(ALGraph &G,void (*visit)(VertexType),int i)
{
    ArcNode * p;
    (*visit)(G.vertices[i].data);
    visited[i]=1;
    for(p=G.vertices[i].firstarc;p!=NULL;p=p->nextarc)
    {
        if(!visited[p->adjvex]) DFS(G,visit,p->adjvex);
    }
}

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

int inqueue[20];//标记是否已经在访问队列，或已经访问
typedef struct QUEUE {
     int elem[MAXLENGTH];
     int front,length;
     } QUEUE;

void iniQueue(QUEUE &Q)
//该函数实现初始化Q
{
/***************begin***************/
    Q.front=0;
    Q.length=0;

/*************** end ***************/
}

int enQueue(QUEUE &Q,int e)
//将元素e入队Q。成功入栈返回1，否则返回0
{
/***************begin***************/
    if(Q.length<MAXLENGTH)
    {
        Q.elem[(Q.front+Q.length)%MAXLENGTH]=e;
        Q.length++;
        return 1;
    }
    else return 0;

/*************** end ***************/
}

int deQueue(QUEUE &Q, int &e)
//将Q队首元素出队，赋值给e。成功出队返回1，否则返回0
{
/***************begin***************/
    if(Q.length>0)
    {
        e=Q.elem[Q.front];
        Q.front=(Q.front+1)%MAXLENGTH;
        Q.length--;
        return 1;
    }
    return 0;
/*************** end ***************/
}

int emptyQueue(QUEUE Q)
{
    if(Q.length==0) return TRUE;
    else return FALSE;
}

int main(void)
{
	VertexType V[30];
	KeyType VR[100][2]; 
	VertexType value;
	ALGraph G;
	int operate1=1; 
	int operate2 = 1; 
	int i,k,v,w,u;//序号 
	char listname[30];
	char x[] = "C:\\Users\\86153\\高博文\\a.txt";
	while(operate1){
	system("cls");
	printf("\n\n");
	printf("                       欢迎来到多图管理菜单 \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  创建无向图    2.  删除无向图\n");
	printf("                       3.  查找无向图    4.  选择无向图\n");
	printf("                       0.  退出\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~4]:\n");
	scanf("%d", &operate1);
	switch (operate1)
	{
	case 1:
	//AddList
		printf("\n请输入要增加的无向图名称\n");
		scanf("%s", listname);
		AddList(Lists,listname);
		printf("\n增加无向图成功\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;		 
		

	case 2:
	//RemoveList
		printf("\n请输入要删除的无向图名称\n");
		scanf("%s", listname);
		if(RemoveList(Lists,listname)==OK)
			printf("\n删除无向图成功\n");
		else
			printf("\n删除无向图失败\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;	
		
	case 3:
	//locateList
		printf("\n请输入要查找的无向图名称\n");
		scanf("%s", listname);
		if(LocateList(Lists,listname)!=0)
			printf("\n查找的无向图序号为%d\n",LocateList(Lists,listname));
		else
			printf("\n查找无向图失败\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;	
	
	case 4:
	printf("选择需要操作的无向图序号\n");
	scanf("%d",&k);
	G=Lists.elem[k-1].G;
	operate2=1;
	while (operate2) {
	system("cls");
	printf("\n\n");
	printf("                       Welcome to the 无向图管理 menu \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  创建无向图        2.  销毁无向图\n");
	printf("                       3.  查找顶点          4.  顶点赋值\n");
	printf("                       5.  获得第一邻接点    6.  获得下一邻接点\n");	
	printf("                       7.  插入顶点          8.  删除顶点\n");
	printf("                       9.  插入弧            10. 删除弧\n");
	printf("                       11. 深度优先搜索遍历  12. 广度优先搜索遍历\n");
	printf("                       13. 文件存储          14. 文件读取\n");
	printf("                       15. 打印图            0.  退出\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~14]:\n");
	scanf("%d", &operate2);
	switch (operate2)
	{
	case 1:
	//CreateGraph 
		i=0;
		printf("输入无向图的结点数据\n");
		do 
		{
    		scanf("%d%s",&V[i].key,V[i].others);
		} while(V[i++].key!=-1);
		i=0;
		printf("输入弧的关系\n");
		do 
		{
    		scanf("%d%d",&VR[i][0],&VR[i][1]);
   		} while(VR[i++][0]!=-1);
		if (CreateGraph(G,V,VR)==ERROR) printf("输入数据错，无法创建");
		else for(i=0;i<G.vexnum;i++)
		{
     		ArcNode *p=G.vertices[i].firstarc;
     		printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     		while (p)
     		{
         		printf(" %d",p->adjvex);
         		p=p->nextarc;
     		}
     		printf("\n");
		}
		printf("创建成功！"); 
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
     	break;
	
	case 2:
	//DestroyGraph
        if (DestroyGraph(G)==OK) 
   			printf("销毁无向图成功\n");
        else printf("销毁无向图失败\n");
    	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 3:
	//LocateVex
    		printf("输入需要查找的结点\n");
			scanf("%d",&u);   
			i=LocateVex(G,u);
			if (i!=-1)
				printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else
				printf("查找失败\n");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 4:
	//PutVex
		printf("输入需要赋值的结点u\n"); 
		scanf("%d",&u);   
		printf("输入新的结点value的数据结构\n"); 
		scanf("%d%s",&value.key,value.others);
		i=PutVex(G,u,value);
		if (i==OK)
		{
			for(i=0;i<G.vexnum;i++)
     		printf(" %d %s\n",G.vertices[i].data.key,G.vertices[i].data.others);
     		printf("赋值成功！");
		}
		else
			printf("赋值操作失败");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 5:
	//FirstAdjVex
		printf("输入要查找的结点关键字\n");
 		scanf("%d",&u);   
		i=FirstAdjVex(G,u);
		if (i!=-1)
			printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
		else
			printf("查找失败\n");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 6:
	//NextAdjVex
		printf("输入结点v和它的邻接点w\n"); 
		scanf("%d%d",&v,&w);   
		i=NextAdjVex(G,v,w);
		if (i!=-1)
			printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
		else
			printf("无下一邻接顶点\n");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 7:
	//InsertVex
		printf("输入需要插入的新顶点\n");
		scanf("%d%s",&value.key,value.others);
		i=InsertVex(G,value);
		if (i==OK)
		for(i=0;i<G.vexnum;i++)
		{
     		ArcNode *p=G.vertices[i].firstarc;
     		printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     		while (p)
     		{
         		printf(" %d",p->adjvex);
         		p=p->nextarc;
     		}
     		printf("\n");
		}
		else printf("插入操作失败\n");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 8:
	//DeleteVex
		printf("输入需要删除的顶点\n");
		scanf("%d",&v);
		i=DeleteVex(G,v);
		if (i==OK) 
		{
			for(i=0;i<G.vexnum;i++)
			{
     			ArcNode *p=G.vertices[i].firstarc;
     			printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     			while (p)
     			{
         			printf(" %d",p->adjvex);
         			p=p->nextarc;
     			}
     			printf("\n");
			}
		}
		else printf("删除顶点操作失败\n");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 9:
	//InsertArc
		printf("输入需要插入的弧\n");
		scanf("%d%d",&v,&w);
		i=InsertArc(G,v,w);
		if (i==OK) 
		{
			for(i=0;i<G.vexnum;i++)
			{
     			ArcNode *p=G.vertices[i].firstarc;
     			printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     			while (p)
     			{
        			printf(" %d",p->adjvex);
        			p=p->nextarc;
     			}
     			printf("\n");
			}
		}	
		else printf("插入弧操作失败\n");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 10:
	//DeleteArc
		printf("输入需要删除的弧\n");
		scanf("%d%d",&v,&w);
		i=DeleteArc(G,v,w);
		if (i==OK)
		{
			for(i=0;i<G.vexnum;i++)
			{
     			ArcNode *p=G.vertices[i].firstarc;
     			printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     			while (p)
     			{
        			printf(" %d",p->adjvex);
        			p=p->nextarc;
     			}
     			printf("\n");
			}
		}
		else printf("删除弧操作失败");
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 11:
	//DFSTraverse
		DFSTraverse(G,visit);
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 12:
	//BFSTraverse
		BFSTraverse(G,visit);
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
    	
	case 13:
	//SaveGraph
	    if (k = SaveGraph(G, x) == OK)
        printf("文件保存成功\n");
    	else printf("文件保存失败\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;
		
	case 14:
	//LoadGraph
	    if (i = LoadGraph(G, x) == OK)
        printf("文件输入成功\n");
        else printf("文件输入失败\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;
		
	case 15:
	//printGraph
		for(i=0;i<G.vexnum;i++)
		{
     		ArcNode *p=G.vertices[i].firstarc;
     		printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     		while (p)
     		{
         		printf(" %d",p->adjvex);
         		p=p->nextarc;
     		}
     		printf("\n"); 
     	}
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;
}
}
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;
		
	
}
}
	return 0;
}



status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=0,k=0,m=0,n=0,b=0;
    int a[100];
    for(i=0;i<=99;i++) a[i]=0;
    for(i=0;V[i].key!=-1;i++)
    {
        if(i>19) return ERROR;
        a[V[i].key]+=1;
        if(a[V[i].key]==2) return ERROR;
    }
    for(k=0;VR[k][1]!=-1;k++)
    {
        if((a[VR[k][0]]==0)||(a[VR[k][1]]==0)) return ERROR;
    }
    //判断合法
    G.vexnum=0;
    G.arcnum=0;
    ArcNode *p;
    for(i=0;V[i].key!=-1;i++)
    {
        G.vertices[i].data=V[i];
        G.vertices[i].firstarc=NULL;
        G.vexnum++;
    }
    for(k=0;VR[k][0]!=-1;k++)
    {

    	b++;
        for(i=0;V[i].key!=-1;i++) 
        {
            if(V[i].key==VR[k][0])
            break;
        }
        for(m=0;V[m].key!=-1;m++)
        {
            if(V[m].key==VR[k][1])
            break;
        }
    	p=(ArcNode*)malloc(sizeof(ArcNode));    
    	p->adjvex=m;
		p->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=p;
    	p=(ArcNode*)malloc(sizeof(ArcNode));    
    	p->adjvex=i;
		p->nextarc=G.vertices[m].firstarc; 
		G.vertices[m].firstarc=p;

    }
    return OK;
    /********** End **********/
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=0;
    ArcNode *p,*q;
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertices[i].firstarc->nextarc;
        G.vertices[i].firstarc=NULL;
        while(p)
        {
            q=p;
            p=p->nextarc;
            free(q);
        }
    }
    G.vexnum=0;
    return OK;
    /********** End **********/
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,k=0;
    for(int i=0;i<G.vexnum;i++)
    {
        if(u==G.vertices[i].data.key)
        {
            k++;
            return i;
        }
    }
    if(k==0)
    return -1;
    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,k=0;
    for(i=0;i<G.vexnum;i++)
    {
        if(value.key==G.vertices[i].data.key)
        return ERROR;
    }
    for(i=0;i<G.vexnum;i++)
    {
        if(u==G.vertices[i].data.key)
        {
            k++;
            G.vertices[i].data=value;
            return OK;
        }
    }
    if(k==0)
    return ERROR;

    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,k=0;
    for(int i=0;i<G.vexnum;i++)
    {
        if(u==G.vertices[i].data.key)
        {
        	if(G.vertices[i].firstarc)
        	{
            	k++;
            	return G.vertices[i].firstarc->adjvex;
            }
        }
    }
    if(k==0)
    return -1;

    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    ArcNode *p;
    for(int i=0;i<G.vexnum;i++)
    {
        if(v==G.vertices[i].data.key)
        {
            p=G.vertices[i].firstarc;
            while(p)
            {
                if(G.vertices[p->adjvex].data.key==w)
                {
                    p=p->nextarc;
                    if(p) return p->adjvex;
                    else return -1;
                }
                p=p->nextarc;
            }

        }
    }
    return -1;

    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/    
    if(G.vexnum==20) return ERROR;
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(v.key==G.vertices[i].data.key)
        return ERROR;
    }
    
    G.vertices[i].data=v;
    G.vexnum++;
    G.vertices[i].firstarc=NULL;
    return OK;

    /********** End **********/
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=0,k=0,m=0;
    ArcNode *p,*q;
    if(G.vexnum==1) return ERROR;
    for(i=0;i<=G.vexnum-1;i++)
    {
        if(v==G.vertices[i].data.key)
        {
            if(G.vertices[i].firstarc!=NULL)
            {
                p=G.vertices[i].firstarc->nextarc;
                G.vertices[i].firstarc=NULL;
                while(p)
                {
                    q=p;
                    p=p->nextarc;
                    free(q);
                }
            }
            
            for(m=0;m<=G.vexnum-1;m++)
            {
                if(m!=i)
                {
                    p=G.vertices[m].firstarc;
                    if(p)
                    {
                        if(G.vertices[p->adjvex].data.key==v)
                        {
                            G.vertices[m].firstarc=p->nextarc;
                            free(p);
                        }
                        else
                        {
                            while(p->nextarc)
                            {
                                if(G.vertices[p->nextarc->adjvex].data.key==v)
                                {
                                    q=p->nextarc;
                                    p->nextarc=p->nextarc->nextarc;
                                    free(q);
                                    break;
                                }
                                p=p->nextarc;
                            }   
                        }
                    }         
                }
            }
            
            for(m=0;m<=G.vexnum-1;m++)
            {
                if(m!=i)
                {
                    p=G.vertices[m].firstarc;
                    while(p)
                    {
                        if(p->adjvex>=i)  p->adjvex--;
                        p=p->nextarc;
                    }
                }
            }
            for(k=i;k<=G.vexnum-2;k++)
            G.vertices[k]=G.vertices[k+1];
            G.vexnum--;
            G.vertices[k].data.key=-1;
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,k=0,x=0,y=0;
    ArcNode *p,*q;
    for(x=0;x<G.vexnum;x++)
    {
        if(v==G.vertices[x].data.key)
        {
            k++;
            break;
        }
    }
    for(y=0;y<G.vexnum;y++)
    {
        if(w==G.vertices[y].data.key)
        {
            k++;
            break;
        }
    }
    if(k!=2) return ERROR;
    p=G.vertices[x].firstarc;
    if(p)
    {
        if(G.vertices[p->adjvex].data.key==w)
        {
            return ERROR;
        }
        while(p->nextarc)
        {
            if(G.vertices[p->nextarc->adjvex].data.key==w)
            {
                return ERROR;
            }
            p=p->nextarc;
        }
    	p=(ArcNode*)malloc(sizeof(ArcNode));    
    	p->adjvex=y;
        p->nextarc=G.vertices[x].firstarc;
        G.vertices[x].firstarc=p;
    	p=(ArcNode*)malloc(sizeof(ArcNode));    
    	p->adjvex=x;
        p->nextarc=G.vertices[y].firstarc;
        G.vertices[y].firstarc=p;
        return OK;
    }
    else
    {
    	p=(ArcNode*)malloc(sizeof(ArcNode));    
    	p->adjvex=y;
        p->nextarc=G.vertices[x].firstarc;
        G.vertices[x].firstarc=p;
    	p=(ArcNode*)malloc(sizeof(ArcNode));    
    	p->adjvex=x;
        p->nextarc=G.vertices[y].firstarc;
        G.vertices[y].firstarc=p;
        return OK;
    }


    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i,k=0;
    ArcNode *p,*q;
    for(i=0;i<G.vexnum;i++)
    {
        if(v==G.vertices[i].data.key)
        {
            p=G.vertices[i].firstarc;
            if(G.vertices[p->adjvex].data.key==w)
            {
                G.vertices[i].firstarc=p->nextarc;
                free(p);
                break;
            }
            while(p->nextarc)
            {
                if(G.vertices[p->nextarc->adjvex].data.key==w)
                {
                    q=p->nextarc;
                    p->nextarc=p->nextarc->nextarc;
                    free(q);
                    break;
                }
                p=p->nextarc;
            }

        }
    }
    for(i=0;i<G.vexnum;i++)
    {
        if(w==G.vertices[i].data.key)
        {
            p=G.vertices[i].firstarc;
            if(G.vertices[p->adjvex].data.key==v)
            {
                G.vertices[i].firstarc=p->nextarc;
                free(p);
                return OK;
            }
            while(p->nextarc)
            {                
                if(G.vertices[p->nextarc->adjvex].data.key==v)
                {
                    q=p->nextarc;
                    p->nextarc=p->nextarc->nextarc;
                    free(q);
                    return OK;
                }
                p=p->nextarc;
            }
        }
    }
    return ERROR;
    /********** End **********/
}


status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited[i]) DFS(G,visit,i);
    }
    return OK;
    /********** End **********/
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int e;//本函数中无用
    int i,j;
    ArcNode *p;
    QUEUE Q;
    iniQueue(Q);
    for(j=0;j<G.vexnum;j++)
    {
        if(!inqueue[j])
        {
            enQueue(Q,j);
            inqueue[j]=1;
            for(i=Q.front;i-Q.front+1<=Q.length;i++)//一个联通子图中的结点未全部入队列
            {
                for(p=G.vertices[Q.elem[i]].firstarc;p!=NULL;p=p->nextarc)
                {
                    if(!inqueue[p->adjvex])
                    {
                        enQueue(Q,p->adjvex);
                        inqueue[p->adjvex]=1;
                    }
                }
            }
            while(!emptyQueue(Q))
            {
                deQueue(Q,e);
                (*visit)(G.vertices[e].data);
            }
        }

    }

    return OK;
    /********** End **********/
}


status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE* fout = fopen(FileName, "wt");
    if (fout == NULL) exit(-1);
    int i;
    ArcNode* temp;
    for (i = 0;i < G.vexnum;i++)
    {
        fprintf(fout, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);//先输出节点数据
        temp = G.vertices[i].firstarc;
        while (temp != NULL)
        {
            fprintf(fout, "%d ", temp->adjvex);
            temp = temp->nextarc;
        }
        fprintf(fout, "-1 ");//表示一个节点输出完了（包括邻接表）
    }
    //结尾输入-2表示所有输出结束
    fclose(fout);
    return OK;
    /********** End 1 **********/
}


status LoadGraph(ALGraph& G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    int vexn = 0, arcn = 0;
    ArcNode* te, * pre;
    FILE* fin = fopen(FileName, "rt");
    if (fin == NULL) exit(-1);
    int tkey, t;
    char tothers[20];//暂时储存的数据
    while (fscanf(fin, "%d%s", &tkey, tothers) != EOF)
    {
        G.vertices[vexn].data.key = tkey;
        strcpy(G.vertices[vexn].data.others, tothers);
        fscanf(fin, "%d", &t);
        if (t != -1)
        {
            te = (ArcNode*)malloc(sizeof(ArcNode));
            G.vertices[vexn].firstarc = te;
            te->adjvex = t;
            te->nextarc = NULL;
            fscanf(fin, "%d", &t);
            while (t != -1)
            {
                pre = te;
                te = (ArcNode*)malloc(sizeof(ArcNode));
                pre->nextarc = te;
                te->adjvex = t;
                te->nextarc = NULL;
                fscanf(fin, "%d", &t);
            }
        }
        else
        {
            G.vertices[vexn].firstarc = NULL;
        }
        vexn++;
    }
    G.vexnum = vexn;
    fclose(fin);
    return OK;
    /********** End 2 **********/
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的无向图
{
    int j=0;
    for(j=0;ListName[j]!='\0';j++){
        Lists.elem[Lists.length].name[j]=ListName[j];
    }
    Lists.elem[Lists.length].name[j]='\0';
    ALGraph G;
    Lists.elem[Lists.length].G=G;
    Lists.length+=1;
}


status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的无向图 
{
    int i;
    int k=0;
    for(i=0;i<=Lists.length-1;i++){
        while(Lists.elem[i].name[k]==ListName[k]){
            k++;
            if((Lists.elem[i].name[k]=='\0')&&(ListName[k]=='\0'))
            break;
        }
         if((Lists.elem[i].name[k]=='\0')&&(ListName[k]=='\0'))
            break;
    }
    if((Lists.elem[i].name[k]=='\0')&&(ListName[k]=='\0')){
        int m;
        int n=0;
        for(m=i;m<=Lists.length-1;m++)
        {
            Lists.elem[m].G=Lists.elem[m+1].G;
            while(Lists.elem[m].name[n]!='\0'){
                Lists.elem[m].name[n]=Lists.elem[m+1].name[n];
                n++;
            }
        }
        Lists.length--;
        return OK;
    }
    else return ERROR;
}


int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的无向图，成功返回逻辑序号，否则返回0
{
    int i;
    int k=0;
    for(i=0;i<=Lists.length-1;i++){
        while(Lists.elem[i].name[k]==ListName[k]){
            k++;
            if((Lists.elem[i].name[k]=='\0')&&(ListName[k]=='\0'))
            break;
        }
         if((Lists.elem[i].name[k]=='\0')&&(ListName[k]=='\0'))
            break;
    }
    if((Lists.elem[i].name[k]=='\0')&&(ListName[k]=='\0')){
        return i+1;
    }
    else return 0;
}

