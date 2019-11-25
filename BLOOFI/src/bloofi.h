/*
 *  Copyright (c) 2012-2017, Jyri J. Virkki
 *  All rights reserved.
 *
 *  This file is under BSD license. See LICENSE file.
 */

#include <stdbool.h>
#include "lista.h"
#include "BFINode.h"
//#include "hashtable.h"
//#include "listaBFINode.h"
#ifndef _BLOOFI_H
#define _BLOOFI_H

#ifdef __cplusplus
extern "C" {
#endif

struct bloofi
{

  int order;
  bool splitFull;
  list bfList;
  //hashtable_t *idMap;
  struct BFINode *root;
};

void bloom_filter_index(struct bloofi* bl, int order,struct bloom* sampleFilter,bool splitFull);
void bloom_filter_index2(struct bloofi* bl,list bfList,int order,bool splitFull);
int updateIndex(struct bloofi* bl,struct bloom *newBloomFilter);
int deleteFromIndex(struct bloofi* bl,int id);
void deleteNode(struct bloofi *bl,struct BFINode *childNode);
//void redistribute(struct BFINode node,struct BFINode sibling,bool isRightSibling);
//void merge(struct BFINode node,struct BFINode sibling,bool isRightSibling);
//list bulkload(list mbfList);
//list searchBloomFilters(const void *buf);

#ifdef __cplusplus
}
#endif

#endif
