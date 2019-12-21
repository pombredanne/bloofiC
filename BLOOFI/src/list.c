#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void newList(list*l){

	*l=NULL;

}

int compareElement(void *a,void *b){

	if(a==b){

			return 0;
	}
	else {

		return 1;
	}

}


list insertElement(list l,void *x){

	struct nodeList *temp;
	list p;
	p=l;
	if(!isFullList(l)){
		temp=malloc(sizeof(struct nodeList));
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

boolean isEmptyList(list l){

	return(l==NULL);
}

boolean isFullList(list l){
	struct nodeList *temp;
	temp=malloc(sizeof(struct nodeList));
	if(temp==NULL)
		return 1;
	free(temp);
	return 0;
}


int getSize(list l){
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


void* getElement(list l,int index){
list p;
p=l;
void *temp;
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

//controllo su ultimo elemento
if(p->next==NULL)
	if(conta==index){
		//temp=BFINode(p->bf->value,p->bf->order,p->bf->splitFull);
		//return temp;
		return p->bf;
	}
return NULL;
}

list insertElementByIndex(list l,int index,void *newChild){

	struct nodeList *newList;
	struct nodeList *prec;
	struct nodeList *l2;
	prec=malloc(sizeof(struct nodeList));
	int pos=0;
	if(index==0){
		newList=malloc(sizeof(struct nodeList));
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
		l2=malloc(sizeof(struct nodeList));
		l2->bf=newChild;
		l2->next=prec->next;
		prec->next=l2;

	}
return l;
}

list deleteElement(list l,void *x){

	struct nodeList *temp;
	list p;
	list p2;
    p=l;
    p2=l;

	//elimino primo elemento
	if(!isEmptyList(l)){
		if(!compareElement(l->bf,x)){
			l=l->next;
			//free(p);
			return l;
		}

		p=p->next;
		while(p->next!=NULL){
			if(!compareElement(p->bf,x)){
				p2->next=p2->next->next;
				//free(p);
				break;
			}

				p2=p2->next;
				p=p->next;
		}
		if(p->next==NULL)
			if(!compareElement(p->bf,x))
				p2->next=NULL;
	}
	return (l);
}

list deleteElementByIndex(list l,int index){
	int count=0;
	struct nodeList *temp;
	list p;
	list p2;
    p=l;
    p2=l;

	//elimino primo elemento
	if(!isEmptyList(l)){
		if(count==index){
			l=l->next;

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


list deleteElementByIndexNode(list l,int index){
		int count=0;
		struct nodeList *temp;
		list p;
		list p2;
	    p=l;
	    p2=l;

		//elimino primo elemento
		if(!isEmptyList(l)){
			if(count==index){
				//struct BFINode *newNode=BFINode(l->bf->value,l->bf->order,l->bf->splitFull);
				l=l->next;
				return l;
				//return newNode;
				printf("già tornato\n");
				//free(p);

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
return l;
}

int indexOfElement(list l,void *bfn){

	int pos=0;
	int found=0;
	list p=l;
	if(l==NULL)
		return -1;
	while(!isEmptyList(p)&&!found){

		if(!compareElement(p->bf,bfn))
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

list removeLastHalf(list l,int from){

	list p;
	p=l;
	int count=0;
	while(p->next!=NULL){
		if(count+1==from){
			p->next=NULL;
			break;
		}
	p=p->next;
	count++;

	}
	return l;
}

list addAll(list l,list new){

	list p=l;
	if(l==NULL){

		return new;
	}
	while(p->next!=NULL){

		p=p->next;
	}

	if(p->next==NULL){

		if(new!=NULL)
			p->next=new;
	}
	//bloom_print(l->bf);
	return l;
}



