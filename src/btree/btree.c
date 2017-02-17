/*
 * btree.c
 *
 *  Created on: 2017年2月13日
 *      Author: hntea
 */

#include <stdlib.h>
#include <stdio.h>
#include "btree.h"


// static 可以用于表示内部使用

/*
 * 函数功能：回调打印直到空
 * 参数说明：
 * 			node：数据节点
 * 			pFunc:回调
 * 			tab:缩进
 * 			gap:间隔
 * 			div:分隔符
 * */
static void recursive_printf(BTreeNode* node, BTreePrintf* pFunc, int tab, int gap, char div){

	int i = 0;

	if((node!=NULL)&&(pFunc!=NULL)){

		//打印缩进
		for(i=0; i<tab; i++)
        {
            printf("%c", div);
        }

		//打印结点数据
        pFunc(node);

        printf("\n");

        if( (node->left != NULL) || (node->right != NULL) )
        {
        	recursive_printf(node->left, pFunc, tab + gap, gap, div);
        	recursive_printf(node->right, pFunc, tab + gap, gap, div);
        }
	}
	else
    {
        for(i=0; i<tab; i++)
        {
            printf("%c", div);
        }
        printf("\n");
    }

}

/*
 * 函数功能：递归计算子数节点总数
 * 参数说明：
 *
 * */
static int recursive_count(BTreeNode* node){

	int count = 0;

	if(node != NULL){
		count = recursive_count(node->left) + recursive_count(node->right)+1;
	}

	return count;

}

/*
 * 函数功能：递归
 * 参数说明：
 *
 * */
static int recursive_height(BTreeNode* node){

	int height = 0;

	if(node != NULL){

		//分别求左右两颗树的高度，再取其中大的
		int lh = recursive_height(node->left);
		int rh = recursive_height(node->right);

		height = ((lh > rh)? lh : rh) + 1;

	}

	return height;
}
/*
 * 函数功能：深度递归
 * 参数说明：
 * 注意：二叉树的度最多也是2
 * */
static int recursive_degree(BTreeNode* node){

	int deg = 0;

	if(node != NULL){

		if(node->left != NULL)
			deg++;

		if(node->right != NULL)
			deg++;

		if(deg == 1){

            int ld = recursive_degree(node->left);
            int rd = recursive_degree(node->right);

            if( deg < ld )
            {
            	deg = ld;
            }

            if( deg < rd )
            {
            	deg = rd;
            }

		}

	}

	return deg;

}


/*
 * 函数功能：创建空树
 * */
BTree* BtreeCreate(){
	TBTree* ret = (TBTree*)malloc(sizeof(TBTree));
	if(ret != NULL){
		ret->count = 0;
		ret->root = NULL;
	}
	return ret;
}


/*
 * 函数功能：销毁树
 * */
void BtreeDestory(BTree* tree){
	free(tree);
}


/*
 * 函数功能：清空
 * */
void BtreeClear(BTree* tree){
	TBTree* tag = (TBTree*)tree;
	if(tag != NULL){
		tag->count = 0;
		tag->root = NULL;
	}
}

/*
 * 函数功能：
 * */
BTreeNode* BtreeRoot(BTree* tree){
	TBTree* tag = (TBTree*)tree;
	BTreeNode* ret = NULL;

	if(tag != NULL){
		ret = tag->root;
	}

	return ret;
}
/*
 * 函数功能：插入数据(指路法)
 * 参数说明：
 * 			tree：根
 * 			node：插入的数据
 * 			pos：位置
 * 			count:左右转的次数
 * 			flag: 左右标志
 * */
int BtreeInsert(BTree* tree,BTreeNode* node,BTPos pos,int count,int flag){

	int bit = 0;
	TBTree* tag = (TBTree*)tree;

	int ret = (tag != NULL) && (node != NULL) && ((flag == BT_LEFT) || (flag == BT_RIGHT));

	if(ret){

		BTreeNode* parent = NULL;
		BTreeNode* current =  tag->root;	//每次插入都要从根目录插入

		node->left = NULL;
		node->right = NULL;

		while((current != NULL) && (count > 0)){

			bit = pos & 1;
			pos = pos >> 1;

			parent = current;

			if(bit == BT_LEFT){

				current = current->left;

			}else if(bit == BT_RIGHT){

				current = current->right;
			}

			count--;
		}

		//找到要插入的位置
		if(flag == BT_RIGHT){

			node->right = current;

		}else if(flag == BT_LEFT)
		{

			node->left = current;

		}

		//插入位置判断
        if( parent != NULL )
        {
            if( bit == BT_LEFT )
            {
                parent->left = node;
            }
            else if( bit == BT_RIGHT )
            {
                parent->right = node;
            }
        }
        else
        {
            tag->root = node;
        }

	}
	return ret;
}


/*
 * 函数功能：删除结点
 * 参数说明：
 * 			pos:位置
 * 			count：左右转的总次数
 * 注意：指路法类似线性访问，所以删除时不需要将子节点的孩子一并删除
 * */
BTreeNode* BtreeDelete(BTree* tree,BTPos pos,int count){

	int bit = 0;
	TBTree* tag = (TBTree*)tree;

	if(tag != NULL){

		BTreeNode* parent = NULL;
		BTreeNode* current = tag->root;	//每次插入都要从根目录插入

		//定位
		while((current != NULL) && count >0){

			bit = pos & 1;
			pos = pos >> 1;

			parent = current;

			if(bit == BT_LEFT){

				current = current->left;

			}else if(bit == BT_RIGHT){

				current = current->right;
			}

			count--;
		}

		//删除节点
		if(parent != NULL){

            if( bit == BT_LEFT )
            {
                parent->left = NULL;
            }
            else if( bit == BT_RIGHT )
            {
                parent->right = NULL;
            }
		}else
        {
            tag->root = NULL;
        }

		//更新节点数

		tag->count = tag->count - BtreeCount((BTree*)current);

	}

	return 0;
}

/*
 * 函数功能：搜索
 * */
BTreeNode* BtreeGet(BTree* tree,BTPos pos,int count){

	TBTree* tag = (TBTree*)tree;
	BTreeNode* ret = NULL;
	int bit = 0;

	if(tag != NULL){

		bit = pos & 1;
		pos = pos >> 1;

		BTreeNode* current = tag->root;

		while((current != NULL) && (count>0))
		{
			if(bit == BT_RIGHT){
				current = current->right;
			}

			if(bit == BT_LEFT){
				current = current->left;
			}
			count--;
		}

		ret = current;
	}

	return ret;
}


/*
 * 函数功能：树的度
 * 定义：节点所包含子节点的个数的最大值称为度
 * 注意：二叉树中度只有0，1，2
 * */
int BtreeDegree(BTree* tree){

	int deg = 0;

	TBTree* tag = (TBTree*)tree;

	if(tag != NULL){

		deg = recursive_degree(tag->root);

	}

	return deg;
}

/*
 * 函数功能：树的高度
 * */
int BtreeHeight(BTree* tree){

	TBTree* tag = (TBTree*)tree;

	int height = 0;

	if(tree != NULL){

		height = recursive_height(tag->root);

	}

	return height;
}

/*
 * 函数功能：节点数
 * */
int BtreeCount(BTree* tree){

	int count = 0;

	TBTree* tag = (TBTree*)tree;

	if(tag != NULL){

		count = recursive_count(tag->root);

	}

	return count;
}



/*
 * 函数功能：数据打印
 * 参数说明：
 * 			tree：所在树
 * 			pFunc：回调打印函数
 * 			tab:缩进
 * 			gap：间隔
 * 			div：分隔符
 * */
void BtreeDisplay(BTree* tree, BTreePrintf* pFunc, int tab,int gap, char div){
	int ret = 0;

	TBTree* tag = (TBTree*)tree;

	ret = (tag != NULL) && (pFunc != NULL);

	if(ret){
		recursive_printf(tag->root,pFunc,tab,gap,div);
	}
}
