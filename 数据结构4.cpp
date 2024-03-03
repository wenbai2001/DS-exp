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
} VertexType; //�������Ͷ���
typedef struct ArcNode {             //�������Ͷ���
        int adjvex;              	    //����λ�ñ�� 
     struct ArcNode  *nextarc;       //��һ������ָ��
} ArcNode;
typedef struct VNode{                //ͷ��㼰���������Ͷ���
        VertexType data;           	   //������Ϣ
     ArcNode *firstarc;                  //ָ���һ����
    } VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  		   //�ڽӱ�����Ͷ���
    AdjList vertices;                      //ͷ�������
    int vexnum,arcnum;               //������������
    GraphKind  kind;                   //ͼ������
   } ALGraph;
typedef struct{  	  	  //���Ա�ļ������Ͷ���
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

int visited[20];//��Ƿ������飬�Ѿ�����Ϊ1��Ϊ����Ϊ0��
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

int inqueue[20];//����Ƿ��Ѿ��ڷ��ʶ��У����Ѿ�����
typedef struct QUEUE {
     int elem[MAXLENGTH];
     int front,length;
     } QUEUE;

void iniQueue(QUEUE &Q)
//�ú���ʵ�ֳ�ʼ��Q
{
/***************begin***************/
    Q.front=0;
    Q.length=0;

/*************** end ***************/
}

int enQueue(QUEUE &Q,int e)
//��Ԫ��e���Q���ɹ���ջ����1�����򷵻�0
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
//��Q����Ԫ�س��ӣ���ֵ��e���ɹ����ӷ���1�����򷵻�0
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
	int i,k,v,w,u;//��� 
	char listname[30];
	char x[] = "C:\\Users\\86153\\�߲���\\a.txt";
	while(operate1){
	system("cls");
	printf("\n\n");
	printf("                       ��ӭ������ͼ����˵� \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  ��������ͼ    2.  ɾ������ͼ\n");
	printf("                       3.  ��������ͼ    4.  ѡ������ͼ\n");
	printf("                       0.  �˳�\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~4]:\n");
	scanf("%d", &operate1);
	switch (operate1)
	{
	case 1:
	//AddList
		printf("\n������Ҫ���ӵ�����ͼ����\n");
		scanf("%s", listname);
		AddList(Lists,listname);
		printf("\n��������ͼ�ɹ�\n");
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;		 
		

	case 2:
	//RemoveList
		printf("\n������Ҫɾ��������ͼ����\n");
		scanf("%s", listname);
		if(RemoveList(Lists,listname)==OK)
			printf("\nɾ������ͼ�ɹ�\n");
		else
			printf("\nɾ������ͼʧ��\n");
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;	
		
	case 3:
	//locateList
		printf("\n������Ҫ���ҵ�����ͼ����\n");
		scanf("%s", listname);
		if(LocateList(Lists,listname)!=0)
			printf("\n���ҵ�����ͼ���Ϊ%d\n",LocateList(Lists,listname));
		else
			printf("\n��������ͼʧ��\n");
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;	
	
	case 4:
	printf("ѡ����Ҫ����������ͼ���\n");
	scanf("%d",&k);
	G=Lists.elem[k-1].G;
	operate2=1;
	while (operate2) {
	system("cls");
	printf("\n\n");
	printf("                       Welcome to the ����ͼ���� menu \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  ��������ͼ        2.  ��������ͼ\n");
	printf("                       3.  ���Ҷ���          4.  ���㸳ֵ\n");
	printf("                       5.  ��õ�һ�ڽӵ�    6.  �����һ�ڽӵ�\n");	
	printf("                       7.  ���붥��          8.  ɾ������\n");
	printf("                       9.  ���뻡            10. ɾ����\n");
	printf("                       11. ���������������  12. ���������������\n");
	printf("                       13. �ļ��洢          14. �ļ���ȡ\n");
	printf("                       15. ��ӡͼ            0.  �˳�\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~14]:\n");
	scanf("%d", &operate2);
	switch (operate2)
	{
	case 1:
	//CreateGraph 
		i=0;
		printf("��������ͼ�Ľ������\n");
		do 
		{
    		scanf("%d%s",&V[i].key,V[i].others);
		} while(V[i++].key!=-1);
		i=0;
		printf("���뻡�Ĺ�ϵ\n");
		do 
		{
    		scanf("%d%d",&VR[i][0],&VR[i][1]);
   		} while(VR[i++][0]!=-1);
		if (CreateGraph(G,V,VR)==ERROR) printf("�������ݴ��޷�����");
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
		printf("�����ɹ���"); 
     	getchar();
		printf("\n���س�������\n");
		getchar();
     	break;
	
	case 2:
	//DestroyGraph
        if (DestroyGraph(G)==OK) 
   			printf("��������ͼ�ɹ�\n");
        else printf("��������ͼʧ��\n");
    	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 3:
	//LocateVex
    		printf("������Ҫ���ҵĽ��\n");
			scanf("%d",&u);   
			i=LocateVex(G,u);
			if (i!=-1)
				printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else
				printf("����ʧ��\n");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 4:
	//PutVex
		printf("������Ҫ��ֵ�Ľ��u\n"); 
		scanf("%d",&u);   
		printf("�����µĽ��value�����ݽṹ\n"); 
		scanf("%d%s",&value.key,value.others);
		i=PutVex(G,u,value);
		if (i==OK)
		{
			for(i=0;i<G.vexnum;i++)
     		printf(" %d %s\n",G.vertices[i].data.key,G.vertices[i].data.others);
     		printf("��ֵ�ɹ���");
		}
		else
			printf("��ֵ����ʧ��");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 5:
	//FirstAdjVex
		printf("����Ҫ���ҵĽ��ؼ���\n");
 		scanf("%d",&u);   
		i=FirstAdjVex(G,u);
		if (i!=-1)
			printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
		else
			printf("����ʧ��\n");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 6:
	//NextAdjVex
		printf("������v�������ڽӵ�w\n"); 
		scanf("%d%d",&v,&w);   
		i=NextAdjVex(G,v,w);
		if (i!=-1)
			printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
		else
			printf("����һ�ڽӶ���\n");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 7:
	//InsertVex
		printf("������Ҫ������¶���\n");
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
		else printf("�������ʧ��\n");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 8:
	//DeleteVex
		printf("������Ҫɾ���Ķ���\n");
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
		else printf("ɾ���������ʧ��\n");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 9:
	//InsertArc
		printf("������Ҫ����Ļ�\n");
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
		else printf("���뻡����ʧ��\n");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 10:
	//DeleteArc
		printf("������Ҫɾ���Ļ�\n");
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
		else printf("ɾ��������ʧ��");
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 11:
	//DFSTraverse
		DFSTraverse(G,visit);
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 12:
	//BFSTraverse
		BFSTraverse(G,visit);
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
    	
	case 13:
	//SaveGraph
	    if (k = SaveGraph(G, x) == OK)
        printf("�ļ�����ɹ�\n");
    	else printf("�ļ�����ʧ��\n");
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;
		
	case 14:
	//LoadGraph
	    if (i = LoadGraph(G, x) == OK)
        printf("�ļ�����ɹ�\n");
        else printf("�ļ�����ʧ��\n");
		getchar();
		printf("\n���س�������\n");
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
		printf("\n���س�������\n");
		getchar();
		break;
}
}
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;
		
	
}
}
	return 0;
}



status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    // �������ﲹ����룬��ɱ�������
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
    //�жϺϷ�
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
/*��������ͼG*/
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int e;//������������
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
            for(i=Q.front;i-Q.front+1<=Q.length;i++)//һ����ͨ��ͼ�еĽ��δȫ�������
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
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    FILE* fout = fopen(FileName, "wt");
    if (fout == NULL) exit(-1);
    int i;
    ArcNode* temp;
    for (i = 0;i < G.vexnum;i++)
    {
        fprintf(fout, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);//������ڵ�����
        temp = G.vertices[i].firstarc;
        while (temp != NULL)
        {
            fprintf(fout, "%d ", temp->adjvex);
            temp = temp->nextarc;
        }
        fprintf(fout, "-1 ");//��ʾһ���ڵ�������ˣ������ڽӱ�
    }
    //��β����-2��ʾ�����������
    fclose(fout);
    return OK;
    /********** End 1 **********/
}


status LoadGraph(ALGraph& G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    int vexn = 0, arcn = 0;
    ArcNode* te, * pre;
    FILE* fin = fopen(FileName, "rt");
    if (fin == NULL) exit(-1);
    int tkey, t;
    char tothers[20];//��ʱ���������
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
// ֻ��Ҫ��Lists������һ������ΪListName������ͼ
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
// Lists��ɾ��һ������ΪListName������ͼ 
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
// ��Lists�в���һ������ΪListName������ͼ���ɹ������߼���ţ����򷵻�0
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

