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

	if(a->b==b->b){
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

list addAll(list l,list new){
	//bloom_print(l->bf);
	list p=l;
	if(l==NULL){
		printf("go1\n");
		return new;
	}
	while(p->next!=NULL){
		printf("go2\n");
		p=p->next;
	}

	if(p->next==NULL){
		printf("go3\n");
		if(new!=NULL)
			p->next=new;
	}
	//bloom_print(l->bf);
	return l;
}


//implementazione che torna per valore(non per riferimento)
struct bloom* getElement(list l,int index){
list p;
p=l;
struct bloom *temp;
int conta=0;
//se la lista è vuota
if(l==NULL)
	return NULL;
//ci sta un solo elemento
if(p->next==NULL){
	if(conta==index){
		//printf(":%d\n",p->bf->order);
		return p->bf;
		//bloom_init(temp,88099, 0.5f);
		//temp=BFINode(p->bf->value,p->bf->order,p->bf->splitFull);
		//printf("Order temp:%d\n",temp->order);
		//return temp;
	}
	else return NULL;
}
printf("ci sono più elementiiii\n");
//ci sono almeno due elementi
while(p->next!=NULL){
	if(conta==index){
		//temp=BFINode(p->bf->value,p->bf->order,p->bf->splitFull);
		//return temp;
		return p->bf;
	}
	p=p->next;
	conta++;
}
printf("Conta:%d e index:%d\n",conta,index);
//controllo su ultimo elemento
if(p->next==NULL)
	if(conta==index){
		//temp=BFINode(p->bf->value,p->bf->order,p->bf->splitFull);
		//return temp;
		return p->bf;
	}
return NULL;
}


