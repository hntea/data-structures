/*
 * graph.h
 *
 *  Created on: 2017年2月17日
 *      Author: hntea
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

typedef void Graph;		//图
typedef void Vertex;	//顶点数据类型


/*
 * 函数功能：创建n个顶点的图
 * 参数说明：
 * */
Graph* GraphCreate(int n);


/*
 * 函数功能：销毁图
 * 参数说明：
 * */
void GraphDestory(Graph* graph);


/*
 * 函数功能：将图中的边集合清空
 * 参数说明：
 * */
void GraphClear(Graph* graph);


/*
 * 函数功能：在图中的V1和V2之间加上边，且边的权为w
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2:顶点
 * 			w:权
 * */
int GraphAddEdge(Graph* graph,int v1,int v2,int w);


/*
 * 函数功能：删除两个顶点之间的边
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：被删除的边的权
 * */
int GraphRemoveEdge(Graph* graph,int v1,int v2);

/*
 * 函数功能：获取两个顶点之间的权
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：边的权
 * */
int GraphGetEdge(Graph* graph,int v1,int v2);


/*
 * 函数功能：顶点V的度
 * 参数说明：
 * 返回：顶点的度
 * */
int GraphTD(Graph* graph,int v);

/*
 * 函数功能：获取图中顶点总数
 * 参数说明：
 * 返回：顶点总数
 * */
int GraphVectexCount(Graph* graph);

/*
 * 函数功能：获取图的所有边
 * 参数说明：
 * 返回：图的边数
 * */
int GraphEdgeCount(Graph* graph);

#endif /* SRC_GRAPH_GRAPH_H_ */
