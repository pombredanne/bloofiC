#include "BFINode.h"
#include <stdlib.h>

struct BFINode* BFINode(struct bloom *value,int order,bool splitFull){

	struct BFINode *b;
	b=malloc(sizeof(struct BFINode));
	b->order=order;
	b->value=value;
	b->parent=NULL;
	b->splitFull=splitFull;
	b->children=NULL;
	return b;
}

bool isLeaf(struct BFINode *bfn){

	return (bfn->children==NULL);
}

int getLevel(struct BFINode *bfn){
	if(isLeaf(bfn)){
		return 0;
	}else{
		struct BFINode *child=getElement(bfn->children,0);
		int childLevel=getLevel(child);
		return 1+childLevel;
	}
}

int getTreeSize(struct BFINode *bfn){
	struct BFINode *currentNode;
	if(isLeaf(bfn)){
		return 1;
	}else{
		int size=1;
		for(int i=0;i<getSize(bfn->children);i++){
			currentNode=getElement(bfn->children,i);
			size+=getTreeSize(currentNode);
		}
		return size;
	}
}

int getBloomFilterSize(struct BFINode *bfn){
	return bfn->value->bits;
}

void recomputeValue(struct BFINode *bfn){
	printf("Sono nella recomputeValue\n");
	bloom_clear(bfn->value);
	struct BFINode *currentNode;
	for(int i=0;i<getSize(bfn->children);i++){
		currentNode=getElement(bfn->children,i);
		or_bloom_filter(bfn->value,currentNode->value);

	}
}

bool needSplit(struct BFINode *bfn){
	if(bfn->splitFull){
		return !(bfn->children==NULL||getSize(bfn->children)<=2*bfn->order);
	}else{
		return !(bfn->children==NULL||getSize(bfn->children)<=2*bfn->order||isFull(bfn->value));
	}
}

bool needMerge(struct BFINode *bfn){

	return bfn->parent!=NULL && getSize(bfn->children)<bfn->order;
}

bool canRedistribute(struct BFINode *bfn){

	return getSize(bfn->children)>bfn->order;
}

int findClosestIndex(struct BFINode *b,list nodeList){

	if(isEmptyList(nodeList))
		return -1;
	struct BFINode *currentNode;
	currentNode=getElement(nodeList,0);
	double minDistance=computeHammingDistance(b->value,currentNode->value);
    int minIndex=0;
    double currentDistance;
    for(int i=1;i<getSize(nodeList);i++){
    	currentNode=getElement(nodeList,i);
    	currentDistance=computeHammingDistance(b->value,currentNode->value);
    	srand(time(NULL));
    	if(currentDistance<minDistance||(minDistance-currentDistance<0.00001&&rand()<1.0/getSize(nodeList))){
    		minDistance=currentDistance;
    		minIndex=i;
    	}
    }
    return minIndex;
}

struct BFINode* findClosest(struct BFINode *bfn,list nodeList){

	int index=findClosestIndex(bfn,nodeList);
	if(index>=0){
		return getElement(nodeList,index);
	}
	else{
		return NULL;
	}
}
