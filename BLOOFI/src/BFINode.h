#include "bloom.h"
//#include "listaBFINode.h"
#include <stdbool.h>
#include <stdlib.h>
typedef struct BFINode *rifer;
typedef short boolean;
//typedef struct BFINode item;
struct nodeL{

	struct BFINode *bf;
	struct nodeL *next;
	//int size;
};

typedef struct nodeL*listBFINode;

void newList2(listBFINode *l);
listBFINode insertList2(listBFINode l,struct BFINode *x);
listBFINode DeleteList2(listBFINode l,struct BFINode *x);
listBFINode DeleteListbyIndex2(listBFINode l,int index);
boolean FullList2(listBFINode l);
int ConfrontaList2(struct BFINode *a,struct BFINode *b);
void VisualizzaElementoLista2(struct BFINode *x);
void VisitList2(listBFINode l);
boolean EmptyList2(listBFINode l);
struct BFINode* getFirst2(listBFINode l);
struct BFINode* getElement2(listBFINode l,int index);
int GetSize2(listBFINode l);
listBFINode insertList2ByIndex(listBFINode l,int index,struct BFINode *newChild);
int indexOfElement2(listBFINode l,struct BFINode *bfn);


struct BFINode{
	struct bloom *value;
	int order;
	rifer parent;
	listBFINode children;
	bool splitFull;
};





struct BFINode* BFINode(struct bloom *value,int order,bool splitFull);
bool isLeaf(struct BFINode *bfn);
int getLevel(struct BFINode *bfn);
int getTreeSize(struct BFINode *bfn);
int getBloomFilterSize(struct BFINode *bfn);
struct BFINode* findClosest(struct BFINode *bfn,listBFINode nodeList);
int findClosestIndex(struct BFINode *b,listBFINode nodeList);
void recomputeValue(struct BFINode *bfn);
bool needSplit(struct BFINode *bfn);
bool needMerge(struct BFINode *bfn);


