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
	struct bloom b1;
	struct bloom b2;
	struct bloom b3;
	struct bloom b4;
	struct bloom b5;
	struct bloofi bl;
	bloom_init(&b,88099, 0.5f);
	bloom_init(&b1,78099, 0.5f);
	bloom_init(&b2,48099, 0.5f);
	bloom_init(&b3,68099, 0.5f);
	bloom_init(&b4,18099, 0.5f);
	bloom_init(&b5,28099, 0.5f);
	bloom_add(&b1, "Cane",4);
	bloom_add(&b2, "Gatto",5);
	bloom_add(&b3, "Mela",4);
	bloom_add(&b4, "Pera",4);
	//bloom_add(&b4, "Siiii",5);
	//bloom_add(&b4, "Cia",3);
	//bloom_add(&b4, "Mamma",5);
	bloom_add(&b5, "Banana",6);
	struct BFINode *bfi=BFINode(&b,5,true);
	struct BFINode *bfi1=BFINode(&b1,15,true);
	struct BFINode *bf2=BFINode(&b2,25,true);
	struct BFINode *bf3=BFINode(&b3,35,true);
	struct BFINode *bf4=BFINode(&b4,45,true);
	struct BFINode *bf5=BFINode(&b5,55,true);
	or_bloom_filter(&b,&b4);
	//or_bloom_filter(&b,&b2);
	//or_bloom_filter(&b1,&b3);
	//or_bloom_filter(&b1,&b4);
	//or_bloom_filter(&b2,&b5);
	list l=findMatches(bfi,"Pera");
	VisitList(l);
	printf("%d\n",bloom_check(&b,"Pera",4));
	//bloom_filter_index(&bl,5,b,true);
	//insertBloomFilter(&bl,&b2);
	//insertBloomFilter(&bl,&b3);
	//list lista;
	//list lista2;
	//newList(&lista2);
	//newList(&lista);
	//lista=insertList(lista,&b2);
	//lista=insertList(lista,&b3);
	//lista2=insertList(lista2,&b4);
	//lista2=insertList(lista2,&b5);
	//lista=addAll(lista,lista2);
	//VisitList(lista);
	//insertBloomFilter(&bl,&b2);
	//insertBloomFilter(&bl,&b3);
	//VisitList2(bl.root->children);
	//updateIndex
//	bloom_print(&b);
	//dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
	//struct BFINode *bfi1=BFINode(&b2,15,true);
	//struct BFINode *bfi2=BFINode(&b3,25,true);
	//struct BFINode *bfi3=BFINode(&b4,35,true);
	//struct BFINode *bfi4=BFINode(&b5,45,true);
	//bfi1->children=insertList2(bfi1->children,bfi2);
	//bfi1->children=insertList2(bfi1->children,bfi3);
	//bfi2->parent=bfi1;
	//bfi3->parent=bfi1;
	//VisitList2(bfi1->children);
	//VisitList2(bfi3->parent->children);
	//struct BFINode *boh=insertEntryIntoParent(bfi4,bfi2);
	//VisitList2(bfi1->children);
	//bl.root->children=insertList2(bl.root->children,bfi2);
	//int indice=indexOfElement2(bl.root->children,bfi2);
	//printf("Indice:%d\n",indice);
	//printf("%d\n",getTreeSize(bl.root));
	//struct BFINode *bfi4=findClosest(bl.root,bl.root->children);
	//printf("Order closest:%d\n",bfi4->order);
	//struct BFINode *bfi1=BFINode(&b2,15,true);
	//struct BFINode *bfi2=BFINode(&b3,25,true);
	//struct BFINode *bfi3=BFINode(&b4,35,true);
	//bl.root->children=insertList2(bl.root->children,bfi1);
	//bl.root->children=insertList2(bl.root->children,bfi2);
	//bl.root->children=insertList2(bl.root->children,bfi3);
	//bl.root->children=insertList2ByIndex(bl.root->children,2,bfi3);
	//bl.root->children=DeleteListbyIndex2(bl.root->children,2);
	//bl.root->children=insertList2(bl.root->children,bfi3);
	//VisitList2(bl.root->children);
	//struct BFINode *new;
	//new=getElement2(bl.root->children,0);
	//bfi1->order=40;
	//printf("This order:%d\n",new->order);
	//printf("ORDER:%d\n",new->childr);
	//insert(1, bfi1);
	//display();
	//bloom_init(&b3,28099, 0.5f);
	//bloom_init(&b4,68099, 0.5f);
	//BFINode(&bl,&b,15,true);
	//printf("prima\n");
	//list bfList;
	//newList(&bfList);
	//bloom_filter_index2(&bl,6,&bfList,true);
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
	//hashArray[20];
	//struct bloofi bl;
	//bloom_filter_index2(&bl,13,true);
	//struct DataItem* hashA[SIZE]={NULL};
	//struct bloom b;
	//struct bloom b2;
	//bloom_init(&b,88099, 0.5f);
	//bloom_init(&b2,88099, 0.5f);
	//struct BFINode *bi1=BFINode(&b,5,true);
	//struct BFINode *bi2=BFINode(&b,10,true);
	//struct DataItem* item1;
	//struct DataItem* item2;
	//item1=(struct DataItem*) malloc(sizeof(struct DataItem));
	//item2=(struct DataItem*) malloc(sizeof(struct DataItem));
	//item1->data=bi1;
	//item1->key=1;
	//item2->data=bi2;
	//item2->key=2;
	//insert(hashA,1,item1->data);
	//insert(2,item2->data);

	//struct BFINode *bi3=search(item1->key);
	//printf("Order nodo:%d\n",bi3->order);
	 //dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
	 //dummyItem->data = NULL;
	 //dummyItem->key = -1;
	//delete(bi1);
	//display(hashA);
	return EXIT_SUCCESS;
}
