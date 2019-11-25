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

int main(void) {

	//struct bloom bf;
	//int numLettereDaInserire = 10;
	//char *lettereDaInserire = "Telecinesi";
	//char *lettereDaControllare= "Telecinesi";

	//puts("Testiamo il bloofi ;)");


	// piu vuoi stare sicuro di non avere collisioni(probabilità tende a zero)e ti crea un array piu grande(elevato numero di bit)
	//bloom_init(&bf,88099, 0.99f);
	//bloom_add(&bf, lettereDaInserire, numLettereDaInserire);
	//bloom_print(&bf);
	//printf("Risultato1:%d\n",bloom_check(&bf,lettereDaControllare,10));

	//bloom_add(&bf,"Idrolisi",8);
	//printf("Risultato2:%d\n",bloom_check(&bf,lettereDaControllare,10));

//	printf("Risultato3:%d\n",bloom_check(&bf,"Idrolisi",8));

//	printf("Risultato4:%d\n",bloom_check(&bf,"Cane",4));

	//bloom_add(&bf, "Cane",4);
	//printf("Risultato5:%d\n",bloom_check(&bf,"Cane",4));

	//bloom_print(&bf);

	struct bloom b;
	//struct bloom b2;
	struct bloofi bl;
	bloom_init(&b,88099, 0.5f);
	//bloom_init(&b2,88099, 0.7f);
	//printf("%d\n",b.id);
	//printf("%d\n",b2.id);
	//bloom_filter_index(&bl,2,&b,true);

	bloom_filter_index(&bl,5,&b,true);
	//printf("%d\n",bl->root->order);
	printf("ORDERRRRR:%d\n",bl.order);
	return EXIT_SUCCESS;
}
