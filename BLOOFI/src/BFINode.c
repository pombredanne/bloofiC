#include "BFINode.h"
#include <stdlib.h>

struct BFINode* BFINode(struct bloom *value,int order,bool splitFull){

	struct BFINode *b;
	b=malloc(sizeof(struct BFINode));
	b->order=order;
	//printf("Order 1:%d\n",b->order);
	//printf("Order 2:%d\n",b->order);
	b->value=value;
	b->parent=NULL;
	b->splitFull=splitFull;
	b->children=NULL;
	return b;
	//bfn->value=value;
	//printf("aooooo\n");
	//bfn->order=order;
	//printf("ordine:%d\n",bfn->order);
	//bfn->splitFull=splitFull;
	//bfn->parent=NULL;
	//bfn->children=NULL;
	//newList2(&bfn->children);
	//if(bfn->children==NULL)
		//printf("siiiiiiiiiiii\n");
	//printf("ECCO:%p\n",bfn->children);
	//printf("%p\n",&bfn->children);
	//printf("VALORE ORDER BFINODE:%d\n",order);
	//struct BFINode *root;
	//struct bloom b2;
	//bloom_init(&b2, 7000, 0.5);
	//BFINode(root,&b2,10,true);
	//insertList2(bfn->children,root);
}
bool isLeaf(struct BFINode *bfn){
	return (bfn->children==NULL);
}
