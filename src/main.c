/*
 * main.c
 *
 *  Created on: 2017年1月11日
 *      Author: hntea
 */

#include <stdlib.h>
#include <stdio.h>
#include "seqlist/seqlist.h"
#include "gtree/gtree.h"
#include "btree/btree.h"
#include "btree/traversalBtree.h"
void SeqlistTest(){

	Seqlist* list = SeqlistCreate(20);
	printf("SeqList capacity = %d\n",SeqlistCapcity(list));
	printf("SeqList length = %d\n",SeqlistLength(list));

	int i;
	int* ret = NULL;
	for(i = 0; i<10;i++){
		SeqlistInsert(list,&i,i);
	}

	for(i=0;i<10;i++){
		ret = SeqListGet(list,i);
		printf("SeqlistGet: %d\n",*ret);
	}
	//Delete 是错的吗！！！ ？？？？
	for(i=0;i<5;i++){
		ret = SeqlistDelete(list,0);
		printf("SeqlistDelete: %d\n",*ret);
	}
	printf("*SeqlistDelete(list,3): %d\n",*(int*)SeqlistDelete(list,3));
	printf("*SeqlistDelete(list,1): %d\n",*(int*)SeqlistDelete(list,1));



	printf("SeqList capacity = %d\n",SeqlistCapcity(list));
	printf("SeqList length = %d\n",SeqlistLength(list));

	for(i=0;i<SeqlistLength(list);i++){
		ret = SeqListGet(list,i);
		printf("SeqlistGet: %d\n",*ret);
	}
	printf("SeqlistClear");
	SeqlistClear(list);
	printf("SeqList capacity = %d\n",SeqlistCapcity(list));
	printf("SeqList length = %d\n",SeqlistLength(list));

	printf("SeqlistDestory");
	SeqlistDestory(list);
	printf("SeqList capacity = %d\n",SeqlistCapcity(list));
	printf("SeqList length = %d\n",SeqlistLength(list));
}

void gtree_print(GTreeData* data)
{
    printf("%c", (int)data);
}
void gtreeTest(){
    GTree* tree = GTree_Create();
    int i = 0;

    GTree_Insert(tree, (GTreeData*)'A', -1);
    GTree_Insert(tree, (GTreeData*)'B', 0);
    GTree_Insert(tree, (GTreeData*)'C', 0);
    GTree_Insert(tree, (GTreeData*)'D', 0);
    GTree_Insert(tree, (GTreeData*)'E', 1);
    GTree_Insert(tree, (GTreeData*)'F', 1);
    GTree_Insert(tree, (GTreeData*)'H', 3);
    GTree_Insert(tree, (GTreeData*)'I', 3);
    GTree_Insert(tree, (GTreeData*)'J', 3);


    printf("Tree Height: %d\n", GTree_Height(tree));
    printf("Tree Degree: %d\n", GTree_Degree(tree));
    printf("Full Tree:\n");

    GTree_Display(tree, gtree_print, 4, '-');
}


void btree_print(Node* node){
	if(node != NULL){
	 printf("%c", node->data);
	}
}
void btreeTest(){
	Node A = {{NULL,NULL},'A'};
	Node B = {{NULL,NULL},'B'};
	Node C = {{NULL,NULL},'C'};
	Node D = {{NULL,NULL},'D'};
	Node E = {{NULL,NULL},'E'};
	Node F = {{NULL,NULL},'F'};

	//创建树
	BTree* tree = BtreeCreate();

	BtreeInsert(tree,(BTreeNode*)&A,0,0,0);
	BtreeInsert(tree, (BTreeNode*)&B, 0x00, 1, 0);
	BtreeInsert(tree, (BTreeNode*)&C, 0x01, 1, 1);
	BtreeInsert(tree, (BTreeNode*)&D, 0x00, 2, 0);
	BtreeInsert(tree, (BTreeNode*)&E, 0x02, 2, 1);
	BtreeInsert(tree, (BTreeNode*)&F, 0x02, 3, 0);


	//遍历测试
	printf("Traversal Tree: \n");
	pre_order_traversal(BtreeRoot(tree));
	printf("\n");

	mid_order_traversal(BtreeRoot(tree));
	printf("\n");

	back_order_traversal(BtreeRoot(tree));
	printf("\n");


	level_order_traversal(BtreeRoot(tree));
	printf("\n");

    printf("\nFull Tree: \n");
    Node* data = (Node*)BtreeGet(tree, 0x02, 2);
    printf("Full Tree Get position is: %c\n",data->data);
    printf("Full Tree height: %d\n",BtreeHeight(tree));
    printf("Full Tree degree: %d\n",BtreeDegree(tree));
	BtreeDisplay(tree,btree_print,0,4, '-');

	BtreeDelete(tree, 0x00, 1);

    printf("After Delete B: \n");
    printf("Count: %d\n", BtreeCount(tree));
    printf("After Delete B height: %d\n",BtreeHeight(tree));
    printf("After Delete B degree: %d\n",BtreeDegree(tree));
    BtreeDisplay(tree,btree_print,0,4, '-');


	//销毁
	BtreeDestory(tree);

}

int main(int argc,char* argv[]){

	//SeqlistTest();
	//gtreeTest();
	btreeTest();
	printf("\n OK!\n");
	return 0;
}
