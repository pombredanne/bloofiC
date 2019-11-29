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
//#include "hashtable.h"

int main(void) {

//	struct bloom bf;
	//int numLettereDaInserire = 10;
	//char *lettereDaInserire = "Telecinesi";
	//char *lettereDaControllare= "Telecinesi";

	//puts("Testiamo il bloofi ;)");


	// piu vuoi stare sicuro di non avere collisioni(probabilità tende a zero)e ti crea un array piu grande(elevato numero di bit)
//	bloom_init(&bf,88099, 0.99f);
	//bloom_add(&bf, lettereDaInserire, numLettereDaInserire);
	//bloom_print(&bf);
	//printf("Risultato1:%d\n",bloom_check(&bf,lettereDaControllare,10));

	//bloom_add(&bf,"Idrolisi",8);
	//printf("Risultato2:%d\n",bloom_check(&bf,lettereDaControllare,10));

//	printf("Risultato3:%d\n",bloom_check(&bf,"Idrolisi",8));

//	printf("Risultato4:%d\n",bloom_check(&bf,"Cane",4));

	//bloom_add(&bf, "Cane",4);
	//printf("Risultato5:%d\n",bloom_check(&bf,"Cane",4));
	/*****************************************************/

	struct bloom b;
	struct bloom b2;
	struct bloom b3;
	struct bloom b4;
	struct bloofi bl;

	bloom_init(&b,88099, 0.5f);
//	bloom_print(&b);
	//bloom_init(&b2,48099, 0.5f);
	//bloom_init(&b3,28099, 0.5f);
	//bloom_init(&b4,68099, 0.5f);
	//BFINode(&bl,&b,15,true);
	//printf("prima\n");
	bloom_filter_index(&bl,5,&b,true);
	//printf("funzionaaaaa\n");
	//insertBloomFilter(&bl,&b2);
	//insertBloomFilter(&bl,&b3);
	//VisitList2(bl.root->children);
	//VisitList(bl.bfList);
	  //dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
	   //dummyItem->data = -1;
	   //dummyItem->key = -1;
	   //struct BFINode bfi1;
	   //struct BFINode bfi2;
	  // struct BFINode bfi3;
	  // struct BFINode *new;
	   //BFINode(&bfi1,&b,15,true);
	  // bfi1.children=NULL;
	   //BFINode(&bfi2,&b2,25,true);
	  // BFINode(&bfi3,&b3,35,true);

	  //bfi1.children=insertList2(bfi1.children,&bfi2);
	 //  bfi1.children=insertList2(bfi1.children,&bfi3);
	  // VisitList2(bfi1.children);
	  // insert(1, bfi1);
	   //insert(2, bfi2);

	//printf("funziona ancoraaaa\n");

	return EXIT_SUCCESS;
}
