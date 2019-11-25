#include <stdio.h>
#include "bloofi.h"

//char str[2];

void bloom_filter_index(struct bloofi* bl, int order,struct bloom* sampleFilter,bool splitFull){


	bl->splitFull=splitFull;
	bl->order=order;
	struct bloom b2;
	struct bloom b3;
	newList(&bl->bfList);
	//bl->idMap=ht_create(1024);

	//ht_put(bl->idMap, "foo", bl->root);
	//struct BFINode *b=ht_get(bl->idMap, "foo");
	bloom_init(&b2, 8000, 0.5);
	bloom_init(&b3, 4000, 0.5);
	//bloom_print(&b3);
	//bl->bfList=insertList(bl->bfList,&b2);
	bl->bfList=insertList(bl->bfList,&b3);
	VisitList(bl->bfList);
	BFINode(bl->root,&b2,10,true);
	struct bloom *zeroFilter;
	//printf("Valore order:%d\n",bl->order);
	//BFINode(bl->root,zeroFilter,bl->order,bl->splitFull);
	printf("ORDER ROOT:%d\n",bl->root->order);
	//printf("ORDER ROOT:%d\n",bl->root->order);
}

void bloom_filter_index2(struct bloofi* bl,list bfList,int order,bool splitFull){

	bl->order=order;
	bl->splitFull=splitFull;
	//bl->idMap=ht_create(1024);



	//bl->bfList=bulkLoad(bfList);
}

int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter){

int id=newBloomFilter->id;
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

void deleteNode(struct bloofi* bl,struct BFINode *childNode){



}

