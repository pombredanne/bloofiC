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
	if(a->value->b==b->value->b){
			printf("siiiiiii\n");
			return 0;
	}
	else {
		printf("nadaaaa\n");
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
struct BFINode* getFirst2(listBFINode l){

	return l->bf;
}

//implementazione che torna per valore(non per riferimento)
struct BFINode* getElement2(listBFINode l,int index){
listBFINode p;
p=l;
struct BFINode *temp;
int conta=0;
//se la lista è vuota
if(l==NULL)
	return NULL;
//ci sta un solo elemento
if(p->next==NULL){
	if(conta==index){
		printf(":%d\n",p->bf->order);
		//return p->bf;
		temp=BFINode(p->bf->value,p->bf->order,p->bf->splitFull);
		temp->parent=p->bf->parent;
		//printf("Order temp:%d\n",temp->order);
		return temp;
	}
	else return NULL;
}
printf("ci sono più elementiiii\n");
//ci sono almeno due elementi
while(p->next!=NULL){
	if(conta==index){
		temp=BFINode(p->bf->value,p->bf->order,p->bf->splitFull);
		temp->parent=p->bf->parent;
		return temp;
		//return p->bf;
	}
	p=p->next;
	conta++;
}
printf("Conta:%d e index:%d\n",conta,index);
//controllo su ultimo elemento
if(p->next==NULL)
	if(conta==index){
		temp=BFINode(p->bf->value,p->bf->order,p->bf->splitFull);
		return temp;
		//return p->bf;
	}
return NULL;
}

listBFINode insertList2ByIndex(listBFINode l,int index,struct BFINode *newChild){

	struct nodeL *newList;
	struct nodeL *prec;
	struct nodeL *l2;
	prec=malloc(sizeof(struct nodeL));
	int pos=0;
	if(index==0){
		newList=malloc(sizeof(struct nodeL));
		newList->bf=newChild;
		newList->next=l;
		l=newList;
		return l;
	}
	prec=l;
	while(pos<index-1&&prec!=NULL){
		prec=prec->next;
		pos++;
	}
	if(prec!=NULL){
		l2=malloc(sizeof(struct nodeL));
		l2->bf=newChild;
		l2->next=prec->next;
		prec->next=l2;

	}
return l;
}

//68 è il primo nella lista. Il next è 88
listBFINode DeleteList2(listBFINode l,struct BFINode *x){
	printf("Order1:%d\n",l->bf->order);
	printf("Order2:%d\n",x->order);
	struct nodeL *temp;
	listBFINode p;
	listBFINode p2;
    p=l;
    p2=l;
	printf("VALORE:%d\n",EmptyList2(l));
	//elimino primo elemento
	if(!EmptyList2(l)){
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
		if(p->next==NULL)
			if(!ConfrontaList2(p->bf,x))
				p2->next=NULL;
	}
	return (l);
}


//68 è il primo nella lista. Il next è 88
listBFINode DeleteListbyIndex2(listBFINode l,int index){
	int count=0;
	struct nodeL *temp;
	listBFINode p;
	listBFINode p2;
    p=l;
    p2=l;
	printf("VALORE:%d\n",EmptyList2(l));
	//elimino primo elemento
	if(!EmptyList2(l)){
		if(count==index){
			l=l->next;
			printf("vaaaaaaa\n");
			//free(p);
			return l;
		}
		count++;
		p=p->next;
		while(p->next!=NULL){
			if(count==index){
				p2->next=p2->next->next;
				//free(p);
				break;
			}
				count++;
				p2=p2->next;
				p=p->next;
		}
		if(p->next==NULL)
			if(count==index)
				p2->next=NULL;
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

int indexOfElement2(listBFINode l,struct BFINode *bfn){
	printf("terminazione\n");
	int pos=0;
	int found=0;
	listBFINode p=l;
	if(l==NULL)
		return -1;
	while(!EmptyList2(p)&&!found){
		printf("dentro\n");
		if(!ConfrontaList2(p->bf,bfn))
			found=1;
		else{
			pos++;
			p=p->next;
		}
	}
	if(!found)
		return -1;

	return pos;
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

listBFINode removeLastHalf(listBFINode l,int from){

	listBFINode p;
	p=l;
	int count=0;
	while(p->next!=NULL){
		if(count+1==from){
			p->next=NULL;
			break;
		}
	p=p->next;
	count++;
	printf("This is count:%d\n",count);
	}
	return l;
}






