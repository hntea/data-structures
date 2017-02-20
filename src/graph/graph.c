/*
 * graph.c
 *
 *  Created on: 2017年2月17日
 *      Author: hntea
 */

#include <stdio.h>
#include "graph.h"

/*
 * 函数功能：创建n个顶点的图
 * 参数说明：
 * */
Graph* GraphCreate(int n){
	Graph* graph = NULL;
	return graph;
}


/*
 * 函数功能：销毁图
 * 参数说明：
 * */
void GraphDestory(Graph* graph){

}


/*
 * 函数功能：将图中的边集合清空
 * 参数说明：
 * */
void GraphClear(Graph* graph){

}

/*
 * 函数功能：在图中的V1和V2之间加上边，且边的权为w
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2:顶点
 * 			w:权
 * */
int GraphAddEdge(Graph* graph,int v1,int v2,int w){
	int weight = 0;
	return weight;
}


/*
 * 函数功能：删除两个顶点之间的边
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：被删除的边的权
 * */
int GraphRemoveEdge(Graph* graph,int v1,int v2){
	int ret = 0;

	return ret;
}
/*
 * 函数功能：获取两个顶点之间的权
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：边的权
 * */
int GraphGetEdge(Graph* graph,int v1,int v2){
	int w = 0;

	return w;
}

/*
 * 函数功能：顶点V的度
 * 参数说明：
 * 返回：顶点的度
 * */
int GraphTD(Graph* graph,int v){
	int degree = 0;

	return degree;
}
/*
 * 函数功能：获取图中顶点总数
 * 参数说明：
 * 返回：顶点总数
 * */
int GraphVectexCount(Graph* graph){
	int count;

	return count;
}
/*
 * 函数功能：获取图的所有边
 * 参数说明：
 * 返回：图的边数
 * */
int GraphEdgeCount(Graph* graph){
	int count;

	return count;
}
