/*
 * Lgraph.h
 *
 *  Created on: 2017年2月20日
 *      Author: hntea
 */

#ifndef SRC_LGRAPH_LGRAPH_H_
#define SRC_LGRAPH_LGRAPH_H_


typedef void LGraph;		//图
typedef void LVertex;		//顶点数据类型
typedef void(LGprintf)(LVertex*);	//打印回调

/*
 * 函数功能：创建n个顶点的图
 * 参数说明：
 * 			n:顶点个数
 * 			v:矩阵空间
 * */
LGraph* LGraphCreate(LVertex** v,int n);


/*
 * 函数功能：销毁图
 * 参数说明：
 * */
void LGraphDestory(LGraph* graph);


/*
 * 函数功能：将图中的边集合清空
 * 参数说明：
 * */
void LGraphClear(LGraph* graph);


/*
 * 函数功能：在图中的V1和V2之间加上边，且边的权为w
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2:顶点
 * 			w:权
 * */
int LGraphAddEdge(LGraph* graph,int v1,int v2,int w);


/*
 * 函数功能：删除两个顶点之间的边
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：被删除的边的权
 * */
int LGraphRemoveEdge(LGraph* graph,int v1,int v2);

/*
 * 函数功能：获取两个顶点之间的权
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：边的权
 * */
int LGraphGetEdge(LGraph* graph,int v1,int v2);


/*
 * 函数功能：顶点V的度
 * 参数说明：
 * 返回：顶点的度
 * */
int LGraphTD(LGraph* graph,int v);

/*
 * 函数功能：获取图中顶点总数
 * 参数说明：
 * 返回：顶点总数
 * */
int LGraphVectexCount(LGraph* graph);

/*
 * 函数功能：获取图的所有边
 * 参数说明：
 * 返回：图的边数
 * */
int LGraphEdgeCount(LGraph* graph);

/*
 * 函数功能：打印
 * 参数说明：
 * 返回：
 * */
void LGraphPrintf(LGraph* graph,LGprintf* pFun);



#endif /* SRC_LGRAPH_LGRAPH_H_ */
