/*
 * gtree.h
 *
 *  Created on: 2017年2月9日
 *      Author: hntea
 */

#ifndef SRC_GTREE_GTREE_H_
#define SRC_GTREE_GTREE_H_

//数据封装，只在实现文件中具体指定数据类型
typedef void GTree;
typedef void GTreeData;
typedef void (GTree_Printf)(GTreeData*);


GTree* GTree_Create();

void GTree_Destroy(GTree* tree);

void GTree_Clear(GTree* tree);

int GTree_Insert(GTree* tree, GTreeData* data, int pPos);

GTreeData* GTree_Delete(GTree* tree, int pos);

GTreeData* GTree_Get(GTree* tree, int pos);

GTreeData* GTree_Root(GTree* tree);

int GTree_Height(GTree* tree);

int GTree_Count(GTree* tree);

int GTree_Degree(GTree* tree);

void GTree_Display(GTree* tree, GTree_Printf* pFunc, int gap, char div);


#endif /* SRC_GTREE_GTREE_H_ */
