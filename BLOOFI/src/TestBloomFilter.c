/*
 ============================================================================
 Name        : BLOOFI2.c
 Author      : fab
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


// Con add si inserisce un elemento per volta

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bloom.h"
#include "bloofi.h"
#include "time.h"
//#include "list.h"
int main(void) {




//listBFINode l;
//newList2(&l);
struct bloom bloom;
struct bloom bloom2;
struct bloom bloom3;
struct bloom bloom4;
struct bloom bloom5;
struct bloom bloom6;
struct bloom bloom7;
struct bloom bloom8;
struct bloom bloom9;
struct bloofi bl;
bloom_init(&bloom,10000,0.5);
bloom_filter_index(&bl,2,&bloom,false);//radice id 2
bloom_init(&bloom2,10000,0.5);
bloom_init(&bloom3,10000,0.5);
bloom_init(&bloom4,10000,0.5);
bloom_init(&bloom5,10000,0.5);
bloom_init(&bloom6,10000,0.5);
bloom_init(&bloom7,10000,0.5);
insertBloomFilter(&bl,&bloom2);//inserisco id 3
insertBloomFilter(&bl,&bloom3);//inserisco id 4
insertBloomFilter(&bl,&bloom4);//inserisco id 5
insertBloomFilter(&bl,&bloom5);//inserisco id 6
insertBloomFilter(&bl,&bloom6);//inserisco id 7
insertBloomFilter(&bl,&bloom7);//inserisco id 8
printf("FINE SESTO INSERIMENTO\n");
printf("Mamma root:%d\n",bl.root->value->id);


bloom_init(&bloom8,10000,0.5);
insertBloomFilter(&bl,&bloom8);//inserisco id 11

bloom_init(&bloom9,10000,0.5);
insertBloomFilter(&bl,&bloom9);//inserisco id 13
struct BFINode *mah=getElement(bl.root->children,2);
int size2=getSize(mah->children);
printf("DIM:%d\n",size2);
deleteFromIndex(&bl,6);
printf("Ultimissima size root:%d\n",getSize(bl.root->children));
//struct BFINode *test1=getElement2(bl.root->children,2);
//printf("id da valutare:%d\n",test1->value->id);


struct BFINode *test1=getElement(bl.root->children,0);
struct BFINode *test2=getElement(bl.root->children,1);
//struct BFINode *test3=getElement2(bl.root->children,2);
struct BFINode *test4=getElement(test1->children,0);
struct BFINode *test5=getElement(test1->children,1);
struct BFINode *test6=getElement(test1->children,2);
struct BFINode *test7=getElement(test1->children,3);
struct BFINode *test8=getElement(test2->children,0);
struct BFINode *test9=getElement(test2->children,1);
struct BFINode *test10=getElement(test2->children,2);
printf("DIM1:%d\n",getSize(test1->children));
printf("DIM2:%d\n",getSize(test2->children));
printf("Id root:%d\n",bl.root->value->id);
printf("Id nummber 1:%d\n",test1->value->id);
printf("Id nummber 2:%d\n",test2->value->id);
//printf("Id nummber 3:%d\n",test3->value->id);
printf("Id nummber 4:%d\n",test4->value->id);
printf("Id nummber 5:%d\n",test5->value->id);
printf("Id nummber 6:%d\n",test6->value->id);
printf("Id nummber 7:%d\n",test7->value->id);
printf("Id nummber 8:%d\n",test8->value->id);
printf("Id nummber 9:%d\n",test9->value->id);
printf("Id nummber 10:%d\n",test10->value->id);



//struct BFINode *b1=getElement2(bl.root->children,0);
//struct BFINode *b2=getElement2(bl.root->children,1);
//struct BFINode *b3=getElement2(bl.root->children,2);
//struct BFINode *b4=getElement2(bl.root->children,3);
//printf("Size:%d\n",GetSize2(bl.root->children));
//printf("ID ROOT:%d\n",bl.root->value->id);
//printf("ID bloom1:%d\n",b1->value->id);
//printf("ID bloom2:%d\n",b2->value->id);
//printf("ID bloom3:%d\n",b3->value->id);
//printf("ID bloom4:%d\n",b4->value->id);

//struct BFINode *n1=getElement2(bl.root->children,0);
//struct BFINode *n2=getElement2(bl.root->children,1);
//printf("ID bloom:%d\n",bloom.id);
//printf("ID b1:%d\n",n1->value->id);
//printf("ID b2:%d\n",n2->value->id);
//VisitList(bl.bfList);

printf("SIZE_BLOOM:%d\n",getSize(bl.bfList));
//printf("ID BLOOM_1:%d\n",getElement(bl.bfList,0)->id);
//printf("ID BLOOM_2:%d\n",getElement(bl.bfList,1)->id);
//printf("ID BLOOM_3:%d\n",getElement(bl.bfList,2)->id);
//printf("ID BLOOM_4:%d\n",getElement(bl.bfList,3)->id);
//printf("ID BLOOM_5:%d\n",getElement(bl.bfList,4)->id);
//printf("ID BLOOM_6:%d\n",getElement(bl.bfList,5)->id);
//printf("ID BLOOM_7:%d\n",getElement(bl.bfList,6)->id);
//printf("ID BLOOM_8:%d\n",getElement(bl.bfList,7)->id);
//struct BFINode *b=getElement2(bl.root->children,0);
//printf("ID nodo rimasto:%d\n",b->value->id);
//struct BFINode *b2=BFINode(&bloom2,2,false);



printf("Test della lista generica...\n");


/*
listG l;
newList3(&l);
struct bloom *b1;
b1=malloc(sizeof(struct bloom));
bloom_init(b1,10000,0.5);
struct bloom *b2;
b2=malloc(sizeof(struct bloom));
bloom_init(b2,10000,0.5);
struct BFINode *node=BFINode(b1,2,false);
struct BFINode *node2=BFINode(b2,2,false);
l=insertList3(l,node);
l=insertList3(l,node2);
l=DeleteList3(l,node);
struct BFINode *node3=getElement3(l,0);
printf("Id del nodo inserito:%d\n",node3->value->id);

*/







	return EXIT_SUCCESS;
}
