/*
 * Mgraph.h
 *
 *  Created on: 2017年2月20日
 *      Author: hntea
 *
 *      邻接矩阵法图
 *
 *      缺点：占用大量内存。
 */

#ifndef SRC_MGRAPH_MGRAPH_H_
#define SRC_MGRAPH_MGRAPH_H_


typedef void MGraph;		//图
typedef void MVertex;		//顶点数据类型
typedef void(MGprintf)(MVertex*);	//打印回调

/*
 * 函数功能：创建n个顶点的图
 * 参数说明：
 * 			n:顶点个数
 * 			v:矩阵空间
 * */
MGraph* MGraphCreate(MVertex** v,int n);


/*
 * 函数功能：销毁图
 * 参数说明：
 * */
void MGraphDestory(MGraph* graph);


/*
 * 函数功能：将图中的边集合清空
 * 参数说明：
 * */
void MGraphClear(MGraph* graph);


/*
 * 函数功能：在图中的V1和V2之间加上边，且边的权为w
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2:顶点
 * 			w:权
 * */
int MGraphAddEdge(MGraph* graph,int v1,int v2,int w);


/*
 * 函数功能：删除两个顶点之间的边
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：被删除的边的权
 * */
int MGraphRemoveEdge(MGraph* graph,int v1,int v2);

/*
 * 函数功能：获取两个顶点之间的权
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：边的权
 * */
int MGraphGetEdge(MGraph* graph,int v1,int v2);


/*
 * 函数功能：顶点V的度
 * 参数说明：
 * 返回：顶点的度
 * */
int MGraphTD(MGraph* graph,int v);

/*
 * 函数功能：获取图中顶点总数
 * 参数说明：
 * 返回：顶点总数
 * */
int MGraphVectexCount(MGraph* graph);

/*
 * 函数功能：获取图的所有边
 * 参数说明：
 * 返回：图的边数
 * */
int MGraphEdgeCount(MGraph* graph);

/*
 * 函数功能：打印
 * 参数说明：
 * 返回：
 * */
void MGraphPrintf(MGraph* graph,MGprintf* pFun);

#endif /* SRC_MGRAPH_MGRAPH_H_ */
