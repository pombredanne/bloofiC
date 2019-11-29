#include "BFINode.h"
#include <stdio.h>


void newList2(listBFINode *l){
	printf("Sto aggiornando il valore di list....\n");
	*l=NULL;
}

void VisitList2(listBFINode l){
	while(l!=NULL){
		VisualizzaElementoLista2(l->bf);
		l=l->next;
	}
}

int ConfrontaList2(struct BFINode *a,struct BFINode *b){
//confronta valore interno al bf
	if(a->value->bf==b->value->bf){
			return 0;
	}
	else {
		return 1;
	}

}
void VisualizzaElementoLista2(struct BFINode *x){

	bloom_print(x->value);

}

listBFINode insertList2(listBFINode l,struct BFINode *x){
	struct nodeL *temp;
	listBFINode p;
	p=l;
	if(!FullList2(l)){
		temp=(struct nodeL*)malloc(sizeof(struct nodeL));
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

boolean EmptyList2(listBFINode l){

	return(l==NULL);
}
//68 è il primo nella lista. Il next è 88
listBFINode DeleteList2(listBFINode l,struct BFINode *x){
	struct nodeL *temp;
	listBFINode p;
	listBFINode p2;
    p=l;
    p2=l;
	printf("VALORE:%d\n",EmptyList2(l));
	if(!EmptyList2(l))
		if(!ConfrontaList2(p->bf,x)){
			l=l->next;
			//free(p);
			return l;
		}
		p=p->next;
		while(p->next!=NULL){
			if(!ConfrontaList2(p->bf,x)){
				p2->next=p2->next->next;
				//free(p);
				break;
			}

				p2=p2->next;
				p=p->next;
		}
	return (l);
}

boolean FullList2(listBFINode l){
	struct nodeL *temp;
	temp=(struct nodeL*)malloc(sizeof(struct nodeL));
	if(temp==NULL)
		return 1;
	free(temp);
	return 0;
}

int GetSize2(listBFINode l){
	int conta=0;
	listBFINode p;
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

