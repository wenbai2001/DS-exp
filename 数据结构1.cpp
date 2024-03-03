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
 
typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               SqList L;    
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 
LISTS Lists;      //线性表集合的定义Lists

status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);

ElemType e;

int main(void)
{
	SqList L;
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
            L.elem[0]=1;
            L.elem[L.listsize-1]=2;
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
		if (L.elem==NULL)
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
		if (L.elem==NULL)
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

status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length=0;
    L.listsize=100;
    return 1;
}


status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
    free(L.elem);
    L.elem=NULL;
    return OK;
    }
}


status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        int i;
        for(i=0;i<=L.length-1;i++){
            L.elem[i]=NULL;
        }
        L.length=0;
        return OK;
    }
}


status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    if(L.length==0) return TRUE;
    else return FALSE;
}


status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else return L.length;
}


status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        if((i<1)||(i>L.length)) return ERROR;
        else{
            e=L.elem[i-1];
            return OK;
        }
    }
}


status LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        int i;
        for(i=0;i<=L.length-1;i++){
            if(L.elem[i]==e) return i+1;
        }
        return ERROR;
    }
}


status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        int i;
        for(i=0;i<=L.length-1;i++){
            if((L.elem[i]==e)&&(i!=0)){
                pre=L.elem[i-1];
                return OK;
            }
        }
        return ERROR;
    }
}


status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        int i;
        for(i=0;i<=L.length-1;i++){
            if((L.elem[i]==e)&&(i!=L.length-1)){
                next=L.elem[i+1];
                return OK;
            }
        }
        return ERROR;
    }
}


status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        if((i>L.length+1)||(i<=0)) return ERROR;
        else{
            int k;
            if(L.length>=L.listsize){
                ElemType * newbase=(ElemType * )realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
                L.elem=newbase;
                L.listsize+=LISTINCREMENT;
            }
                for(k=L.length;k>=i;k--)
                    L.elem[k]=L.elem[k-1];
                L.elem[i-1]=e;
                L.length++;
                return OK;
        }
    }
}


status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        if((i<1)||(i>L.length)) return ERROR;
        else{
            int k;
            e=L.elem[i-1];
            for(k=i-1;k<=L.length-2;k++)
                L.elem[k]=L.elem[k+1];
            L.length--;
            return OK;
        }
    }
}


status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
        int i;
        for(i=0;i<=L.length-1;i++){
        if(i==L.length-1)  printf("%d",L.elem[i]);
        else printf("%d ",L.elem[i]);
        }
        return OK;
    }
}


status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	FILE *fp;
	if ((fp = fopen(FileName, "wb")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);
	fclose(fp);
	return OK;
    

    /********** End **********/
}


status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/

	L.length = 0;
	FILE *fp;
	if ((fp = fopen(FileName, "rb")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
	while (fread(&L.elem[L.length], sizeof(ElemType), 1, fp))
	L.length++;
	fclose(fp);
	return OK;
    /********** End **********/
}



status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int j=0;
    for(j=0;ListName[j]!='\0';j++){
        Lists.elem[Lists.length].name[j]=ListName[j];
    }
    Lists.elem[Lists.length].name[j]='\0';
     SqList L;
    //ElemType *L.elem=(ElemType * )malloc(sizeof(ElemType)*10);
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    L.length=0;
    L.listsize=100;
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


