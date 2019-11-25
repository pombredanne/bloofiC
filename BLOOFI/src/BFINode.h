#include "bloom.h"
//#include "listaBFINode.h"
#include <stdbool.h>
typedef struct BFINode *rifer;
typedef short boolean;

struct BFINode{
	struct bloom *value;
	int order;
	rifer parent;
	//listBFINode children;
	bool splitFull;
};


void BFINode(struct BFINode *bfn,struct bloom *value,int order,bool splitFull);
