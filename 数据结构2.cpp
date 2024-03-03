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
typedef int ElemType; //����Ԫ�����Ͷ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct{  //˳���˳��ṹ���Ķ���
      ElemType * elem;
      int length;
      int listsize;
 }SqList;
 
typedef struct LNode
{				//����Ľṹ����
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;


typedef struct{  //���Ա�ļ������Ͷ���
     struct { char name[30];
               LinkList L;    
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 
LISTS Lists;      //���Ա��ϵĶ���Lists


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
	int i,pre,next,k;//��� 
	char listname[30];
	while(operate1){
	system("cls");
	printf("\n\n");
	printf("                       ��ӭ���������Ա����˵� \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  �������Ա�    2.  ɾ�����Ա�\n");
	printf("                       3.  �������Ա�    4.  ѡ����Ž������Ա����˵�\n");
	printf("                       0.  �˳�\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~4]:\n");
	scanf("%d", &operate1);
	switch (operate1)
	{
	case 1:
	//AddList
		printf("\n������Ҫ���ӵ����Ա�����\n");
		scanf("%s", listname);
		AddList(Lists,listname);
		printf("\n�������Ա�ɹ�\n");
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;		 
		

	case 2:
	//RemoveList
		printf("\n������Ҫɾ�������Ա�����\n");
		scanf("%s", listname);
		if(RemoveList(Lists,listname)==OK)
			printf("\nɾ�����Ա�ɹ�\n");
		else
			printf("\nɾ�����Ա�ʧ��\n");
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;	
		
	case 3:
	//locateList
		printf("\n������Ҫ���ҵ����Ա�����\n");
		scanf("%s", listname);
		if(LocateList(Lists,listname)!=0)
			printf("\n���ҵ����Ա����Ϊ%d\n",LocateList(Lists,listname));
		else
			printf("\n�������Ա�ʧ��\n");
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;	
	
	case 4:
	printf("ѡ����Ҫ���������Ա����\n");
	scanf("%d",&k);
	L=Lists.elem[k-1].L;
	operate2=1;
	while (operate2) {
	system("cls");
	printf("\n\n");
	printf("                       Welcome to the sequential linear table menu \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  �������Ա�    2.  �������Ա�\n");
	printf("                       3.  ɾ�����Ա�    4.  ���Ա��п�\n");
	printf("                       5.  ���Ա���    6.  ��ȡ�̶�ֵ\n");	
	printf("                       7.  ����Ԫ�غ�    8.  ��ȡԪ��ǰ��\n");
	printf("                       9.  ��ȡԪ�غ��  10. ����Ԫ��\n");
	printf("                       11. ɾ��Ԫ��      12. ��ʾԪ��\n");
	printf("                       13. �ļ��洢      14. �ļ���ȡ\n");
	printf("                        0.  �˳�\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf(" Please select your operation[0~14]:\n");
	scanf("%d", &operate2);
	switch (operate2)
	{
	case 1:
	//InitList
    	if (InitList(L)==OK) {
            printf("�������Ա�ɹ�");
        }
		else
     	{
     		printf("���������Ա�ʧ��");
     	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
     	break;
	
	case 2:
	//DestroyList
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	if (DestroyList(L)==OK) 
   				printf("�������Ա�ɹ�");
        	else printf("�������Ա�ʧ��");
    	}
    	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 3:
	//ClearList
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	if (ClearList(L)==OK) 
   				printf("������Ա�ɹ�");
        	else printf("������Ա�ʧ��");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 4:
	//ListEmpty
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	if (ListEmpty(L)==TRUE) 
   				printf("���Ա�Ϊ��");
        	else printf("���Ա�ǿ�");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 5:
	//listLenth
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	printf("�����Ա�ĳ���Ϊ%d",ListLength(L));
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 6:
	//GetElem
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	printf("������Ҫ��ѯ�����\n");
        	scanf("%d",&i); 
        	if(GetElem(L,i,e)==OK)    printf("��%d������ֵΪ%d",i,e);
        	else printf("��ѯʧ��");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 7:
	//LocateElem
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	printf("������Ҫ��ѯ��Ԫ��\n");
        	scanf("%d",&e); 
        	if(LocateElem(L,e)!=ERROR)    printf("Ԫ��%d�����Ϊ%d",e,LocateElem(L,e));
        	else printf("��ѯʧ��");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 8:
	//PriorElem
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	printf("������Ҫ��ѯ��Ԫ��\n");
        	scanf("%d",&e); 
        	if(PriorElem(L,e,pre)!=ERROR)    printf("Ԫ��%d��ǰ��Ϊ%d",e,pre);
        	else printf("����ǰ��ʧ��");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 9:
	//NextElem
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	printf("������Ҫ��ѯ��Ԫ��\n");
        	scanf("%d",&e); 
        	if(NextElem(L,e,next)!=ERROR)    printf("Ԫ��%d�ĺ��Ϊ%d",e,next);
        	else printf("���Һ��ʧ��");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 10:
	//ListInsert
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	printf("������Ҫ�����Ԫ��\n");
        	scanf("%d",&e); 
        	printf("������Ҫ�����λ��\n");
        	scanf("%d",&i); 
        	if(ListInsert(L,i,e)!=ERROR)    
			{
				printf("����ɹ�����ʾ���Ա���Ԫ�أ�\n");
				for (int k = 1; k <= ListLength(L); k++)
				{
					GetElem(L, k, e);
					printf("%d ", e);
				}
			}
        	else printf("����ʧ��");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 11:
	//ListDelete
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	printf("������Ҫɾ��Ԫ�ص�λ��\n");
        	scanf("%d",&i); 
        	if(ListDelete(L,i,e)!=ERROR)    
			{
				printf("ɾ���ɹ�����ʾ���Ա���Ԫ�أ�\n");
				for (int k = 1; k <= ListLength(L); k++)
				{
					GetElem(L, k, e);
					printf("%d ", e);
				}
			}
        	else printf("ɾ��ʧ��");
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
	
	case 12:
	//ListTraverse
        if (L==NULL) 
			printf("���Ա�����");    
		else
    	{ 
        	ListTraverse(L); 
    	}
     	getchar();
		printf("\n���س�������\n");
		getchar();
    	break;
    	
	case 13:
	//SaveList
		if (L==NULL)
			printf("���Ա�����");
		else
		{
			printf("\n�����뱣�浽���ļ�����\n");
			char filename[30];
			scanf("%s", filename);
			if (SaveList(L, filename)!=ERROR)
				printf("\n����ɹ�\n");
			else
				printf("\n�������\n");
		}
		getchar();
		printf("\n���س�������\n");
		getchar();
		break;
		
	case 14:
	//LoadList 
		if (L==NULL)
			printf("���Ա�����");
		else
		{
			printf("\n������Ҫ���ص��ļ�����\n");
			char filename[30];
			scanf("%s", filename);
			if (LoadList(L, filename)!=ERROR)
				printf("\n�ļ���ȡ�ɹ�\n");
			else
				printf("\n�ļ���ȡ����\n");
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

status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
        else printf("�����Ա�");
    }

    /********** End **********/
}


status SaveList(LinkList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
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
// Lists��ɾ��һ������ΪListName�����Ա�
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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

