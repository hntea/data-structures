/*
 * Lgraph.c
 *
 *  Created on: 2017年2月20日
 *      Author: hntea
 *
 *      图的表示-邻接链表法
 *
 *  基本思想：
 *
 *  	从同一个顶点(链表头节点)出发的边链接在同一个链表中
 *  	每个链表节点代表一条边，节点中保存另一个顶点的下标和权值
 */
#include <stdio.h>
#include <malloc.h>
#include "Lgraph.h"
#include "../linklist/linklist.h"

/*
 * 头节点数据结构
 * */

typedef struct _tag_Lgraph{
	int count;			//顶点个数
	LVertex** v;		//顶点相关的数据类型
	LinkList** la;		//记录描述边集
}TLgraph;

/*
 * 每个链表中的数据
 * */
typedef struct _tag_LinkNode{
	LinkListNode header;	//链表头
	int w;					//权
	int v;					//另一个顶点的下标
}TListNode;

/*
 * 函数功能：创建n个顶点的图
 * 参数说明：
 * 			n:顶点个数
 * 			v:矩阵空间
 * */
LGraph* LGraphCreate(LVertex** v,int n){

	TLgraph* ret = NULL;

	if((v != NULL) && (n>0)){

		ret = (TLgraph*)malloc(sizeof(TLgraph));

		if(ret != NULL){

			ret->count = n;

			ret->v = (LVertex**)calloc(n,sizeof(LVertex*));		//分配顶点空间

			ret->la = (LinkList**)calloc(n,sizeof(LinkList*));	//分配链表指针数组

			int ok = (ret->v != NULL) &&(ret->la != NULL);

			if( ok )
			{
				int i;

				for(i=0;i<ret->count;i++)		//填充顶点
					ret->v[i] = v[i];

				for(i=0;(i<n) && ok ;i++)		//填充链表指针
					ok = ok && ((ret->la[i] = LinkList_Create()) != NULL);
			}

			if(!ok)
			{
				if(ret->la != NULL){
					int i = 0;
					for(i=0;i<n;i++){
						LinkList_Destroy(ret->la[i]);
					}
				}

				free(ret->la);
				free(ret->v);
				free(ret);
			}
		}
	}

	return ret;
}


/*
 * 函数功能：销毁图
 * 参数说明：
 * */
void LGraphDestory(LGraph* graph){

	TLgraph* ret = 	(TLgraph*) graph;

	if(ret != NULL){

		LGraphClear(ret);	//这里只是将链表中的数据清除，并没有删除链表哦

		int i = 0;

		//清除边集链表
		for(i=0;i<ret->count;i++){
			LinkList_Destroy(ret->la[i]);
		}

		free(ret->la);
		free(ret->v);
		free(ret);

	}

}

/*
 * 函数功能：将图中的边集合清空
 * 参数说明：
 * */
void LGraphClear(LGraph* graph){

	TLgraph* ret = 	(TLgraph*) graph;

	if(ret != NULL){

		int i = 0;

		for(i=0;i<ret->count;i++){

			while(LinkList_Length(ret->la[i]) > 0 )
			{
				free(LinkList_Delete(ret->la[i],0));
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
int LGraphAddEdge(LGraph* graph,int v1,int v2,int w){

	TLgraph* tag = 	(TLgraph*) graph;


	int ret = (tag != NULL);

	ret = ret && (v1>=0) && (v1<= tag->count);
	ret = ret && (v2>=0) && (v2<= tag->count);
	ret = ret && (w>0) ;

	if(ret)
	{
		TListNode* node = (TListNode*)malloc(sizeof(TListNode));
		if(node != NULL)
		{
			node->v = v2;
			node->w = w;
			LinkList_Insert(tag->la[v1],(LinkListNode*)node,0);	//每次都往头部插入就好了
		}
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
int LGraphRemoveEdge(LGraph* graph,int v1,int v2){

	TLgraph* tag = 	(TLgraph*) graph;

	int ret = (tag != NULL);

	ret = ret && (v1>=0) && (v1<= tag->count);
	ret = ret && (v2>=0) && (v2<= tag->count);

	if(ret){

		int i = 0;
		//遍历链表数组
		for(i=0;i<LinkList_Length(tag->la[v1]);i++){

			TListNode* node = (TListNode*)LinkList_Get(tag->la[v1],i);
			if(node->v == v2){
				ret = node->w;
				LinkList_Delete(tag->la[v1],i);
				free(node);
				break;
			}
		}
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
int LGraphGetEdge(LGraph* graph,int v1,int v2){
	TLgraph* tag = 	(TLgraph*) graph;

	int ret = (tag != NULL);

	ret = ret && (v1>=0) && (v1<= tag->count);
	ret = ret && (v2>=0) && (v2<= tag->count);

	if(ret){

		int i = 0;
		//遍历链表数组
		for(i=0;i<LinkList_Length(tag->la[v1]);i++){

			TListNode* node = (TListNode*)LinkList_Get(tag->la[v1],i);
			if(node->v == v2){
				ret = node->w;
				break;
			}
		}
	}
	return ret;
}

/*
 * 函数功能：顶点V的度
 * 参数说明：
 * 返回：顶点的度
 * */
int LGraphTD(LGraph* graph,int v){

	int deg = 0;
	TLgraph* tag = 	(TLgraph*) graph;

	if((tag != NULL) && (tag->count > v)){

		int i=0,j=0;

		for(i=0;i<tag->count;i++){

			for(j=0;j<(LinkList_Length(tag->la[i]));j++)
			{
				TListNode* node = (TListNode*)LinkList_Get(tag->la[i],j);

				if(node->v == v){
					deg++;
				}

			}
		}

		deg += LinkList_Length(tag->la[v]);
	}

	return deg;
}

/*
 * 函数功能：获取图中顶点总数
 * 参数说明：
 * 返回：顶点总数
 * */
int LGraphVectexCount(LGraph* graph){
	int ret = 0;
	TLgraph* tag = 	(TLgraph*) graph;
	if(tag != NULL){
		ret = tag->count;
	}
	return ret;
}

/*
 * 函数功能：获取图的所有边
 * 参数说明：
 * 返回：图的边数
 * */
int LGraphEdgeCount(LGraph* graph){
	//相当于链表中的节点总数
	int ret = 0;
	TLgraph* tag = 	(TLgraph*) graph;
	if(tag != NULL){
		int i;
		for(i=0;i<tag->count;i++){
			ret += LinkList_Length( tag->la[i]);
		}
	}
	return ret;
}

/*
 * 函数功能：打印
 * 参数说明：
 * 返回：
 * */
void LGraphPrintf(LGraph* graph,LGprintf* pFun){

	int ret = 0;
	TLgraph* tag = 	(TLgraph*) graph;

	if((tag != NULL) && (pFun != NULL)){

		int i=0,j=0;

		LVertex** vp = tag->v;

		for(i=0;i<tag->count;i++)
		{
			pFun(vp++);
		}


	}
}




