#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //数据元素类型定义
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct{  //顺序表（顺序结构）的定义
      ElemType * elem;
      int length;
      int listsize;
 }SqList;
 
typedef struct LNode
{				//链表的结构定义
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;


typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               LinkList L;    
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 
LISTS Lists;      //线性表集合的定义Lists


status InitList(LinkList &L);
status DestroyList(LinkList& L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);

ElemType e;

int main(void)
{
	LinkList L;
	int operate1=1; 
	int operate2 = 1; 
	int i,pre,next,k;//序号 
	char listname[30];
	while(operate1){
	system("cls");
	printf("\n\n");
	printf("                       欢迎来到多线性表管理菜单 \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  创建线性表    2.  删除线性表\n");
	printf("                       3.  查找线性表    4.  选择序号进入线性表管理菜单\n");
	printf("                       0.  退出\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~4]:\n");
	scanf("%d", &operate1);
	switch (operate1)
	{
	case 1:
	//AddList
		printf("\n请输入要增加的线性表名称\n");
		scanf("%s", listname);
		AddList(Lists,listname);
		printf("\n增加线性表成功\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;		 
		

	case 2:
	//RemoveList
		printf("\n请输入要删除的线性表名称\n");
		scanf("%s", listname);
		if(RemoveList(Lists,listname)==OK)
			printf("\n删除线性表成功\n");
		else
			printf("\n删除线性表失败\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;	
		
	case 3:
	//locateList
		printf("\n请输入要查找的线性表名称\n");
		scanf("%s", listname);
		if(LocateList(Lists,listname)!=0)
			printf("\n查找的线性表序号为%d\n",LocateList(Lists,listname));
		else
			printf("\n查找线性表失败\n");
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;	
	
	case 4:
	printf("选择需要操作的线性表序号\n");
	scanf("%d",&k);
	L=Lists.elem[k-1].L;
	operate2=1;
	while (operate2) {
	system("cls");
	printf("\n\n");
	printf("                       Welcome to the sequential linear table menu \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  创建线性表    2.  销毁线性表\n");
	printf("                       3.  删除线性表    4.  线性表判空\n");
	printf("                       5.  线性表求长    6.  获取固定值\n");	
	printf("                       7.  查找元素号    8.  获取元素前驱\n");
	printf("                       9.  获取元素后继  10. 插入元素\n");
	printf("                       11. 删除元素      12. 显示元素\n");
	printf("                       13. 文件存储      14. 文件读取\n");
	printf("                        0.  退出\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~14]:\n");
	scanf("%d", &operate2);
	switch (operate2)
	{
	case 1:
	//InitList
    	if (InitList(L)==OK) {
            printf("创建线性表成功");
        }
		else
     	{
     		printf("创建新线性表失败");
     	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
     	break;
	
	case 2:
	//DestroyList
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	if (DestroyList(L)==OK) 
   				printf("销毁线性表成功");
        	else printf("销毁线性表失败");
    	}
    	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 3:
	//ClearList
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	if (ClearList(L)==OK) 
   				printf("清空线性表成功");
        	else printf("清空线性表失败");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 4:
	//ListEmpty
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	if (ListEmpty(L)==TRUE) 
   				printf("线性表为空");
        	else printf("线性表非空");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 5:
	//listLenth
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	printf("该线性表的长度为%d",ListLength(L));
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 6:
	//GetElem
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	printf("输入需要查询的序号\n");
        	scanf("%d",&i); 
        	if(GetElem(L,i,e)==OK)    printf("第%d个数的值为%d",i,e);
        	else printf("查询失败");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 7:
	//LocateElem
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	printf("输入需要查询的元素\n");
        	scanf("%d",&e); 
        	if(LocateElem(L,e)!=ERROR)    printf("元素%d的序号为%d",e,LocateElem(L,e));
        	else printf("查询失败");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 8:
	//PriorElem
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	printf("输入需要查询的元素\n");
        	scanf("%d",&e); 
        	if(PriorElem(L,e,pre)!=ERROR)    printf("元素%d的前驱为%d",e,pre);
        	else printf("查找前驱失败");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 9:
	//NextElem
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	printf("输入需要查询的元素\n");
        	scanf("%d",&e); 
        	if(NextElem(L,e,next)!=ERROR)    printf("元素%d的后继为%d",e,next);
        	else printf("查找后继失败");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 10:
	//ListInsert
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	printf("输入需要插入的元素\n");
        	scanf("%d",&e); 
        	printf("输入需要插入的位置\n");
        	scanf("%d",&i); 
        	if(ListInsert(L,i,e)!=ERROR)    
			{
				printf("插入成功，显示线性表中元素：\n");
				for (int k = 1; k <= ListLength(L); k++)
				{
					GetElem(L, k, e);
					printf("%d ", e);
				}
			}
        	else printf("插入失败");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 11:
	//ListDelete
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	printf("输入需要删除元素的位置\n");
        	scanf("%d",&i); 
        	if(ListDelete(L,i,e)!=ERROR)    
			{
				printf("删除成功，显示线性表中元素：\n");
				for (int k = 1; k <= ListLength(L); k++)
				{
					GetElem(L, k, e);
					printf("%d ", e);
				}
			}
        	else printf("删除失败");
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
	
	case 12:
	//ListTraverse
        if (L==NULL) 
			printf("线性表不存在");    
		else
    	{ 
        	ListTraverse(L); 
    	}
     	getchar();
		printf("\n按回车键继续\n");
		getchar();
    	break;
    	
	case 13:
	//SaveList
		if (L==NULL)
			printf("线性表不存在");
		else
		{
			printf("\n请输入保存到的文件名称\n");
			char filename[30];
			scanf("%s", filename);
			if (SaveList(L, filename)!=ERROR)
				printf("\n保存成功\n");
			else
				printf("\n保存出错\n");
		}
		getchar();
		printf("\n按回车键继续\n");
		getchar();
		break;
		
	case 14:
	//LoadList 
		if (L==NULL)
			printf("线性表不存在");
		else
		{
			printf("\n请输入要加载的文件名称\n");
			char filename[30];
			scanf("%s", filename);
			if (LoadList(L, filename)!=ERROR)
				printf("\n文件读取成功\n");
			else
				printf("\n文件读取错误\n");
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

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L!=NULL) return INFEASIBLE;
    else
    {
        L=(LinkList)malloc(sizeof(LNode));
        L->next=NULL;
        return OK;
    }

    /********** End **********/
}


status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else 
    {
        LinkList p,q;
        p=L;
        while(p!=NULL)
        {
            q=p->next;
            free(p);
            p=q;
        }
        L=NULL;
        return OK;
    }

    /********** End **********/
}



status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else 
    {
        LinkList p,q;
        p=L->next;
        while(p!=NULL)
        {
            q=p->next;
            free(p);
            p=q;
        }
        L->next=NULL;
        return OK;
    }

    /********** End **********/
}


status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else
    {
        if(L->next) return FALSE;
        else return TRUE;
    }

    /********** End **********/
}


int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else 
    {
        LinkList p;
        int i=0;
        p=L->next;
        while(p)
        {
            p=p->next;
            i++;
        }
        return i;
    }

    /********** End **********/
}



status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else if(i<1) return ERROR;
    else
    {
        LinkList p;
        p=L;
        for(int k=0;k<=i-1;k++) 
        {
            p=p->next;
            if(p==NULL) return ERROR;
        }
        if(p->data!=NULL)
        {
            e=p->data;
            return OK;
        }
        else return ERROR;
    }

    /********** End **********/
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else
    {
        LinkList p;
        p=L;
        int i=0;
        while((p!=NULL)&&(p->data!=e))
        {
            p=p->next;
            i++;
        }
        if(p)
        {
            return i;
        }
        else return ERROR;
    }

    /********** End **********/
}


status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else
    {
        LinkList p,q;
        p=L;
        int i=0;
        while((p!=NULL)&&(p->data!=e))
        {
            q=p;
            p=p->next;
            i++;
        }
        if((p)&&(q!=L))
        {
            pre=q->data;
            return OK;
        }
        else return ERROR;
    }


    /********** End **********/
}


status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else
    {
        LinkList p;
        p=L;
        int i=0;
        while((p!=NULL)&&(p->data!=e))
        {
            p=p->next;
            i++;
        }
        if((p)&&(p->next!=NULL))
        {
            next=p->next->data;
            return OK;
        }
        else return ERROR;
    }


    /********** End **********/
}


status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else if(i<1) return ERROR;
    else
    {
        LinkList p,q,l;
        p=L;
        for(int k=0;k<=i-1;k++) 
        {
            q=p;
            if(p==NULL) return ERROR;
            p=p->next;
        }
        l=(LinkList)malloc(sizeof(LNode));
        l->next=q->next;
        q->next=l;
        l->data=e;
        return OK;
    }

    /********** End **********/
}



status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else if(i<1) return ERROR;
    else
    {
        LinkList p,q,l;
        p=L;
        for(int k=0;k<=i-1;k++) 
        {
            q=p;
            p=p->next;
            if(p==NULL) return ERROR;
        }
        e=p->data;
        q->next=p->next;
        p->next=NULL;
        free(p);
        return OK;
    }
    /********** End **********/
}



status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else
    {
        LinkList p,q,l;
        p=L->next;
        if(p)
        {
            printf("%d",p->data);
            p=p->next;
            while(p) 
            {
                printf(" %d",p->data);
                p=p->next;
            }
            return OK;
        }
        else printf("空线性表");
    }

    /********** End **********/
}


status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L==NULL) return INFEASIBLE;
    else {
        LinkList p;
        p=L->next;
        FILE* fp;
        fp = fopen(FileName, "wb");
        if (!fp) exit(-1);
        while(p)
        {
            fwrite(p, 2*sizeof(LinkList), 1, fp);
            p=p->next;
        }
        fclose(fp);
        return OK;
    }

    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
	L->data = 0;
	LinkList p = L;
	FILE *fp;
	if ((fp = fopen(FileName, "rb")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}	
	LNode temp;

	while (fread(&temp, 2*sizeof(LinkList), 1, fp))
	{
		p->next = (LinkList)malloc(2 * sizeof(LinkList));
		p = p->next;
		*p = temp;
		L->data++;
	}
		p->next = NULL;
		fclose(fp);
		return OK;


    /********** End 2 **********/
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int j=0;
    for(j=0;ListName[j]!='\0';j++){
        Lists.elem[Lists.length].name[j]=ListName[j];
    }
    Lists.elem[Lists.length].name[j]='\0';
    LinkList L;
    //ElemType *L.elem=(ElemType * )malloc(sizeof(ElemType)*10);
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    Lists.elem[Lists.length].L=L;
    Lists.length+=1;
}


status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
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
            Lists.elem[m].L=Lists.elem[m+1].L;
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
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
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

