/*
 * traversalBtree.h
 *
 *  Created on: 2017年2月17日
 *      Author: hntea
 */

#ifndef SRC_BTREE_TRAVERSALBTREE_H_
#define SRC_BTREE_TRAVERSALBTREE_H_

/*
 * 函数功能：前序遍历
 * 算法思想：根->左->右
 * 参数说明：
 *
 * */
void pre_order_traversal(BTreeNode* node);


/*
 * 函数功能：中序遍历
 * 算法思想：左->根->右
 * 参数说明：
 *
 * */
void mid_order_traversal(BTreeNode* node);

/*
 * 函数功能：后序遍历
 * 算法思想：左->右->中
 * 参数说明：
 *
 * */
void back_order_traversal(BTreeNode* node);

/*
 * 函数功能：层次遍历
 * 算法思想：使用队列存放依次出队即可
 * 参数说明：
 *
 * */
void level_order_traversal(BTreeNode* node);


#endif /* SRC_BTREE_TRAVERSALBTREE_H_ */
