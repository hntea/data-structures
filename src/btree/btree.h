/*
 * btree.h
 *
 *  Created on: 2017年2月13日
 *      Author: hntea
 */

#ifndef SRC_BTREE_BTREE_H_
#define SRC_BTREE_BTREE_H_

//指路法数据封装
#define BT_LEFT 0
#define BT_RIGHT 1
typedef unsigned long long BTPos;	//位置信息

typedef void BTree;					//数据封装
typedef char UserData;				//用户数据


/*
 * 结点指针域
 * */
typedef struct _tag_BTreeNode BTreeNode;
struct _tag_BTreeNode{
	BTreeNode* left;
	BTreeNode* right;
};

/*
 * 头结点
 * */
typedef struct _tag_BTree TBTree;
struct _tag_BTree{
	int count;			//表示该树节点总个数
	BTreeNode* root;
};

/*
 * 数结点
 * */
typedef struct _tag_Node Node;
struct _tag_Node {
	BTreeNode link;
	UserData data;			//自定义用户数据
};



typedef void (BTreePrintf)(BTreeNode*);


/*
 * 函数功能：创建空树
 * */
BTree* BtreeCreate();


/*
 * 函数功能：插入数据
 * 参数说明：
 * 			tree：根
 * 			node：插入的数据
 * 			pos：位置
 * 			count：左右转的次数
 * 			flag： 左右标志
 * */
int BtreeInsert(BTree* tree,BTreeNode* node,BTPos pos,int count,int flag);

/*
 * 函数功能：销毁树
 * */
void BtreeDestory(BTree* tree);


/*
 * 函数功能：清空
 * */
void BtreeClear(BTree* tree);



/*
 * 函数功能：
 * */
BTreeNode* BtreeRoot(BTree* tree);

/*
 * 函数功能：删除结点
 * 参数说明：
 * */
BTreeNode* BtreeDelete(BTree* tree,BTPos pos,int count);


/*
 * 函数功能：搜索
 * */
BTreeNode* BtreeGet(BTree* tree,BTPos pos,int count);


/*
 * 函数功能：树的度
 * */
int BtreeDegree(BTree* tree);

/*
 * 函数功能：树的高度
 * */
int BtreeHeight(BTree* tree);

/*
 * 函数功能：总节点数
 * */
int BtreeCount(BTree* tree);

/*
 * 函数功能：
 * */
void BtreeDisplay(BTree* tree, BTreePrintf* pFunc,int tab, int gap, char div);

#endif /* SRC_BTREE_BTREE_H_ */
