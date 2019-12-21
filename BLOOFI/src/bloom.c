/*
 *  Copyright (c) 2012-2019, Jyri J. Virkki
 *  All rights reserved.
 *
 *  This file is under BSD license. See LICENSE file.
 */

/*
 * Refer to bloom.h for documentation on the public interfaces.
 */

#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

#include "bloom.h"
#include "murmur2/murmurhash2.h"

#define MAKESTRING(n) STRING(n)
#define STRING(n) #n

int lastID=0;
//corrisponde alla contains del BloomFilter in Java
inline static int test_bit_set_bit(bitset_t * buf,
                                   unsigned int x, int set_bit)
{
	//printf("size_bit_set:%d",buf->arraysize);
	if(set_bit){
		bitset_set_to_value(buf,x,true);
		return 0;
	}

	if(!set_bit)
		if(bitset_get(buf,x))
			return 1;

	return 0;
}


static int bloom_check_add(struct bloom * bloom,
                           const void * buffer, int len, int add)
{
  if (bloom->ready == 0) {
    printf("bloom at %p not initialized!\n", (void *)bloom);
    return -1;
  }

  int hits = 0;
  register unsigned int a = murmurhash2(buffer, len, 0x9747b28c);
  register unsigned int b = murmurhash2(buffer, len, a);
  register unsigned int x;
  register unsigned int i;

  for (i = 0; i < bloom->hashes; i++) {
    x = (a + i*b) % bloom->bits;
    if (test_bit_set_bit(bloom->b, x, add)) {
      hits++;
      //printf("Numero hits:%d",hits);
    } else if (!add) {
      // Don't care about the presence of all the bits. Just our own.
      return 0;
    }
  }
//printf("%d\n",bloom->hashes);
  if (hits == bloom->hashes) {
    return 1;                // 1 == element already in (or collision)
  }

  return 0;
}


int bloom_init_size(struct bloom * bloom, int entries, double error,
                    unsigned int cache_size)
{
  return bloom_init(bloom, entries, error);
}


int bloom_init(struct bloom * bloom, int entries, double error)
{

  bloom->numberOffElement=0;
  bloom->ready = 0;
  // semplicemente devi usare un numero molto alto di elementi da inserire
  if (entries < 1000 || error == 0) {

    return 1;
  }
  lastID++;
  bloom->id=lastID;
  bloom->entries = entries;
  bloom->error = error;

  double num= log(bloom->error);
  double denom = 0.480453013918201; // ln(2)^2
  bloom->bpe = -(num / denom);

  double dentries = (double)entries;
  bloom->bits = (int)(dentries * bloom->bpe);

  if (bloom->bits % 8) {
    bloom->bytes = (bloom->bits / 8) + 1;
  } else {
    bloom->bytes = bloom->bits / 8;
  }

  bloom->hashes = (int)ceil(0.693147180559945 * bloom->bpe);  // ln(2)
  //size_t capacity=(size_t)bloom->bits;
  bloom->b=bitset_create_with_capacity(bloom->bits);
 // bloom->bf = (unsigned char *)calloc(bloom->bytes, sizeof(unsigned char));
  if (bloom->b == NULL) {                                   // LCOV_EXCL_START
    return 1;
  }                                                          // LCOV_EXCL_STOP

  bloom->ready = 1;
  return 0;
}


int bloom_check(struct bloom * bloom, const void * buffer, int len)
{
  return bloom_check_add(bloom, buffer, len, 0);
}


int bloom_add(struct bloom * bloom, const void * buffer, int len)
{
  bloom->numberOffElement++;
  return bloom_check_add(bloom, buffer, len, 1);
}


void bloom_print(struct bloom * bloom)
{
  printf("bloom at %p\n", (void *)bloom);
  printf(" ->entries = %d\n", bloom->entries);
  printf(" ->error = %f\n", bloom->error);
  printf(" ->bits = %d\n", bloom->bits);
  printf(" ->bits per elem = %f\n", bloom->bpe);
  printf(" ->bytes = %d\n", bloom->bytes);
  printf(" ->hash functions = %d\n", bloom->hashes);
}
void print_bin(uint64_t integer)
{

    int i = CHAR_BIT * sizeof integer; /* however many bits are in an integer */
    while(i--) {
        putchar('0' + ((integer >> i) & 1));
    }
}

void bloom_print_supreme(struct bloom *bloom){

for(int i=0;i<bloom->b->arraysize;i++){
	printf("[%d]|",i);
	print_bin(bloom->b->array[i]);
	printf("|");
	if(i%2==0)
		printf("\n");
}

}


void bloom_free(struct bloom * bloom)
{
  bloom->numberOffElement=0;
  if (bloom->ready) {
    bitset_free(bloom->b);
    //free(bloom->b);
  }
  bloom->ready = 0;
}

void bloom_clear(struct bloom * bloom){

	bitset_clear(bloom->b);

}

int bloom_reset(struct bloom * bloom)
{
  if (!bloom->ready) return 1;
  bitset_clear(bloom->b);
 // memset(bloom->bf, 0, bloom->bytes);
  return 0;
}

void or_bloom_filter(struct bloom * bloom,struct bloom * filter){
	//printf("PrimoID:%d\n",bloom->id);
	//printf("SecondoID:%d\n",filter->id);
	bitset_inplace_union(bloom->b,filter->b);
	bloom->numberOffElement+=filter->numberOffElement;
}

int computeHammingDistance(struct bloom * bloom,struct bloom *filter){

	int x= xorcardinality(bloom->b,filter->b);
	return x;
}

double computeDistance(struct bloom *bloom,struct bloom *filter){

	if(bloom->metric==2)
		return computeJaccardDistance(bloom,filter);
	else if(bloom->metric==3)
		return computeCosineDistance(bloom,filter);
	return computeHammingDistance(bloom,filter);
}

double computeCosineDistance(struct bloom *bloom,struct bloom *filter){

	double distance=0;
	int maxLength=bloom->b->arraysize;
	bitset_t *otherBitSet = filter->b;
	if(otherBitSet->arraysize>maxLength){
		maxLength=otherBitSet->arraysize;
	}
	int countAND = andCardinality(bloom->b,filter->b);
	int count1 = cardinality(bloom->b);
	int count2 = cardinality(bloom->b);

	if(count1>0 || count2>0){
		distance=1.0-countAND/sqrt(count1)*sqrt(count2);
	}

	return distance;
}

double computeJaccardDistance(struct bloom *bloom,struct bloom *filter){

	double distance = 0;

	int maxLength = bloom->b->arraysize;
	bitset_t *otherBitSet = filter->b;
	if(otherBitSet->arraysize > maxLength){
		maxLength = otherBitSet->arraysize;
	}
	int countAND = andCardinality(bloom->b,filter->b);
	int countOR = orCardinality(bloom->b,filter->b);

	if(countOR > 0){
		distance = 1.0 -(double)countAND/countOR;
	}
	return distance;
}

int isFull(struct bloom *bloom){
	//printf("\n%d/%d\n",cardinality(bloom->b),bloom->bits);
	return cardinality(bloom->b)==bloom->bits;
}

const char * bloom_version()
{
  return MAKESTRING(BLOOM_VERSION);
}
