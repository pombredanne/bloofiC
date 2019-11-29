#include <stdio.h>
#include "bloofi.h"

//char str[2];

void bloom_filter_index(struct bloofi* bl, int order,struct bloom *sampleFilter,bool splitFull){
		bl->splitFull=splitFull;
		bl->order=order;
		struct bloom bb2;
		struct bloom bb3;
		newList(&bl->bfList);
		bloom_init(&bb2, 8000, 0.5);
		bloom_init(&bb3, 4000, 0.5);
		printf("listaaaaa\n");
		bl->root=BFINode(&bb2,bl->order,bl->splitFull);
		//struct bloom zeroFilter=createZeroBloomFilter(sampleFilter);
		printf("This is order:%d\n",bl->root->order);
			//printf("listaaaaa\n");
}

struct bloom createZeroBloomFilter(struct bloom filter){
	double bitsPerElement=filter.bpe;
	int expectedNumberOfFilterElements=filter.entries;
	int k=filter.hashes;
	struct bloom zeroFilter;
	bloom_init(&zeroFilter,expectedNumberOfFilterElements, 0.5f);
}

void bloom_filter_index2(struct bloofi* bl,list bfList,int order,bool splitFull){

	bl->order=order;
	bl->splitFull=splitFull;
	//bl->idMap=(struct DataItem*) malloc(sizeof(struct DataItem));
	//bl->bfList=bulkLoad(bfList);
}

int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter){

//int id=newBloomFilter->id;
//sprintf(str,"%d",id);
//struct BFINode node=ht_get(bl->idMap, str);
//if(node ==NULL){
	//return -1;
//}
//updateValueToTheRoot(node,newBloomFilter);
return 0;
}

int deleteFromIndex(struct bloofi* bl,int id){
	//struct BFINode node;
	//if(node==NULL){
		//return -1;
	//}
	//else{

	//}
	//deleteNode(node);
	//idMap.remove(id);
	//bfList.remove(node.value);
	return 0;
}
void insertBloomFilter(struct bloofi *bl,struct bloom *b){
	struct BFINode newBFInode;
	//BFINode(&newBFInode,b,bl->order,bl->splitFull);
	bl->bfList=insertList(bl->bfList,b);
	if(bl->root->children == NULL){
		printf("NEW_LOG3\n");
		bl->root->children=insertList2(bl->root->children,&newBFInode);
		newBFInode.parent=bl->root;
		printf("GetSize:%d\n",GetSize2(bl->root->children));
	}
	else{

		printf("NEW_LOG4\n");

	}
	//insert2(bl,bl->root,&newBFInode);
	//bl->root->children=insertList2(bl->root->children,&node);
	//VisitList2(bl->root->children);
}

//struct BFINode* insert2(struct bloofi *bl,struct BFINode *current,struct BFINode *newChild){

//if(!isLeaf(current)){
	//current->value;
	//struct BFINode closestChild=findClosest(current->children);
	//struct BFINode newSibling=insert2(bl,closestChild,newChild);
	///if(newSibling==NULL)
	//	return NULL;
	//else{
	//	if(current->parent==NULL){
			//current

	//	}
//	}

//}
	//printf("yesssss\n");

//}


void deleteNode(struct bloofi* bl,struct BFINode *childNode){

	//int size=GetSize2(bl->root->children);
	//printf("SIZE:%d\n",size);
}

//list bulkload(struct bloofi *bl,list mbfList){

//	if(GetSize(mbfList)>0){
	//	struct bloom base=GetFirst(mbfList);
//	}
	//struct BFINode rightmost;

//}
