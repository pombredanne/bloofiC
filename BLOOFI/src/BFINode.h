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
boolean FullList2(listBFINode l);
int ConfrontaList2(struct BFINode *a,struct BFINode *b);
void VisualizzaElementoLista2(struct BFINode *x);
void VisitList2(listBFINode l);
boolean EmptyList2(listBFINode l);
int GetSize2(listBFINode l);



struct BFINode{
	struct bloom *value;
	int order;
	rifer parent;
	listBFINode children;
	bool splitFull;
};





struct BFINode* BFINode(struct bloom *value,int order,bool splitFull);
bool isLeaf(struct BFINode *bfn);



