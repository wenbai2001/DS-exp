#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    char others[20];
} TElemType; //二叉树结点类型定义
typedef struct
{
    int pos;
    TElemType data;
} DEF;
typedef struct BiTNode
{ //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct Forest
{ //森林定义
    BiTree tree;
    char name[30];
    struct Forest *next;
} Forest, *Fp;
void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}
BiTree case1(BiTree &T, bool flag = true);
int *getkeys(BiTree &T, int *keys = NULL) //获取所有key值
{
    if (T)
    {
        if (!keys)
            keys = new int[1000]{0};
        keys[T->data.key]++;
        getkeys(T->lchild, keys);
        getkeys(T->rchild, keys);
    }
    return keys;
}
status checkKey(TElemType *keys) //检查序列中有无重复key值
{
    int marks[10000]{0};
    for (int i = 0; i < 100; i++, keys++)
    {
        if (keys->key)
        {
            if (keys->key == -1)
                return i;
            if (++marks[keys->key - 1] == 2)
                return ERROR;
        }
    }
    return OK;
}
BiTNode *LocateParent(BiTree T, KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode *temp = (BiTNode *)malloc(sizeof(BiTNode));
    if (T && (T->lchild || T->rchild))
    {
        if (T->lchild && T->lchild->data.key == e || T->rchild && T->rchild->data.key == e)
            return T;
        if ((temp = LocateParent(T->lchild, e)))
            return temp;
        else
            return LocateParent(T->rchild, e);
    }
    return NULL;
    /********** End **********/
}
status CreateBiTree(BiTree &T, DEF definition[])
{
    static int m=0;
    if(m==0)
    {
        m++;
    int k;
    int b[200];
    for(k=0;k<=99;k++) b[k]=0;
    k=0;
    while(definition[k].pos!=0)
    {
        if(definition[k].data.key!=0)
        {
            b[definition[k].data.key]+=1;
        }
        k++;
    }
    for(k=0;k<=99;k++)
    {
        if(b[k]>=2) 
        {
            return ERROR;
        }
    }
    }
    int i = 0, j;
    static BiTNode *p[100];
    while (j = definition[i].pos)
    {	
        p[j] = (BiTNode *)malloc(sizeof(BiTNode));
        p[j]->data = definition[i].data;
        p[j]->lchild = NULL;
        p[j]->rchild = NULL;
        if (j != 1)
            if (j % 2)
                p[j / 2]->rchild = p[j];
            else
                p[j / 2]->lchild = p[j];
        i++;
    }
    T = p[1];
    return OK;
}
status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T->lchild)
        ClearBiTree(T->lchild);
    if (T->rchild)
        ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
    /********** End **********/
}
int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    static int i = 0, count = 0;
    if (T)
    {
        // 请在这里补充代码，完成本关任务
        /********** Begin *********/
        i++;
        if (i > count)
            count = i;
        BiTreeDepth(T->lchild);
        BiTreeDepth(T->rchild);
        i--;
    }
    else
    {
        return INFEASIBLE;
    }
    return count;
}
BiTNode *LocateNode(BiTree T, KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode *temp = (BiTNode *)malloc(sizeof(BiTNode));
    if (T)
    {
        if (T->data.key == e)
            return T;
        if ((temp = LocateNode(T->lchild, e)))
            return temp;
        else
            return LocateNode(T->rchild, e);
    }
    return NULL;

    /********** End **********/
}
status Assign(BiTree &T, KeyType e, TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree Node = LocateNode(T, e);
    int *keys = getkeys(T);
    if (!Node)
        return INFEASIBLE;
    if (Node->data.key != value.key && keys[value.key])
        return ERROR;
    else
        Node->data.key = value.key;
    strcpy(Node->data.others, value.others);
    return OK;
}
BiTNode *GetSibling(BiTree T, KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree parent = LocateParent(T, e);
    if (parent && parent->lchild && parent->rchild)
    {
        if (parent->lchild->data.key == e)
            return parent->rchild;
        else
            return parent->lchild;
    }
    return NULL;
    /********** End **********/
}
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int *keys = getkeys(T);
    if (keys[c.key])
        return ERROR;
    if (LR == -1)
    {
        BiTree Node = (BiTree)malloc(sizeof(BiTNode));
        Node->data = c;
        Node->rchild = T;
        Node->lchild = NULL;
        T = Node;
        return OK;	
    }
    BiTree root = (BiTree)malloc(sizeof(BiTNode)), temp = (BiTree)malloc(sizeof(BiTNode));
    if (root = LocateNode(T, e))
    {
        if (LR == 0)
        {
            temp = root->lchild;
            BiTree Node = (BiTree)malloc(sizeof(BiTNode));
            Node->data = c;
            Node->rchild = temp;
            Node->lchild = NULL;
            root->lchild = Node;
        }
        else
        {
            temp = root->rchild;
            BiTree Node = (BiTree)malloc(sizeof(BiTNode));
            Node->data = c;
            Node->rchild = temp;
            Node->lchild = NULL;
            root->rchild = Node;
        }
        return OK;
    }
    return ERROR;
    /********** End **********/
}
status DeleteNode(BiTree &T, KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree parent = LocateParent(T, e);
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    BiTree temp = (BiTree)malloc(sizeof(BiTNode));
    int flag = -1;
    if (!parent)
        if (T->data.key == e)
        {
            root = T;
            flag = 1;
        }
        else
            return ERROR;
    else if (parent->rchild->data.key == e)
    {
        root = parent->rchild;
        flag = 2;
    }
    else
    {
        root = parent->lchild;
        flag = 3;
    }
    if (root->lchild)
    {
        BiTree maxrchild = root->lchild;
        while (maxrchild->rchild)
            maxrchild = maxrchild->rchild;
        maxrchild->rchild = root->rchild;
        temp = root->lchild;
    }
    else if (root->rchild)
        temp = root->rchild;
    else
        temp = NULL;
    free(root);
    if (flag == 1)
        T = temp;
    else if (flag == 2)
        parent->rchild = temp;
    else
        parent->lchild = temp;
    return OK;
}
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T)
    {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
    /********** End **********/
}
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T)
    {
        InOrderTraverse(T->lchild, visit);
        visit(T);
        InOrderTraverse(T->rchild, visit);
    }
    return OK;

    /********** End **********/
}
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T)
    {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;
    /********** End **********/
}
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree s[100];
    for(int x=0;x<=99;x++) s[x]=NULL;
    if(T) 
    {
        s[0]=T;
    }

    BiTree p;
    int i=0,k=1,m=0;
    while(k)
    {
        p=s[m];
        m++;
        visit(p);
        k--;
        if(p->lchild)
        {
            i++;
            k++;
            s[i]=p->lchild;	
        }
        if(p->rchild)
        {
            i++;
            k++;
            s[i]=p->rchild;
        }
    }
    return OK;
    /********** End **********/
}
status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (!T)
        return ERROR;
    BiTree *list = (BiTree *)malloc(sizeof(BiTree) * 1000);
    list[0] = T;
    BiTree Tlist = (BiTree)malloc(sizeof(BiTNode) * 1000);
    Tlist[0] = *T;
    int head = -1, tail = 1;
    FILE *fp;
    if (!(fp = fopen(FileName, "w+b")))
        return ERROR;
    while (++head < tail)
    {
        if (list[head])
        {
            list[tail++] = list[head]->lchild;
            list[tail++] = list[head]->rchild;
            Tlist[head] = *(list[head]);
        }
    }
    fwrite(&tail, sizeof(int), 1, fp);
    fwrite(list, sizeof(BiTree), tail, fp);
    fwrite(Tlist, sizeof(BiTNode), tail, fp);
    fclose(fp);
    return OK;
    /********** End 1 **********/
}
status LoadBiTree(BiTree &T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (T)
        return ERROR;
    BiTree list[1000];
    int head = -1, tail = 1;
    FILE *fp;
    if (!(fp = fopen(FileName, "r+b")))
        return ERROR;
    fread(&tail, sizeof(int), 1, fp);
    fread(list, sizeof(BiTree), tail, fp);
    while (head++ < tail - 1)
    {
        BiTree tp = (BiTree)malloc(sizeof(BiTNode));
        fread(tp, sizeof(BiTNode), 1, fp);
        if (list[head])
        {
            list[head] = tp;
        }
    }
    head = -1, tail = 1;
    while (head++ < tail - 1)
    {
        BiTree tp = (BiTree)malloc(sizeof(BiTNode) * 1);
        tp = list[head];
        if (!T)
            T = tp;
        if (tp)
        {
            tp->lchild = list[tail++];
            tp->rchild = list[tail++];
        }
    }
    fclose(fp);
    return OK;
    /********** End 2 **********/
}
Fp AddTree(Fp &F, char *name)
{
    strcpy(F->name, name);
    F->next = NULL;
    F->tree = NULL;
    case1(F->tree, false);
    return F;
}
Fp LocateTree(Fp F, char *name)
{
    while (F)
    {
        if (!strcmp(F->name, name))
            return F;
        F = F->next;
    }
    return NULL;
}
Fp deleteTree(Fp &F, char *name)
{
    Fp temp = F, pre; //从多表的首元结点开始查询
    while (temp)      //多表的当前结点存在继续遍历
    {
        if (!strcmp(temp->name, name)) //当前链表的名字与输入名字相同
        {
            pre->next = pre->next->next; //从多表链表中删除当前链表
            ClearBiTree(temp->tree);     //释放当前链表空间
            temp->tree = NULL;
            free(temp);
            return F;
        }
        pre = temp; //遍历到下一链表
        temp = temp->next;
    }
    return NULL;
}
status switchList(Fp F, char *name, BiTree &T)
{
    if (LocateTree(F, name))
    {
        T = LocateTree(F, name)->tree;
        return OK;
    }
    return ERROR;
}
void printTree(BiTree T, int h = 0) {
	int i;
	if (T != NULL) {
		printTree(T->rchild, h+1);
		for (i = 0; i < h; i++)
			putchar('\t');
		printf("%d %s", T->data.key, T->data.others);
		putchar('\n');
		printTree(T->lchild, h+1);
	}
}

BiTree case1(BiTree &T, bool flag)
{
    if (T)
        printf("二叉树存在");
    else
    {
        printf("请输入新的pos值, key值和others值\n");
        DEF definition[100];
        int i = 0;
        do
        {
            scanf("%d%d%s", &definition[i].pos, &definition[i].data.key, definition[i].data.others);
        } while (definition[i++].pos);
        if (CreateBiTree(T, definition))
            printf("二叉树创建成功\n");
        else
            printf("二叉树创建失败\n");
    }
    if(flag)
        printf("回车键回到主菜单\n");
    return T;
}
void case2(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
    {
        if (ClearBiTree(T))
            printf("二叉树清空成功\n");
        else
            printf("二叉树清空失败\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case3(BiTree &T)
{
    int depth = BiTreeDepth(T);
    if (depth)
        printf("二叉树的深度为%d\n", depth);
    else if (depth == 0)
        printf("二叉树深度为0\n");
    else
        printf("二叉树不存在\n");
    printf("输入回车键返回主菜单\n");
}
void case4(BiTree &T)
{
    int key;
    if (!T)
        printf("二叉树不存在\n");
    else
    {
        printf("请输入你想要查找的结点的key值:\n");
        scanf("%d", &key);
        BiTree Node = LocateNode(T, key);
        if (Node)
            printf("该key值对应的结点的内容为%s\n", Node->data.others);
        else
            printf("查找失败\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case5(BiTree &T)
{
    if (!T)
        printf("二叉树不存在");
    else
    {
        int key;
        TElemType def;
        printf("请输入你想要赋值的结点的key值:\n");
        scanf("%d", &key);
        printf("请输入新的key值和others值\n");
        scanf("%d %s", &def.key, def.others);
        int f = Assign(T, key, def);
        if (f == INFEASIBLE)
            printf("结点查找失败\n");
        else if (f)
            printf("结点赋值成功\n");
        else
            printf("二叉树中已有待赋值的key值\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case6(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
    {
        int key;
        printf("请输入结点的key值:\n");
        scanf("%d", &key);
        BiTree Node = GetSibling(T, key);
        if (!Node)
            printf("结点的兄弟结点不存在\n");
        else
        {
            printf("结点的兄弟结点的key值为%d,others值为%s", Node->data.key, Node->data.others);
        }
    }
    printf("输入回车键返回主菜单\n");
}
void case7(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
    {
        int key, LR;
        TElemType value;
        printf("请输入你想要插入的结点的父结点key值:\n");
        scanf("%d", &key);
        printf("插入位置为左叶子结点输入0，右叶子结点输入1\n");
        scanf("%d", &LR);
        printf("请输入你想要插入的结点的key值和others值:\n");
        scanf("%d %s", &value.key, value.others);
        int flag = InsertNode(T, key, LR, value);
        if (flag)
            printf("插入成功\n");
        else
            printf("插入失败\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case8(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
    {
        int key;
        printf("请输入你想要删除的结点的key值\n");
        scanf("%d", &key);
        int flag = DeleteNode(T, key);
        if (flag)
            printf("删除成功\n");
        else
            printf("结点不存在\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case9(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
        PreOrderTraverse(T, visit);
    printf("\n输入回车键返回主菜单\n");
}
void case10(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
        InOrderTraverse(T, visit);
    printf("\n输入回车键返回主菜单\n");
}
void case11(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
        PostOrderTraverse(T, visit);
    printf("\n输入回车键返回主菜单\n");
}
void case12(BiTree &T)
{
    if (!T)
        printf("二叉树不存在\n");
    else
        LevelOrderTraverse(T, visit);
    printf("\n输入回车键返回主菜单\n");
}
void save(BiTree &T)
{
    if (!T)
        printf("二叉树不存在");
    else
    {
        char filename[30];
        strcpy(filename, "./list.dat");
        int flag = SaveBiTree(T, filename);
        if (flag)
            printf("二叉树保存成功\n");
        else
            printf("二叉树保存失败\n");
    }
    printf("输入回车键返回主菜单\n");
}
void read(BiTree &T)
{
    if (T)
        printf("二叉树已存在");
    else
    {
        char filename[30];
        strcpy(filename, "./list.dat");
        int flag = LoadBiTree(T, filename);
        if (flag)
            printf("二叉树读取成功\n");
        else
            printf("二叉树读取失败\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case14(Fp &F)
{
    if(!F){
        F = (Fp)malloc(sizeof(Forest));
        F->next = NULL;
        F->tree = NULL;
    }
    Fp tf = F;
    while (tf->next)
    {
        tf = tf->next;
    }
    int count;
    printf("请输入想要种多少颗二叉树:\n");
    scanf("%d", &count);
    char s[30];
    while (count--)
    {
        tf->next = (Fp)malloc(sizeof(Forest));
        printf("请输入二叉树的名字:\n");
        scanf("%s", s);
        AddTree(tf->next, s);
        tf = tf->next;
    }
    tf = F;
    while (tf)
    {
        PreOrderTraverse(tf->tree, visit);
        tf = tf->next;
        printf("\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case15(Fp &F)
{
    if (!F)
        printf("森林不存在\n");
    else
    {
        char s[30];
        printf("请输入二叉树的名字\n");
        scanf("%s", s);
        if (LocateTree(F, s))
        {
            PreOrderTraverse(LocateTree(F, s)->tree, visit);
            printf("\n");
        }
        else
            printf("查找失败\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case16(Fp &F)
{
    Fp tf = F;
    if (!F)
        printf("森林不存在\n");
    else
    {
        char s[30];
        printf("请输入二叉树的名字\n");
        scanf("%s", s);
        if (deleteTree(F, s))
        {
            while (tf)
            {
                PreOrderTraverse(tf->tree, visit);
                tf = tf->next;
                printf("\n");
            }
        }
        else
            printf("查找失败\n");
    }
    printf("输入回车键返回主菜单\n");
}
void case17(Fp &F, BiTree &T)
{
    if (!F)
        printf("森林不存在\n");
    else
    {
        char name[30];
        printf("请输入你想要切换的表的名字\n");
        scanf("%s", name);
        if (switchList(F, name, T) == OK)
            printf("切换成功\n");
        else
            printf("切换失败，请检查你输入的名称\n");
    }
    printf("回车返回主菜单\n");
}
void case18(BiTree T){
    if (!T)
        printf("二叉树不存在");
    else{
        printTree(T);
    }
    printf("回车返回主菜单\n");
}
int main(void)
{
    BiTree T = NULL;
    Fp F = NULL;
    int op = 1;
    while (op)
    {
        system("cls");
        printf("\n\n");
	printf("                       Welcome to the sequential linear table menu \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("                       1.  创建二叉树    2.  清空二叉树\n");
	printf("                       3.  求二叉树深度  4.  查找结点\n");
	printf("                       5.  结点赋值      6.  获得兄弟结点\n");	
	printf("                       7.  插入结点      8.  删除结点\n");
	printf("                       9.  先序遍历      10. 中序遍历\n");
	printf("                       11. 后序遍历      12. 按层遍历\n");
	printf("                       13. 文件存储      14. 文件读取\n");
	printf("                       15. 添加树        16. 查找树\n");
	printf("                       17. 删除树        18. 选择树\n");
	printf("                       19.打印树         0.  结束       \n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("    请选择你的操作[0~19]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            case1(T);
            getchar();
            getchar();
            break;
        case 2:
            case2(T);
            getchar();
            getchar();
            break;
        case 3:
            case3(T);
            getchar();
            getchar();
            break;
        case 4:
            case4(T);
            getchar();
            getchar();
            break;
        case 5:
            case5(T);
            getchar();
            getchar();
            break;
        case 6:
            case6(T);
            getchar();
            getchar();
            break;
        case 7:
            case7(T);
            getchar();
            getchar();
            break;
        case 8:
            case8(T);
            getchar();
            getchar();
            break;
        case 9:
            case9(T);
            getchar();
            getchar();
            break;
        case 10:
            case10(T);
            getchar();
            getchar();
            break;
        case 11:
            case11(T);
            getchar();
            getchar();
            break;
        case 12:
            case12(T);
            getchar();
            getchar();
            break;
        case 13:
            save(T);
            getchar();
            getchar();
            break;
        case 14:
            read(T);
            getchar();
            getchar();
            break;
        case 15:
            case14(F);
            getchar();
            getchar();
            break;
        case 16:
            case15(F);
            getchar();
            getchar();
            break;
        case 17:
            case16(F);
            getchar();
            getchar();
            break;
        case 18:
            case17(F, T);
            getchar();
            getchar();
            break;
        case 19:
            case18(T);
            getchar();
            getchar();
            break;
        case 0:
            break;
        } //end of switch
    }     //end of while
    printf("欢迎下次再使用本系统！\n");
    return 1;
} //end of main()

