#include "bloom.h"
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
typedef struct BFINode *rifer;

struct BFINode{
	struct bloom *value;
	int order;
	rifer parent;
	list children;
	bool splitFull;
};


struct BFINode* BFINode(struct bloom *value,int order,bool splitFull);
bool isLeaf(struct BFINode *bfn);
int getLevel(struct BFINode *bfn);
int getTreeSize(struct BFINode *bfn);
int getBloomFilterSize(struct BFINode *bfn);
struct BFINode* findClosest(struct BFINode *bfn,list nodeList);
int findClosestIndex(struct BFINode *b,list nodeList);
void recomputeValue(struct BFINode *bfn);
bool needSplit(struct BFINode *bfn);
bool needMerge(struct BFINode *bfn);
bool canRedistribute(struct BFINode *bfn);

