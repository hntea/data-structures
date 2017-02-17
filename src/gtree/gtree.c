/*
 * gtree.c
 *
 *  Created on: 2017年2月9日
 *      Author: hntea
 */

#include <stdio.h>
#include <malloc.h>
#include "../linklist/linklist.h"
#include "gtree.h"

/*
 * 树结点
 * 存放具体数据
 * */
typedef struct _tag_GTreeNode GTreeNode;
struct _tag_GTreeNode
{
	GTreeData* data;	//用户数据
	GTreeNode* parent;	//父节点
	LinkList* child;	//子节点也是链表存储
};

/*
 * 组织链表
 *
 * 利用链表组织树中的各个结点
 * 链表中的前后关系不代表结点间的逻辑关系
 * 结点的逻辑关系由 child 域指定
 * child 数据域保存其它结点的【存储地址】
 *
 * 树可以看作是一个递归的模式，一层一层的套着
 * */
typedef struct _tag_TLNode TLNode;
struct _tag_TLNode{
	LinkListNode header;
	GTreeNode* node;
};

/*
 * 递归打印
 * */
static void recursive_display(GTreeNode* node, GTree_Printf* pFunc, int format, int gap, char div)
{
    int i = 0;

    if( (node != NULL) && (pFunc != NULL) )
    {
        for(i=0; i<format; i++)
        {
            printf("%c", div);
        }

        pFunc(node->data);	//回调打印函数

        printf("\n");

        for(i=0; i<LinkList_Length(node->child); i++)
        {
            TLNode* trNode = (TLNode*)LinkList_Get(node->child, i);

            recursive_display(trNode->node, pFunc, format + gap, gap, div);
        }
    }
}


//要点：每次删除都需要删除两个链表中的节点！
static void recursive_delete(LinkList* list, GTreeNode* node)
{
    if( (list != NULL) && (node != NULL) )
    {
        GTreeNode* parent = node->parent;
        int index = -1;
        int i = 0;

        //从组织链表中删除
        for(i=0; i<LinkList_Length(list); i++)
        {
            TLNode* trNode = (TLNode*)LinkList_Get(list, i);

            if( trNode->node == node )
            {
                LinkList_Delete(list, i);

                free(trNode);

                index = i;

                break;
            }
        }

        //递归遍历删除父结点以下的子节点
        if( index >= 0 )
        {
            if( parent != NULL )
            {
            	//从父亲节点的child链表中删除
                 for(i=0; i<LinkList_Length(parent->child); i++)
                 {
                     TLNode* trNode = (TLNode*)LinkList_Get(parent->child, i);

                     if( trNode->node == node )
                     {
                         LinkList_Delete(parent->child, i);

                         free(trNode);

                         break;
                     }
                 }
            }
            //直到遍历完所有子节点，子节点也可以是其它结点的父结点
            while( LinkList_Length(node->child) > 0 )
            {
                TLNode* trNode = (TLNode*)LinkList_Get(node->child, 0);

                recursive_delete(list, trNode->node);
            }

            LinkList_Destroy(node->child);

            free(node);
        }
    }
}

static int recursive_height(GTreeNode* node)
{
    int ret = 0;

    if( node != NULL )
    {
        int subHeight = 0; //子树高度
        int i = 0;

        for(i=0; i<LinkList_Length(node->child); i++)
        {
            TLNode* trNode = (TLNode*)LinkList_Get(node->child, i);

            subHeight = recursive_height(trNode->node);

            //获取子树中高度的最大值
            if( ret < subHeight )
            {
                ret = subHeight;
            }
        }

        ret = ret + 1; //总高度
    }

    return ret;
}

//求度数
static int recursive_degree(GTreeNode* node)
{
	int ret = -1;

    if( node != NULL )
    {
        int subDegree = 0;
        int i = 0;

        //根节点度数也就是子链表的长度
        ret = LinkList_Length(node->child);

        for(i=0; i<LinkList_Length(node->child); i++)
        {
            TLNode* trNode = (TLNode*)LinkList_Get(node->child, i);

            subDegree = recursive_degree(trNode->node);

            //获取最大值
            if( ret < subDegree )
            {
                ret = subDegree;
            }
        }
    }

    return ret;
}
/*
 * 创建通用树
 *
 * 树本质上由链表构成，那么创建时即相当于创建一个空链表头
 *
 * */
GTree* GTree_Create()
{
	return LinkList_Create();
}

/*
 * 销毁树
 * */
void GTree_Destroy(GTree* tree){
    GTree_Clear(tree);
    LinkList_Destroy(tree);
}


/*
 * 清除树
 * */
void GTree_Clear(GTree* tree)
{
     GTree_Delete(tree, 0);
}

/*
 * 递归销毁
 * */
GTreeData* GTree_Delete(GTree* tree, int pos)
{
    TLNode* trNode = (TLNode*)LinkList_Get(tree, pos);
    GTreeData* ret = NULL;

    if( trNode != NULL )
    {
        ret = trNode->node->data;

        recursive_delete(tree, trNode->node);
    }

    return ret;
}

/*
 * 函数功能：将数据以子结点的方式插入
 * 			 本质是往两个链表中插入数据
 * 参数说明：
 * 			tree:所在树
 * 			data:用户数据
 * 			pPos:父结点所在位置
 * */
int GTree_Insert(GTree* tree, GTreeData* data, int pPos){

    LinkList* list = (LinkList*)tree;

	//合法性判断 父节点所在位置不能超过组织链表的长度
    int ret = (list != NULL) && (data != NULL) && (pPos < LinkList_Length(list));

	if(ret){
		TLNode* trNode = (TLNode*)malloc(sizeof(TLNode));	  //组织链表
        TLNode* cldNode = (TLNode*)malloc(sizeof(TLNode));	  //插入的数据被当作是一个子结点
        TLNode* pNode = (TLNode*)LinkList_Get(list, pPos);    //获取父节点所在位置

        GTreeNode* gNode = (GTreeNode*)malloc(sizeof(GTreeNode));	//需要构造目标对象

        ret = (trNode != NULL) && (cldNode != NULL) && (gNode != NULL);

        if(ret){
        	//填充构造数据
        	gNode->data = data;
        	gNode->parent = NULL;
        	gNode->child =  LinkList_Create();

        	//目标对象即存在于组织链表，也存在于子结点中
        	trNode->node = gNode;
        	cldNode->node = gNode;

        	//插入主干组织链表中
        	LinkList_Insert(list, (LinkListNode*)trNode, LinkList_Length(list));

        	//若父节点存在，则将子节点插入到子节点链表中
            if( pNode != NULL )
            {
                gNode->parent = pNode->node;

                LinkList_Insert(pNode->node->child, (LinkListNode*)cldNode, LinkList_Length(pNode->node->child));
            }
        }
        else
        {
            free(trNode);
            free(cldNode);
            free(gNode);
        }
	}

	return ret;
}

GTreeData* GTree_Get(GTree* tree, int pos)
{
    TLNode* trNode = (TLNode*)LinkList_Get(tree, pos);
    GTreeData* ret = NULL;

    if( trNode != NULL )
    {
        ret = trNode->node->data;
    }

    return ret;
}

GTreeData* GTree_Root(GTree* tree)
{
    return GTree_Get(tree, 0);
}

int GTree_Height(GTree* tree)
{
    TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);
    int ret = 0;

    if( trNode != NULL )
    {
        ret = recursive_height(trNode->node);
    }

    return ret;
}

int GTree_Count(GTree* tree)
{
    return LinkList_Length(tree);
}

int GTree_Degree(GTree* tree)
{
    TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);
    int ret = -1;

    if( trNode != NULL )
    {
        ret = recursive_degree(trNode->node);
    }

    return ret;
}

void GTree_Display(GTree* tree, GTree_Printf* pFunc, int gap, char div)
{
    TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);

    if( (trNode != NULL) && (pFunc != NULL) )
    {
        recursive_display(trNode->node, pFunc, 0, gap, div);
    }
}
