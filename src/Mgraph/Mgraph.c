/*
 * Mgraph.c
 *
 *  Created on: 2017年2月20日
 *      Author: hntea
 *
 *      邻接矩阵法图(有向图)
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Mgraph.h"


/*
 * 头节点数据结构
 * */
typedef struct _tag_Mgraph TMgraph;
struct _tag_Mgraph{
	int count;			//顶点个数
	MVertex** v;		//顶点相关的数据类型
	int** matrix;		//记录描述边集合的二维数组，存放权
};

/*
 * 函数功能：创建n个顶点的图
 * 参数说明：
 * 		n:顶点个数
 * 		v:矩阵空间
 * */
MGraph* MGraphCreate(MVertex** v,int n){

	TMgraph* tmgraph = NULL;
	if((n > 0) && (v != NULL))
	{
		tmgraph = (TMgraph*)malloc((sizeof(TMgraph)));
		if(tmgraph != NULL){
			int* p = NULL;
			tmgraph->count = n;
			tmgraph->v = (MVertex**)malloc(sizeof(MVertex*) * n);	//申请顶点数据空间,若二级指针非指向二维数组，则等效于本身
			tmgraph->matrix = (int**)malloc(sizeof(int*) * n);		//分配二级指针，指向【一维指针数组】
			p = (int*)calloc(n*n,sizeof(int));						//通过一级指针开辟数据空间并初始化为0
			//将一维指针数组中的指针链接到数据空间
			if((tmgraph->v != NULL) && (tmgraph->matrix != NULL) && (p != NULL))
			{
				int i;
				for(i=0;i<n;i++){
					tmgraph->v[i] = v[i];
					tmgraph->matrix[i] = p+i*n;
				}
			}
			//释放空间注意从内到外
			else{
				free(p);
				free(tmgraph->matrix);
				free(tmgraph->v);
				free(tmgraph);
			}
		}
	}

	return tmgraph;
}


/*
 * 函数功能：销毁图
 * 参数说明：
 * */
void MGraphDestory(MGraph* graph){

	TMgraph* tmgraph = (TMgraph*)graph;

	if(tmgraph != NULL){

		tmgraph->count = 0;

		//多级指针释放时需要一层一层由内到外释放
		free(tmgraph->matrix[0]);
		free(tmgraph->matrix);

		free(tmgraph->v);
		free(tmgraph);
	}

}

/*
 * 函数功能：将图中的边集合清空
 * 参数说明：
 * */
void MGraphClear(MGraph* graph){	//o(n)

	TMgraph* tag = (TMgraph*)graph;
	if(tag!=NULL)
	{
		int i;
		int j;
		for(i=0;i<tag->count;i++){
			for(j=0;j<tag->count;j++){
				tag->matrix[i][j] = 0;
			}
		}
	}
}


/*
 * 函数功能：在图中的V1和V2之间加上边，且边的权为w
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2:顶点
 * 			w:权
 * */
int MGraphAddEdge(MGraph* graph,int v1,int v2,int w){

	TMgraph* tag = (TMgraph*)graph;

	int ret = (v1<tag->count) && (v2 < tag->count) && (w > 0);

	ret = ret && (v1>=0) && (v2>=0);

	if(ret){

		tag->matrix[v1][v2] = w;

	}

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
int MGraphGetEdge(MGraph* graph,int v1,int v2){

	int ret = 0;
	TMgraph* tag = (TMgraph*)graph;
	if((v1>=0) && (v2>=0) && (tag != NULL)){
		ret = tag->matrix[v1][v2];
	}

	return ret;
}

/*
 * 函数功能：删除两个顶点之间的边
 * 参数说明：
 * 			graph：图
 * 			v1:顶点
 * 			v2：顶点
 * 返回：被删除的边的权
 * */
int MGraphRemoveEdge(MGraph* graph,int v1,int v2){
	TMgraph* tag = (TMgraph*)graph;
	int ret = MGraphGetEdge(graph,v1,v2);
	if(ret!=0){
		tag->matrix[v1][v2] = 0;
	}
	return ret;
}

/*
 * 函数功能：顶点V的度
 * 定义：顶点V的度是和V相关联的边的数目。
 * 		TD(V)总度数 = ID(V)入度 + OD(V)出度
 * 参数说明：
 * 返回：顶点的度
 * */
int MGraphTD(MGraph* graph,int v){

	int ret = 0;
	TMgraph* tag = (TMgraph*)graph;

	int condition = (tag != NULL);

	condition = condition && (0<=v) &&(v <= tag->count);

	if(condition){

		int i=0;

		for(i=0;i<tag->count;i++){

			if(tag->matrix[v][i]){
				ret++;
			}

			if(tag->matrix[i][v]){
				ret++;
			}
		}

	}

	return ret;
}


/*
 * 函数功能：获取图中顶点总数
 * 参数说明：
 * 返回：顶点总数
 * */
int MGraphVectexCount(MGraph* graph){

	TMgraph* tag = (TMgraph*)graph;

	int ret = 0;

	if(tag != NULL){

		ret = tag->count;

	}

	return ret;
}

/*
 * 函数功能：获取图的所有边
 * 参数说明：
 * 返回：图的边数(有向边是无向边的两倍)
 * */
int MGraphEdgeCount(MGraph* graph){

	int ret = 0;
	TMgraph* tag = (TMgraph*)graph;

	if(tag != NULL){

		int i=0,j=0;

		for(i=0;i<tag->count;i++){
			for(j=0;j<tag->count;j++){

				if(tag->matrix[i][j] != 0){
					ret++;
				}
			}
		}

	}

	return ret;
}


/*
 * 函数功能：打印
 * 参数说明：
 * 返回：
 * */
void MGraphPrintf(MGraph* graph,MGprintf* pFun){

	TMgraph* tag = (TMgraph*)graph;

	if((tag!=NULL) && (pFun!=NULL)){

		int i,j;

		printf("Matrix Vertex is: ");

		MVertex** vp = tag->v;

		for(i=0;i<tag->count;i++){
				pFun(vp++);	//pFun(v[i])这种写法用GCC编译会出现执行错误,只能通过指针的递增来访问
		}

		printf("\n");

		printf("Matrix Edge is:\n ");
		MVertex** vi = tag->v;
		for(i=0;i<tag->count;i++){
			MVertex** vj = tag->v;
			for(j=0;j<tag->count;j++){

				if(tag->matrix[i][j]!=0)
				{
					printf("<");
					pFun(vi);
					printf(",");
					pFun(vj);
					printf(",%d",tag->matrix[i][j]);
					printf(">");
					printf("  ");
				}
				vj++;
			}

			vi++;
		}
	}

}
