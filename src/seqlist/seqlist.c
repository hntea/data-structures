/*
 * seqlist.c
 *
 *  Created on: 2017年1月12日
 *      Author: hntea
 */

#include "seqlist.h"

/*
 * 数据封装
 * */
typedef long TSeqListNode;			//使用最长数据长度，可容纳其它类型数据
typedef struct _tag_seqlist{
	unsigned long capcity;			//容量
	unsigned long length;			//长度
	TSeqListNode* node;				//容量指针
}TSeqlist;


Seqlist* SeqlistCreate(long capcity){
	TSeqlist* ret = NULL;
	if(capcity >=0 ){
		ret = (TSeqlist*)malloc(sizeof(TSeqlist) + sizeof(TSeqListNode)*capcity);
	}
	if(ret != NULL){
		ret->capcity = capcity;
		ret->length = 0;
		ret->node = (TSeqListNode*)(ret+1);			//指向后面容量位置
	}
	return ret;
}


void SeqlistDestory(Seqlist* tlist){
	TSeqlist* list = (TSeqlist*)tlist;
	list->capcity= -1;
	list->length = 0;
	free(list);
}

/*
 * 清空
 * */
void SeqlistClear(Seqlist* tlist){
	TSeqlist* list = (TSeqlist*)tlist;
	if(list != NULL)
		list->length = 0;
}

/*
 * 获取线性表中的长度
 * */
int SeqlistCapcity(Seqlist* tlist){
	int ret = -1;
	TSeqlist* list = (TSeqlist*)tlist;
	if(list != NULL){
		ret = list->capcity;
	}
	return ret;
}

/*
 * 获取线性表中的长度
 * */
int SeqlistLength(Seqlist* tlist){
	int ret = -1;
	TSeqlist* list = (TSeqlist*)tlist;
	if(list != NULL){
		ret = list->length;
	}
	return ret;
}


/*
 * 插入元素到线性表中
 * */
int SeqlistInsert(Seqlist* tlist,SeqlistNode* item,int pos){

	TSeqlist* list = (TSeqlist*)tlist;

	int ret = (list != NULL);
	int i = 0;
	//判断线性表是否合法
	ret = ret && (list->length + 1 <= list->capcity);

	//判断插入位置是否合法
	ret = ret && (0<=pos);

	//插入位置元素向后退
	if(ret)
	{
		if(pos >= list->length){
			pos = list->length;
		}
		//后移
		for(i=list->length;i>=pos;i--){
			list->node[i] = list->node[i-1];
		}

		list->node[pos] = (TSeqListNode)item;

		list->length++;
	}

	return ret;
}
/*
 * 获取线性表中某个元素的位置
 * */
SeqlistNode* SeqListGet(const Seqlist* slist,int pos){

	TSeqlist* list = (TSeqlist*) slist;

	TSeqListNode* ret = NULL;

	if((list!=NULL) && (0<=pos) && (pos<=list->length))
		ret = (SeqlistNode*)(list->node[pos]);
	return ret;
}

/*
 * 将元素从线性表中删除
 * 不知道错哪里！可能是编译器不支持指针数组的赋值形式
 * */
SeqlistNode* SeqlistDelete(Seqlist* slist,const int pos){
	int i=0;
	TSeqlist* list = (TSeqlist*) slist;
	SeqlistNode* ret = NULL;
	if((list != NULL) && (pos>=0) &&(pos < list->length))
	{
		ret = (SeqlistNode*)list->node[pos];
		for(i=pos+1;i < list->length;i++){
			//这个地方被编译器优化了，只剩下指针？
			list->node[i-1] = list->node[i];
		}
		list->length--;
	}
	return ret;
}



