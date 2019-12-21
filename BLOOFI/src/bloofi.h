#include <stdbool.h>
#include <assert.h>
#include "hashtable.h"
#ifndef _BLOOFI_H
#define _BLOOFI_H

#ifdef __cplusplus
extern "C" {
#endif
#define SIZE 20
struct bloofi
{

  int order;
  bool splitFull;
  list bfList;
  struct DataItem*hashTable[SIZE];
  struct BFINode *root;
};

void bloom_filter_index(struct bloofi* bl, int order,struct bloom *sampleFilter,bool splitFull);
void bloom_filter_index2(struct bloofi* bl,list bList,int order,bool splitFull);
list findMatches(struct BFINode *node,const void*o);
struct BFINode *split(struct bloofi *bl,struct BFINode *current);
int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter);
void updateValueToTheRoot(struct BFINode *current,struct bloom *newValue);
int deleteFromIndex(struct bloofi* bl,int id);
void deleteNode(struct bloofi* bl,struct BFINode *childNode);
struct bloom* createZeroBloomFilter(struct bloom *filter);
struct BFINode* insertEntryIntoParent(struct bloofi *bl,struct BFINode *newChild,struct BFINode *node);
void recomputeValueToTheRoot(struct BFINode *current);
void redistribute(struct BFINode *node,struct BFINode *sibling,bool isRightSibling);
void merge(struct BFINode *node,struct BFINode *sibling,bool isRightSibling);
void validate(struct bloofi *bl);
struct BFINode* splitRight(struct bloofi*bl,struct BFINode *current,struct BFINode *rightmost);
struct bloom* aggregateChildren(struct bloofi *bl,struct BFINode *node);
void recomputeValueToTheRoot(struct BFINode *current);
struct BFINode* insertRight(struct bloofi *bl,bool isInBFI,struct BFINode *current,struct BFINode *newChild,struct BFINode *rightmost);
//list bulkload(struct bloofi *bl,list mbfList);
int* search(struct bloofi*bl,const void*o);
list searchBloomFilters(struct bloofi*bl,const void *o);
int findClosestBloom(struct bloom *bf,list bloomList);
int getHeightBloofi(struct bloofi *bf);
int getSizeBloofi(struct bloofi *bf);
int getBloomFilterSizeBloofi(struct bloofi *bf);
int getNbChildrenRootBloofi(struct bloofi *bf);
list getBFListBloofi(struct bloofi *bf);
void insertBloomFilter(struct bloofi *bl,struct bloom *b);
struct BFINode* insert2(struct bloofi *bl,struct BFINode *current,struct BFINode *newChild);
list sortIterative(list bf);
list sort(list bf);
#ifdef __cplusplus
}
#endif

#endif
