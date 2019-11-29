#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void newList(list*l){
	*l=NULL;
	//printf("ciao\n");

}

void VisitList(list l){

	while(l!=NULL){
		VisualizzaElementoLista(l->bf);
		l=l->next;
	}
}

int ConfrontaList(struct bloom *a,struct bloom *b){

	if(a->bf==b->bf){
			return 0;
	}
	else {
		return 1;
	}

}
void VisualizzaElementoLista(struct bloom *x){

	bloom_print(x);

}

list insertList(list l,struct bloom *x){
//printf("Entro nella insert\n");
	struct node *temp;
	list p;
	p=l;
	if(!FullList(l)){
		temp=(struct node*)malloc(sizeof(struct node));
		temp->bf=x;
		if(l==NULL){
			temp->next=NULL;
			l=temp;
		}else{
			while(p->next!=NULL){
				p=p->next;
			}
			if(p->next==NULL){
				p->next=temp;
				temp->next=NULL;
			}
		}

	}
	return l;
}

boolean EmptyList(list l){

	return(l==NULL);
}
//68 è il primo nella lista. Il next è 88
list DeleteList(list l,struct bloom *x){
	struct node *temp;
	list p;
	list p2;
    p=l;
    p2=l;
	printf("VALORE:%d\n",EmptyList(l));
	if(!EmptyList(l))
		if(!ConfrontaList(p->bf,x)){
			l=l->next;
			//free(p);
			return l;
		}
		p=p->next;
		while(p->next!=NULL){
			if(!ConfrontaList(p->bf,x)){
				p2->next=p2->next->next;
				//free(p);
				break;
			}

				p2=p2->next;
				p=p->next;
		}
	return (l);
}

boolean FullList(list l){
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
		return 1;
	free(temp);
	return 0;
}

struct bloom* getFirst(list l){

	return l->bf;
}

int GetSize(list l){
	int conta=0;
	list p;
	if(l==NULL)
		return 0;
	else{
	p=l;
	//if(p->next==NULL)
		//return 1;
	   while(p->next!=NULL){
		    conta++;
		    p=p->next;
	   }
	}
	return conta+1;
}

