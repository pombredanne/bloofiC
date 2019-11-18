/*
 ============================================================================
 Name        : BLOOFI.c
 Author      : fab
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "bloom.h"

int main(void) {

	struct bloom bf;
	int numParoleDaInserire = 6;
	char *paroleDaInserire[] = {"Mimi","Coco","ArotaEScorta","Pippo","Pluto","Paperino"};
	char *paroleDaControllare[] = {"Mimi","Coco","ArotaEScorta","Paperino"};

	puts("Testiamo il bloofi ;)");

	//bf=malloc(sizeof(struct bloom));

	bloom_init(&bf, numParoleDaInserire, 0.3f);
	bloom_add(&bf, paroleDaInserire, numParoleDaInserire);
	bloom_print(&bf);
	bloom_check(&bf,paroleDaControllare,4);






	return EXIT_SUCCESS;
}
