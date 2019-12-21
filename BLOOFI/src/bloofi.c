
#include <stdio.h>
#include "bloofi.h"
#include "time.h"

//FUNZIONI DI INIZIALIZZAZIONE

void bloom_filter_index(struct bloofi* bl, int order,struct bloom *sampleFilter,bool splitFull){

  bl->splitFull=splitFull;
  bl->order=order;
  newList(&bl->bfList);
  for(int i=0;i<SIZE;i++)
  bl->hashTable[i]=NULL;
  struct bloom* zeroFilter=createZeroBloomFilter(sampleFilter);
  bl->root=BFINode(zeroFilter,bl->order,bl->splitFull);
}

struct bloom* createZeroBloomFilter(struct bloom *filter){

 struct bloom *zeroFilter;
 zeroFilter=malloc(sizeof(struct bloom));
 bloom_init(zeroFilter,filter->entries, filter->error);
 assert(zeroFilter->bits==filter->bits);
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
int* search(struct bloofi*bl,const void*o){
	list x=searchBloomFilters(bl,o);
	int size=getSize(x);
	int ans[size];
	struct bloom *bf;
	for(int i=0;i<size;i++){
		bf=getElement(x,i);
		ans[i]=bf->id;
	}
	return ans;
}

list searchBloomFilters(struct bloofi*bl,const void *o){

	return findMatches(bl->root,o);

}

list findMatches(struct BFINode *node,const void*o){

 list result;
 newList(&result);
 int lunghezza=strlen(o);
 if(!bloom_check(node->value,o,lunghezza)){

  return result;
 }
 if(isLeaf(node)){

  result=insertElement(result,node->value);
  return result;
 }
 for(int i=0;i<getSize(node->children);i++){
  result=addAll(result,findMatches(getElement(node->children,i),o));
 }
 return result;
}

list naivefindMatches(struct BFINode *node,const void*o){

	list result;
	newList(&result);
	int lunghezza=strlen(o);
	if(isLeaf(node)){
		if(bloom_check(node->value,o,lunghezza)){
			result=insertElement(result,node->value);
		}
		return result;
	}
	for(int i=0;i<getSize(node->children);i++){
		result=addAll(result,naivefindMatches(getElement(node->children,i),o));
	}
	return result;
}
/****************************************************************************/


//FUNZIONI DI AGGIORNAMENTO
int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter){

int id=newBloomFilter->id;
struct BFINode *node;
//node=malloc(sizeof(struct BFINode));
node=searchHash(bl->hashTable,id);
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

/**************************************************************************/


//FUNZIONI DI INSERIMENTO

void insertBloomFilter(struct bloofi *bl,struct bloom *b){

 struct BFINode *newBFINode;
 newBFINode=BFINode(b,bl->order,bl->splitFull);
 insert(bl->hashTable,b->id,newBFINode);
 bl->bfList=insertElement(bl->bfList,b);
 if(bl->root->children == NULL){
  bl->root->children=insertElement(bl->root->children,newBFINode);
  newBFINode->parent=bl->root;
  or_bloom_filter(bl->root->value,b);

 }
 //se invece ha almeno un figlio
 else{

  insert2(bl,bl->root,newBFINode);

 }
}

struct BFINode* insert2(struct bloofi *bl,struct BFINode *current,struct BFINode *newChild){

if(!isLeaf(current)){
	printf("Id current:%d\n",current->value->id);
	printf("Id newChild:%d\n",newChild->value->id);
 or_bloom_filter(current->value,newChild->value);
 struct BFINode* closestChild=findClosest(newChild,current->children);
 struct BFINode *newSibling=insert2(bl,closestChild,newChild);
 if(newSibling==NULL){
  return NULL;
 }
 else{
  if(current->parent==NULL){
   struct bloom *tempFilter=createZeroBloomFilter(current->value);
   struct BFINode *newRoot=BFINode(tempFilter,bl->order,bl->splitFull);
   or_bloom_filter(newRoot->value,current->value);
   or_bloom_filter(newRoot->value,newSibling->value);
   newRoot->children=insertElement(newRoot->children,current);
   current->parent=newRoot;
   newRoot->children=insertElement(newRoot->children,newSibling);
   newSibling->parent=newRoot;
   struct BFINode *figlio2=getElement(newRoot->children,1);
   //VisitList2(figlio2->children);
 //  struct BFINode *figlio1=getElement2(newRoot->children,0);
 //  struct BFINode *figlio2=getElement2(newRoot->children,1);
 //  printf("id figlio1:%d\n",figlio1->value->id);
 //  printf("id figlio2:%d\n",figlio2->value->id);
   bl->root=newRoot;
  // VisitList2(bl->root->children);
   return NULL;

  }else{
	  printf("Cazzarola è entrato qua!\n");
   newSibling=insertEntryIntoParent(bl,newSibling,current);
   return newSibling;
  }
 }

}
else{


struct BFINode *newSibling=insertEntryIntoParent(bl,newChild,current);
	 return newSibling;
}

}


struct BFINode* insertEntryIntoParent(struct bloofi *bl,struct BFINode *newChild,struct BFINode *node){
printf("IDDDDDDD:%d\n",node->value->id);
printf("IDDDDDDD root:%d\n",bl->root->value->id);
int index=indexOfElement(node->parent->children,node);
printf("INDEX:%d\n",index);
node->parent->children=insertElementByIndex(node->parent->children,index+1,newChild);
newChild->parent=node->parent;
printf("Node parent ID:%d\n",node->parent->value->id);
printf("Size da analizzare prima:%d\n",getSize(node->parent->children));
printf("Id da analizzare prima:%d\n",newChild->value->id);
printf("Size da analizzare:%d\n",getSize(bl->root->children));
if(!needSplit(node->parent)){

 return NULL;
}
printf("Ehh ha bisogno dello split..\n");
struct BFINode *nuovoNodo= split(bl,node->parent);
//struct bloom *test;
//test=malloc(sizeof(struct bloom));
//bloom_init(test,10000,0.5);
//printf("ID TEST:%d\n",test->id);
return nuovoNodo;
}


struct BFINode *split(struct bloofi *bl,struct BFINode *current){
printf("SPLIT CHIAMATA\n");
 struct BFINode *newNode;
 struct BFINode *newChild;
 struct bloom* zeroFilter;
 zeroFilter=malloc(sizeof(struct bloom));
 bloom_init(zeroFilter,current->value->entries,current->value->error);
 printf("ID ZERO FILTER:%d\n",zeroFilter->id);
 newNode=BFINode(zeroFilter,bl->order,bl->splitFull);
 printf("ID NEW NODE:%d\n",newNode->value->id);
 printf("ID ZERO FILTER:%d\n",zeroFilter->id);
 for(int i=bl->order+1;i<getSize(current->children);i++){
  newChild=getElement(current->children,i);
  printf("Stiamo stampando l id del new child:%d\n",newChild->value->id);
  newNode->children=insertElement(newNode->children,newChild);
  newChild->parent=newNode;
  or_bloom_filter(newNode->value,newChild->value);
 }
 //primo estremo incluso-secondo secondo escluso
 current->children=removeLastHalf(current->children,bl->order+1);
 recomputeValue(current);
 return newNode;
}
/**************************************************************************/

//FUNZIONI DI CANCELLAZIONE


int deleteFromIndex(struct bloofi* bl,int id){
	printf("Sono nella deleteFromIndex\n");
 struct BFINode *node;
 //node=malloc(sizeof(struct BFINode));
 node=searchHash(bl->hashTable,id);
 printf("NODO:%d\n",node->value->id);
 if(node==NULL){
  return -1;
 }
 else{

 }
 deleteNode(bl,node);
 delete(bl->hashTable,id);
 bl->bfList=deleteElement(bl->bfList,node->value);
 return 0;
}


void deleteNode(struct bloofi* bl,struct BFINode *childNode){
	printf("Sono nella deleteNode con ID:%d\n",childNode->value->id);
 if(getSize(bl->root->children)<2){
	 printf("ERROR:nb children of root is:%d\n",getSize(bl->root->children));
	 assert(false);
 }
 struct BFINode *node=childNode->parent;
 node->children=deleteElement(node->children,childNode);
 if(node==bl->root&&getSize(node->children)==1){
  if(!isLeaf(getElement(node->children,0))){
  bl->root=getElement(node->children,0);
  bl->root->parent=NULL;
  return;
  }
 }
 printf("Sono il padre del newChild con ID:%d\n",node->value->id);
 if(!needMerge(node)){
  recomputeValueToTheRoot(node);
 }else{
  int index=indexOfElement(node->parent->children,node);
  struct BFINode *sibling;
  bool isRightSibling=false;

  if(index+1<getSize(node->parent->children)){
   isRightSibling=true;
   sibling=getElement(node->parent->children,index+1);
   printf("ID del sibling:%d\n",sibling->value->id);
  }else{
	  if(index-1<0){
		  printf("Errore\n");
	  }
   isRightSibling=false;
   sibling=getElement(node->parent->children,index-1);
  }
  if(canRedistribute(sibling)){
	  redistribute(node,sibling,isRightSibling);

  }else{
	  merge(node,sibling,isRightSibling);
	  deleteNode(bl,node);
  }
 }

 return;
}



void redistribute(struct BFINode *node,struct BFINode *sibling,bool isRightSibling){
	printf("Sono nella redistribute\n");
	int nbChildren=getSize(node->children)+getSize(sibling->children);
	int nbChildren1=nbChildren/2;
	int nbChildren2=nbChildren-nbChildren1;
	int nbChildrenToGive=getSize(sibling->children)-nbChildren2;

	struct BFINode*childToMove;
	if(isRightSibling){
		for(int i=0;i<nbChildrenToGive;i++){
			childToMove=getElement(sibling->children,0);
			sibling->children=deleteElementByIndexNode(sibling->children,0);
			node->children=insertElement(node->children,childToMove);
			childToMove->parent=node;
		}
	}else{

		for(int i=0;i<nbChildrenToGive;i++){
			childToMove=getElement(sibling->children,getSize(sibling->children)-1);
			sibling->children=deleteElementByIndexNode(sibling->children,getSize(sibling->children)-1);
			node->children=insertElementByIndex(node->children,0,childToMove);
			childToMove->parent=node;
		}


	}

	recomputeValue(sibling);
	recomputeValueToTheRoot(node);
}



void recomputeValueToTheRoot(struct BFINode *current){
	printf("Sono nella recomputeValueToTheRoot\n");
	recomputeValue(current);
	if(current->parent!=NULL){
		recomputeValueToTheRoot(current->parent);
	}
}

void merge(struct BFINode *node,struct BFINode *sibling,bool isRightSibling){
	printf("Sono nella merge\n");
	int nbChildrenToGive=getSize(node->children);

	struct BFINode *childToMove;
	if(isRightSibling){
		for(int i=0;i<nbChildrenToGive;i++){
			childToMove=getElement(node->children,getSize(node->children)-1);
			node->children=deleteElementByIndex(node->children,getSize(node->children)-1);
			sibling->children=insertElementByIndex(sibling->children,0,childToMove);
			or_bloom_filter(sibling->value,childToMove->value);
			childToMove->parent=sibling;

		}
	}else{

		for(int i=0;i<nbChildrenToGive;i++){
			childToMove=getElement(node->children,0);
			node->children=deleteElementByIndex(node->children,0);
			sibling->children=insertElement(sibling->children,childToMove);
			or_bloom_filter(sibling->value,childToMove->value);
			childToMove->parent=sibling;
		}


	}

}

/************************************************************************/
//FUNZIONI DA COLLOCARE ANCORA NON SI SA DOVE
void validate(struct bloofi *bl){
	aggregateChildren(bl,bl->root);
}

struct bloom* aggregateChildren(struct bloofi *bl,struct BFINode *node){
	if(node->children==NULL){
		return node->value;

	}
	struct bloom* first=getElement(bl->bfList,0);
	struct bloom* current=createZeroBloomFilter(first);

	for(int i=0;i<getSize(node->children);i++){
		struct BFINode*c=getElement(node->children,i);
		struct bloom *r=aggregateChildren(bl,c);
		bitset_inplace_union(current->b,r->b);

	}
	if(node->value->b!=current->b){
		printf("Lancia eccezione\n");
	}


	return node->value;
}


struct BFINode* splitRight(struct bloofi*bl,struct BFINode *current,struct BFINode *rightmost){

	struct BFINode *newNode;
	struct bloom *sampleFilter=current->value;
	struct bloom *zeroFilter=createZeroBloomFilter(sampleFilter);
	newNode=BFINode(zeroFilter,bl->order,bl->splitFull);

	struct BFINode *receivedRight;
	for(int i=bl->order+1;i<getSize(current->children);i++){
		receivedRight=insertRight(bl,false,newNode,getElement(current->children,i),rightmost);

	}
	current->children=removeLastHalf(current->children,bl->order+1);
	recomputeValue(current);

	if(current->parent!=NULL){
		receivedRight=insertRight(bl,true,current->parent,newNode,rightmost);

	}
	else{

		struct BFINode *newRoot;
		struct bloom *sampleFilter1=current->value;
		struct bloom *zeroFilter1=createZeroBloomFilter(sampleFilter1);
		newRoot=BFINode(zeroFilter1,bl->order,bl->splitFull);
		rightmost=insertRight(bl,false,newRoot,current,rightmost);
		rightmost=insertRight(bl,false,newRoot,newNode,rightmost);
		bl->root=newRoot;

	}
	if(current==rightmost){
		rightmost=newNode;
	}

	return rightmost;
}

struct BFINode* insertRight(struct bloofi *bl,bool isInBFI,struct BFINode *current,struct BFINode *newChild,struct BFINode *rightmost){

	//if(current->children==NULL){
		newList(&current->children);
	//}

	current->children=insertElement(current->children,newChild);
	newChild->parent=current;

	if(!isInBFI){
		or_bloom_filter(current->value,newChild->value);
	}

	if(isLeaf(newChild)){
		updateValueToTheRoot(current,newChild->value);
	}

	if(!needSplit(current)){
		return rightmost;
	}

	rightmost=splitRight(bl,current,rightmost);
	return rightmost;
}


list sort(list bf){
	return sortIterative(bf);
}

list sortIterative(list bf){

	clock_t t_start, t_end;
	double t_passed;
	t_start = clock();

	list sorted;
	newList(&sorted);

	struct bloom*first=getElement(bf,0);

	struct bloom *current=createZeroBloomFilter(first);

	struct bloom *closest;
	int closestIndex;

	while(!isEmptyList(bf)){
		closestIndex=findClosestBloom(current,bf);
		closest=getElement(bf,closestIndex);

		sorted=insertElement(sorted,closest);
		bf=deleteElementByIndex(bf,closestIndex);
		current=closest;
	}
	t_end = clock();

	t_passed = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
	printf("Elapsed time: %f seconds.\n", t_passed);
	return sorted;
}



int findClosestBloom(struct bloom *b,list bloomList){

	if(isEmptyList(bloomList))
		return -1;
	struct bloom *currentBloom;
	currentBloom=getElement(bloomList,0);
	double minDistance=computeHammingDistance(b,currentBloom);
    int minIndex=0;
    double currentDistance;
    for(int i=1;i<getSize(bloomList);i++){
    	currentBloom=getElement(bloomList,i);
    	currentDistance=computeHammingDistance(b,currentBloom);
    	if(currentDistance<minDistance){
    		minDistance=currentDistance;
    		minIndex=i;
    	}
    }
    return minIndex;
}
















































































/********************************************************/
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

 return getSize(bf->root->children);
}

list getBFListBloofi(struct bloofi *bf){

 return bf->bfList;
}
