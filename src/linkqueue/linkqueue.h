/*
 * linkqueue.h
 *
 *  Created on: 2017年2月17日
 *      Author: hntea
 */

#ifndef SRC_LINKQUEUE_LINKQUEUE_H_
#define SRC_LINKQUEUE_LINKQUEUE_H_


typedef void LinkQueue;

LinkQueue* LinkQueue_Create();

void LinkQueue_Destroy(LinkQueue* queue);

void LinkQueue_Clear(LinkQueue* queue);

int LinkQueue_Append(LinkQueue* queue, void* item);

void* LinkQueue_Retrieve(LinkQueue* queue);

void* LinkQueue_Header(LinkQueue* queue);

int LinkQueue_Length(LinkQueue* queue);



#endif /* SRC_LINKQUEUE_LINKQUEUE_H_ */
