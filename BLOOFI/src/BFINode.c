#include "BFINode.h"
#include <stdlib.h>

void BFINode(struct BFINode *bfn,struct bloom *value,int order,bool splitFull){

	bfn->value=value;
	bfn->order=order;
	bfn->splitFull=splitFull;
	bfn->parent=NULL;
	//bfn->children=NULL;
}
