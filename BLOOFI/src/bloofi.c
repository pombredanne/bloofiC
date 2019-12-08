#include <stdio.h>
#include "bloofi.h"


//FUNZIONI DI INIZIALIZZAZIONE

void bloom_filter_index(struct bloofi* bl, int order,struct bloom *sampleFilter,bool splitFull){

		bl->splitFull=splitFull;
		bl->order=order;
		newList(&bl->bfList);
		for(int i=0;i<SIZE;i++)
		bl->hashTable[i]=NULL;
		//struct bloom zeroFilter=createZeroBloomFilter(sampleFilter);
		bloom_init(sampleFilter,10000, 0.5f);
		bl->root=BFINode(sampleFilter,bl->order,bl->splitFull);
}

struct bloom createZeroBloomFilter(struct bloom *filter){
	//double bitsPerElement=filter.bpe;
	//int expectedNumberOfFilterElements=filter->entries;
	//int k=filter.hashes;
	struct bloom zeroFilter;
	bloom_init(&zeroFilter,10000, 0.5f);
	printf("Nuovo bloom creato:%d\n",zeroFilter.id);
	return zeroFilter;
}

void bloom_filter_index2(struct bloofi* bl,list bList,int order,bool splitFull){

	bl->order=order;
	bl->splitFull=splitFull;
	for(int i=0;i<SIZE;i++)
	bl->hashTable[i]=NULL;
	//bl->bfList=bulkLoad(bfList);
}

/*************************************************************************/

//FUNZIONI DI RICERCA
list findMatches(struct BFINode *node,const void*o){

	list result;
	newList(&result);
	int lunghezza=strlen(o);
	printf("%d\n",lunghezza);
	if(!bloom_check(node->value,o,lunghezza)){
		printf("sto iterando..\n");
		return result;
	}
	if(isLeaf(node)){
		printf("è na foglia\n");
		result=insertList(result,node->value);
		return result;
	}
	for(int i=0;i<GetSize2(node->children);i++){
		result=addAll(result,findMatches(getElement2(node->children,i),o));
	}
	return result;
}
/****************************************************************************/


//FUNZIONI DI AGGIORNAMENTO
int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter){

int id=newBloomFilter->id;
printf("ID:%d\n",id);
struct BFINode *node;
//node=malloc(sizeof(struct BFINode));
node=search(bl->hashTable,id);
if(node ==NULL){
	printf("ritorna -1\n");
	return -1;
}
updateValueToTheRoot(node,newBloomFilter);
return 0;
}

void updateValueToTheRoot(struct BFINode *current,struct bloom *newValue){
	printf("Si è questo:%d\n",current->value->id);
	or_bloom_filter(current->value,newValue);
	if(current->parent!=NULL){
		updateValueToTheRoot(current->parent,newValue);
	}
}

/**************************************************************************/


//FUNZIONI DI INSERIMENTO

void insertBloomFilter(struct bloofi *bl,struct bloom *b){
	printf("ID_ROOT:%d\n",bl->root->value->id);
	struct BFINode *newBFINode;
	newBFINode=BFINode(b,bl->order,bl->splitFull);
	insert(bl->hashTable,b->id,newBFINode);
	bl->bfList=insertList(bl->bfList,b);
	if(bl->root->children == NULL){
		printf("NEW_LOG3\n");
		bl->root->children=insertList2(bl->root->children,newBFINode);
		printf("Qui?\n");
		newBFINode->parent=bl->root;
		printf("ID_B:%d\n",b->id);
		or_bloom_filter(bl->root->value,b);
		//printf("GetSize:%d\n",GetSize2(bl->root->children));
	}
	//se invece ha almeno un figlio
	else{
		//printf("IDNellaInsertBloom:%d\n",newBFINode->value->id);
		//printf("IDcurrent:%d\n",bl->root->value->id);
		printf("id ultimo nodo:%d\n",newBFINode->value->id);
		insert2(bl,bl->root,newBFINode);
		printf("NEW_LOG4\n");

	}
}

struct BFINode* insert2(struct bloofi *bl,struct BFINode *current,struct BFINode *newChild){
	printf("chiamate\n");
if(!isLeaf(current)){
	printf("entra\n");
	printf("IDnewChild:%d\n",newChild->value->id);
	printf("IDcurrentttt:%d\n",current->value->id);
	or_bloom_filter(current->value,newChild->value);
	struct BFINode* closestChild=findClosest(newChild,current->children);
	printf("ID closest trovato:%d\n",closestChild->value->id);
	//printf("ID papà closest trovato:%d\n",closestChild->parent->value->id);
	printf("IDnewChild:%d\n",newChild->value->id);
	//if(closestChild==NULL)
		//printf("è null\n");
	printf("flag3\n");
	struct BFINode *newSibling=insert2(bl,closestChild,newChild);
	if(newSibling==NULL){
		return NULL;
	}
	else{
		if(current->parent==NULL){
			//struct bloom newBloom;
			//bloom_init(&newBloom,10000,0.5);
			//printf("Ma possibile??\n");
			//struct bloom tempFilter=createZeroBloomFilter(current->value);
			//struct bloom tempFilter;
			//bloom_init(&tempFilter,10000, 0.5f);
			//struct BFINode *newRoot=BFINode(&tempFilter,bl->order,bl->splitFull);
			//printf("id newbloom:%d\n",newBloom.id);
			//printf("id tempFilter:%d\n",tempFilter.id);
			//bloom_print(newSibling->value);
			//VisitList2(newSibling->children);
			//or_bloom_filter(newRoot->value,current->value);
			//or_bloom_filter(newRoot->value,newSibling->value);
			//newList2(&newRoot->children);
			//newRoot->children=insertList2(newRoot->children,current);
			//current->parent=newRoot;
			//newRoot->children=insertList2(newRoot->children,newSibling);
			//newSibling->parent=newRoot;
			//bl->root=newRoot;

			return NULL;

		}else{
			newSibling=insertEntryIntoParent(bl,newChild,current);
			return newSibling;
		}
	}

}
else{
	//printf("Mo fa la entry parent con gli id:%d e %d\n",newChild->value->id,current->value->id);
	//il  problema sta qua
	//printf("Current parent :D:%d\n",current->parent->value->id);
struct BFINode *newSibling=insertEntryIntoParent(bl,newChild,current);
	if(newSibling!=NULL)
		//printf("Ritorna IDs newNode:%d con entries%d\n",newSibling->value->id,newSibling->value->entries);
	return newSibling;
}

}


struct BFINode* insertEntryIntoParent(struct bloofi *bl,struct BFINode *newChild,struct BFINode *node){
//termina qua
	//printf("Mo fa la entry parent con gli id:%d e %d\n",newChild->value->id,node->value->id);
	//printf("Che nodo è:%d\n",node->value->id);
	//printf("mmmmmmmmmmm\n");
	//printf("ID PARENT:%d\n",node->parent->value->id);
int index=indexOfElement2(node->parent->children,node);
printf("Indice test:%d\n",index);
node->parent->children=insertList2ByIndex(node->parent->children,index+1,newChild);
newChild->parent=node->parent;

if(!needSplit(node->parent)){

	return NULL;
}
struct BFINode *nuovoNodo= split(bl,node->parent);
bloom_print(nuovoNodo->value);
return nuovoNodo;
}

struct BFINode *split(struct bloofi *bl,struct BFINode *current){
	printf("Sono nella split\n");
	printf("ID primo figlio:%d\n",getElement2(current->children,0)->value->id);
	printf("ID secondo figlio:%d\n",getElement2(current->children,1)->value->id);
	printf("ID terzo figlio:%d\n",getElement2(current->children,2)->value->id);
	printf("ID quarto figlio:%d\n",getElement2(current->children,3)->value->id);
	printf("ID quinto figlio:%d\n",getElement2(current->children,4)->value->id);

	printf("ID current nella split:%d\n",current->value->id);
	struct BFINode *newNode;
	struct BFINode *newChild;

	//struct bloom *sampleFilter=current->value;
	struct bloom zeroFilter;
	bloom_init(&zeroFilter,current->value->entries,current->value->error);
	printf("ID_ZERO_FILTER_MMM:%d\n",zeroFilter.id);
	newNode=BFINode(&zeroFilter,bl->order,bl->splitFull);
	//bloom_print(newNode->value);
	//for(int i=bl->order+1;i<GetSize2(current->children);i++){
		//newChild=getElement2(current->children,i);
		//newNode->children=insertList2(newNode->children,newChild);
		//newChild->parent=newNode;
		//or_bloom_filter(newNode->value,newChild->value);
	//}
	//primo estremo incluso-secondo secondo escluso
	//current->children=removeLastHalf(current->children,bl->order+1);
	//recomputeValue(current);
	return newNode;
}
/**************************************************************************/

//FUNZIONI DI CANCELLAZIONE


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


/************************************************************************/

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


//list bulkload(struct bloofi *bl,list mbfList){


	//struct BFINode rightmost;

//}
