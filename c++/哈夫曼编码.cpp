#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIPUT 1024
#define ALPHA_SIZE 26

typedef struct TNODE{
    int times;
    char c;
    int flag;
    struct TNODE *parent;
    struct TNODE *left;
    struct TNODE *right;
}tnode_t;

/*用于选择两个最小的次数的下标，两个下标不能相等*/
void ChooseTwo(tnode_t *array[],int size,int *mmax,int *mmin)
{
    int i;
    int tpm,tpi;
    int iax,iin;
    if(size<=1) return ;
    if(array[1]->times > array[0]->times)
    {
        tpm=array[1]->times;
        tpi=array[0]->times;
        iax=1;
        iin=0;
    }
    else
    {
        tpm=array[0]->times;
        tpi=array[1]->times;
        iax=0;
        iin=1;
    }
    for(i=2;i<size;i++)
    {
        if(array[i]->times < tpi)
        {
            tpm = tpi;
            iax=iin;
            tpi = array[i]->times;
            iin=i;
        }
        else
        {
            if(array[i]->times < tpm)
            {
                tpm = array[i]->times;
                iax=i;
            }
        }
    }
    *mmax=iax;
    *mmin=iin;
}
/*判断c是否已经存在，如果存在返回下标，如果不存在返回-1*/
int ForSearch(tnode_t *array[],int size,char c)
{
    int i;
    if(size<=0) return -1;
    else
    {
        for(i=0;i<size;i++)
        {
            if(array[i]->c == c)
            {
                return i;
            }
        }
        return -1;
    }
}
/*哈夫曼编码，对含父节点的哈夫曼树的递归调用寻找*/
void HallfCode(tnode_t *root)
{
    tnode_t *tp;
    int a[MAXIPUT];
    int idx=0;
    if(root==NULL) return ;
    if(root->left==NULL && root->right==NULL)
    {
        tp=root;
        printf("%c : ",root->c);
        while(tp->flag!=-1)
        {
            a[idx++]=tp->flag;
            tp=tp->parent;
        }
        idx--;
        while(idx>=0)
        {
            printf("%d ",a[idx]);
            idx--;
        }
        printf("\n");
    }
    HallfCode(root->left);
    HallfCode(root->right);
}
int main()
{
    char buf[MAXIPUT];
    tnode_t *array[ALPHA_SIZE];
    tnode_t *node_tp;
    int array_el=0;
    int i,j,tp;
    int mina,mini;
    scanf("%s",buf);
    printf("inputlenght=%d\n",strlen(buf));
    /*统计输入字符串的字符种类，和字符个数，创建子节点*/
    for(i=0;buf[i]!='\0';i++)
    {
        tp=ForSearch(array,array_el,buf[i]);
        if(tp!=-1)  //字符已经存在
        {
            (array[tp]->times)++;
        }
        else
        {
            node_tp=(tnode_t*)malloc(sizeof(tnode_t));
            node_tp->c = buf[i];
            node_tp->times=1;
            //node_tp->flag=0;
            node_tp->parent=NULL;
            node_tp->left=NULL;
            node_tp->right=NULL;
            array[array_el]=node_tp;
            array_el++;
        }
    }

    /*创建哈夫曼树*/
    for(i=array_el;i>1;i--)
    {
        ChooseTwo(array,i,&mina,&mini);
        //printf("choose min=%d:max=%d\n",mini,mina);
        if(mina==mini)
        {
            printf("choose error!:%d\n",mina);
        }
        /*创建一个节点作为选定的两个节点的父节点*/
        node_tp=(tnode_t*)malloc(sizeof(tnode_t));
        node_tp->c='#';
        /*左子树，flag为0*/
        node_tp->left=array[mini];
        array[mini]->flag=0;
        array[mini]->parent=node_tp;
        /*左子树，flag为1*/
        node_tp->right=array[mina];
        array[mina]->flag=1;
        array[mina]->parent=node_tp;
        node_tp->times=array[mini]->times +array[mina]->times;

        /*保证将已经处理的节点放出数组外面，移到数组的尾部*/
        if(mini<i-2 && mina<i-2)
        {
            array[mini]=array[i-1];
            array[mina]=array[i-2];
        }else if(mini>=i-2 && mina>=i-2)
        {
            ;
        }else if(mini==i-1||mina==i-1)
        {
            tp=(mini<mina)?mini:mina;
            array[tp]=array[i-2];
        }
        else if(mini==i-2 ||mina==i-2)
        {
            tp=(mini<mina)?mini:mina;
            array[tp]=array[i-1];
        }
        /*将处理后的两个子节点的父节点假如数组*/
        array[i-2]=node_tp;
    }
    array[0]->parent=NULL;
    array[0]->flag=-1;
    /*校验编码过程*/
    if(array[0]->times != strlen(buf))
    {
        printf("error coding\n");
        exit(1);
    }
    printf("\n============================\n  HALLFMANCODING!\n");
    HallfCode(array[0]);
    return 0;
}
