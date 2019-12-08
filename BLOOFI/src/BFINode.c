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
		struct BFINode *child=getElement2(bfn->children,0);
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
		for(int i=0;i<GetSize2(bfn->children);i++){
			currentNode=getElement2(bfn->children,i);
			size+=getTreeSize(currentNode);
		}
		return size;
	}
}

int getBloomFilterSize(struct BFINode *bfn){
	return bfn->value->bits;
}

void recomputeValue(struct BFINode *bfn){
	printf("Eccomi nella recompute\n");
	bloom_free(bfn->value);
	struct BFINode *currentNode;
	for(int i=0;i<GetSize2(bfn->children);i++){
		currentNode=getElement2(bfn->children,i);
		printf("ID bfn node:%d\n",bfn->value->id);
		printf("ID current node:%d\n",currentNode->value->id);
		or_bloom_filter(bfn->value,currentNode->value);
		printf("Dopo l OR\n");
	}
}

bool needSplit(struct BFINode *bfn){
	if(bfn->splitFull){
		return !(bfn->children==NULL||GetSize2(bfn->children)<=2*bfn->order);
	}else{
		return !(bfn->children==NULL||GetSize2(bfn->children)<=2*bfn->order||isFull(bfn->value));
	}
}

bool needMerge(struct BFINode *bfn){

	return bfn->parent!=NULL && GetSize2(bfn->children)<bfn->order;
}

bool canRedistribute(struct BFINode *bfn){

	return GetSize2(bfn->children)>bfn->order;
}

int findClosestIndex(struct BFINode *b,listBFINode nodeList){
	printf("Sono nella findClosestIndex\n");
	if(EmptyList2(nodeList))
		return -1;
	struct BFINode *currentNode;
	currentNode=getElement2(nodeList,0);
	//ci sta un problema nella computeHammingDistance
	printf("ID_valoreB:%d\n",b->value->id);
	printf("ID_valoreCurrentNode:%d\n",currentNode->value->id);
	double minDistance=computeHammingDistance(b->value,currentNode->value);
	printf("minDistance:%f\n",minDistance);
    int minIndex=0;
    double currentDistance;
    for(int i=1;i<GetSize2(nodeList);i++){
    	currentNode=getElement2(nodeList,i);
    	currentDistance=computeHammingDistance(b->value,currentNode->value);
    	srand(time(NULL));
    	if(currentDistance<minDistance||(minDistance-currentDistance<0.00001&&rand()<1.0/GetSize2(nodeList))){
    		minDistance=currentDistance;
    		minIndex=i;
    	}
    }
    printf("mindIndex:%d\n",minIndex);
    return minIndex;
}

struct BFINode* findClosest(struct BFINode *bfn,listBFINode nodeList){
	//problema nella findClosestIndex
	printf("Sono nella find closest\n");
	printf("IDNellaIndex:%d\n",bfn->value->id);
	int index=findClosestIndex(bfn,nodeList);
	if(index>=0){
		return getElement2(nodeList,index);
	}
	else{
		return NULL;
	}
}