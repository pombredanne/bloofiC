/*
 *  Copyright (c) 2012-2017, Jyri J. Virkki
 *  All rights reserved.
 *
 *  This file is under BSD license. See LICENSE file.
 */

#include <stdbool.h>
#include "lista.h"
//#include "BFINode.h"
#include "hashtable.h"
//#include "listaBFINode.h"
#ifndef _BLOOFI_H
#define _BLOOFI_H

#ifdef __cplusplus
extern "C" {
#endif
//#define SIZE 20
struct bloofi
{

  int order;
  bool splitFull;
  list bfList;
  struct DataItem*hashTable[SIZE];
  struct BFINode *root;
};
void bloom_filter_index(struct bloofi* bl, int order,struct bloom sampleFilter,bool splitFull);
void bloom_filter_index2(struct bloofi* bl,int order,bool splitFull);
list findMatches(struct BFINode *node,const void*o);
int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter);
void updateValueToTheRoot(struct BFINode *current,struct bloom *newValue);
int deleteFromIndex(struct bloofi* bl,int id);
void deleteNode(struct bloofi *bl,struct BFINode *childNode);
struct bloom createZeroBloomFilter(struct bloom *filter);
struct BFINode* insertEntryIntoParent(struct BFINode *newChild,struct BFINode *node);
//void redistribute(struct BFINode node,struct BFINode sibling,bool isRightSibling);
//void merge(struct BFINode node,struct BFINode sibling,bool isRightSibling);
//list bulkload(struct bloofi *bl,list mbfList);
//list searchBloomFilters(const void *buf);
int getHeightBloofi(struct bloofi *bf);
int getSizeBloofi(struct bloofi *bf);
int getBloomFilterSizeBloofi(struct bloofi *bf);
int getNbChildrenRootBloofi(struct bloofi *bf);
list getBFListBloofi(struct bloofi *bf);

void insertBloomFilter(struct bloofi *bl,struct bloom *b);
struct BFINode* insert2(struct bloofi *bl,struct BFINode *current,struct BFINode *newChild);
#ifdef __cplusplus
}
#endif

#endif
