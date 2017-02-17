/*
 * traversalBtree.c
 *
 *  Created on: 2017年2月17日
 *      Author: hntea
 */

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "traversalBtree.h"
#include "../linkqueue/linkqueue.h"


/*
 * 函数功能：前序遍历
 * 算法思想：根->左->右
 * 参数说明：
 *
 * */
void pre_order_traversal(BTreeNode* node){

	Node* data = (Node*)node;

	if(data!= NULL){

		//访问根节点的数据
		printf("%c ",data->data);

		//前序遍历左子树
		pre_order_traversal(data->link.left);

		//前序遍历右子树
		pre_order_traversal(data->link.right);
	}

}


/*
 * 函数功能：中序遍历
 * 算法思想：左->根->右
 * 参数说明：
 *
 * */
void mid_order_traversal(BTreeNode* node){

	Node* data = (Node*)node;

	if(data!= NULL){

		//遍历左子树
		pre_order_traversal(data->link.left);

		//访问根节点中的数据
		printf("%c ",data->data);

		//遍历右子树
		pre_order_traversal(data->link.right);
	}

}

/*
 * 函数功能：后序遍历
 * 算法思想：左->右->根
 * 参数说明：
 *
 * */
void back_order_traversal(BTreeNode* node){

	Node* data = (Node*)node;

	if(data!= NULL){

		//遍历左子树
		pre_order_traversal(data->link.left);

		//遍历右子树
		pre_order_traversal(data->link.right);

		//访问根节点中的数据
		printf("%c ",data->data);
	}

}

/*
 * 函数功能：层次遍历
 * 算法思想：使用队列存放依次出队即可
 * 参数说明：
 *
 * */
void level_order_traversal(BTreeNode* node){

	Node* data = (Node*)node;

	Node* ret = NULL;

	if(data!= NULL)
	{
		LinkQueue* queue =  LinkQueue_Create();

		if(queue != NULL){

			//將根壓入節點
			LinkQueue_Append(queue,data);

			//循环取出并查询子节点，压入
			while(LinkQueue_Length(queue) > 0){

				ret = (Node*)LinkQueue_Retrieve(queue);

				printf("%c  ",ret->data);

				LinkQueue_Append(queue,ret->link.left);
				LinkQueue_Append(queue,ret->link.right);
			}
		}

	}

}
