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
 
typedef struct{  //���Ա�ļ������Ͷ���
     struct { char name[30];
               SqList L;    
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 
LISTS Lists;      //���Ա��ϵĶ���Lists

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
            L.elem[0]=1;
            L.elem[L.listsize-1]=2;
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
        if (L.elem==NULL) 
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
		if (L.elem==NULL)
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
		if (L.elem==NULL)
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

status InitList(SqList& L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length=0;
    L.listsize=100;
    return 1;
}


status DestroyList(SqList& L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if(L.elem==NULL) return INFEASIBLE;
    else{
    free(L.elem);
    L.elem=NULL;
    return OK;
    }
}


status ClearList(SqList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem==NULL) return INFEASIBLE;
    if(L.length==0) return TRUE;
    else return FALSE;
}


status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if(L.elem==NULL) return INFEASIBLE;
    else return L.length;
}


status GetElem(SqList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų�����OK�����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
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


