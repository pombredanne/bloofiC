#include <stdio.h>
#include "bloofi.h"

char str[2];

void bloom_filter_index(struct bloofi* bl, int order,struct bloom sampleFilter,bool splitFull){

		bl->splitFull=splitFull;
		bl->order=order;
		newList(&bl->bfList);
		struct bloom zeroFilter=createZeroBloomFilter(&sampleFilter);
		bl->root=BFINode(&zeroFilter,bl->order,bl->splitFull);
		printf("This is order:%d\n",bl->root->order);

}

struct bloom createZeroBloomFilter(struct bloom *filter){
	//double bitsPerElement=filter.bpe;
	int expectedNumberOfFilterElements=filter->entries;
	//int k=filter.hashes;
	struct bloom zeroFilter;
	bloom_init(&zeroFilter,expectedNumberOfFilterElements, 0.5f);
	return zeroFilter;
}

void bloom_filter_index2(struct bloofi* bl,int order,bool splitFull){

	bl->order=order;
	bl->splitFull=splitFull;
	for(int i=0;i<SIZE;i++)
	bl->hashTable[i]=NULL;
	//bl->bfList=bulkLoad(bfList);
}

int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter){

int id=newBloomFilter->id;
printf("ID:%d\n",id);
struct BFINode *node;
node=malloc(sizeof(struct BFINode));
node=search(bl->hashTable,id);
if(node ==NULL){
	return -1;
}
updateValueToTheRoot(node,newBloomFilter);
return 0;
}

void updateValueToTheRoot(struct BFINode *current,struct bloom *newValue){

	or_bloom_filter(current->value,newValue);
	if(current->parent!=NULL){
		updateValueToTheRoot(current->parent,newValue);
	}
}

int deleteFromIndex(struct bloofi* bl,int id){
	struct BFINode *node;
	node=malloc(sizeof(struct BFINode));
	node=search(bl->hashTable,id);
	if(node==NULL){
		return -1;
	}
	else{
		printf("ok\n");
	}
	deleteNode(bl,node);
	delete(bl->hashTable,id);
	bl->bfList=DeleteList(bl->bfList,node->value);
	return 0;
}
void insertBloomFilter(struct bloofi *bl,struct bloom *b){

	struct BFINode *newBFINode;
	newBFINode=BFINode(b,bl->order,bl->splitFull);
	//insert(b->id,newBFINode);
	bl->bfList=insertList(bl->bfList,b);
	if(bl->root->children == NULL){
		printf("NEW_LOG3\n");
		bl->root->children=insertList2(bl->root->children,newBFINode);
		newBFINode->parent=bl->root;
		or_bloom_filter(bl->root->value,b);
		printf("GetSize:%d\n",GetSize2(bl->root->children));
	}
	else{
		insert2(bl,bl->root,newBFINode);
		printf("NEW_LOG4\n");

	}
}

struct BFINode* insert2(struct bloofi *bl,struct BFINode *current,struct BFINode *newChild){
	printf("chiamate\n");
if(!isLeaf(current)){
	printf("entra\n");
	or_bloom_filter(current->value,newChild->value);
	//problema nella findClosest
	struct BFINode* closestChild=findClosest(current,current->children);
	//if(closestChild==NULL)
		//printf("è null\n");
	printf("flag3\n");
	struct BFINode *newSibling=insert2(bl,closestChild,newChild);
	if(newSibling==NULL)
		return NULL;
	else{
		if(current->parent==NULL){
			struct bloom tempFilter=createZeroBloomFilter(current->value);
			struct BFINode *newRoot=BFINode(&tempFilter,bl->order,bl->splitFull);
			or_bloom_filter(newRoot->value,current->value);
			or_bloom_filter(newRoot->value,newSibling->value);
			newList2(&newRoot->children);
			newRoot->children=insertList2(newRoot->children,current);
			current->parent=newRoot;
			newRoot->children=insertList2(newRoot->children,newSibling);
			newSibling->parent=newRoot;
			bl->root=newRoot;

			return NULL;

		}else{
			newSibling=insertEntryIntoParent(newSibling,current);
			return newSibling;
		}
	}

}
else{
	//il  problema sta qua
struct BFINode *newSibling=insertEntryIntoParent(newChild,current);
	return newSibling;
}

}
//collaudata
struct BFINode* insertEntryIntoParent(struct BFINode *newChild,struct BFINode *node){
//termina qua
int index=indexOfElement2(node->parent->children,node);
printf("Indice test:%d\n",index);
node->parent->children=insertList2ByIndex(node->parent->children,index+1,newChild);
newChild->parent=node->parent;

if(!needSplit(node->parent)){
	return NULL;
}
return NULL;
}

void deleteNode(struct bloofi* bl,struct BFINode *childNode){
	if(GetSize2(bl->root->children)<2){

	}
	struct BFINode *node=childNode->parent;
	node->children=DeleteList2(node->children,childNode);
	if(node==bl->root&&GetSize2(node->children)==1){
		if(!isLeaf(getElement2(node->children,0))){
		bl->root=getElement2(node->children,0);
		bl->root->parent=NULL;
		return;
		}
	}
	if(!needMerge(node)){
		//recomputeValueToTheRoot(node);
	}else{
		int index=indexOfElement2(node->parent->children,node);
		struct BFINode *sibling;
		bool isRightSibling=false;

		if(index+1<GetSize2(node->parent->children)){
			isRightSibling=true;
			sibling=getElement2(node->parent->children,index+1);
		}else{
			if(index-1<0){
				printf("Errore\n");
			}
			isRightSibling=false;
			sibling=getElement2(node->parent->children,index-1);
		}
		//if(sibling)





	}

	return;
}

int getHeightBloofi(struct bloofi *bf){
	return getLevel(bf->root);
}

int getSizeBloofi(struct bloofi *bf){

	return getTreeSize(bf->root);
}

int getBloomFilterSizeBloofi(struct bloofi *bf){

	return getBloomFilterSize(bf->root);
}

int getNbChildrenRootBloofi(struct bloofi *bf){

	return GetSize2(bf->root->children);
}

list getBFListBloofi(struct bloofi *bf){

	return bf->bfList;
}


list findMatches(struct BFINode *node,const void*o){

	list result;
	newList(&result);
	int lunghezza=strlen(o);
	printf("%d\n",lunghezza);
	if(!bloom_check(node->value,o,lunghezza)){
		//printf("sto iterando..\n");
		return result;
	}
	if(isLeaf(node)){
		result=insertList(result,node->value);
		return result;
	}
	for(int i=0;i<GetSize2(node->children);i++){
		result=addAll(result,findMatches(getElement2(node->children,i),o));
	}
	return result;
}

//list bulkload(struct bloofi *bl,list mbfList){


	//struct BFINode rightmost;

//}
