/*
 * seqlist.h
 *
 *  Created on: 2017年1月12日
 *      Author: hntea
 */

#ifndef SRC_SEQLIST_SEQLIST_H_
#define SRC_SEQLIST_SEQLIST_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


typedef void Seqlist;
typedef void SeqlistNode;


/*
 * 创建
 * */
Seqlist* SeqlistCreate(long capcity);

/*
 * 销毁
 * */
void SeqlistDestory(Seqlist* list);

/*
 * 清空
 * */
void SeqlistClear(Seqlist* list);


/*
 * 获取线性表中的长度
 * */
int SeqlistCapcity(Seqlist* list);

/*
 * 获取线性表中的长度
 * */
int SeqlistLength(Seqlist* list);


/*
 * 插入元素到线性表中
 * */
int SeqlistInsert(Seqlist* list,SeqlistNode* item,int pos);

/*
 * 将元素从线性表中删除
 * */
SeqlistNode* SeqlistDelete( Seqlist* list,const int pos);

/*
 * 获取线性表中某个元素的位置
 * */
SeqlistNode* SeqListGet(const Seqlist* list,int pos);



#endif /* SRC_SEQLIST_SEQLIST_H_ */
