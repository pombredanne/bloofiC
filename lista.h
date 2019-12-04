#include "bloom.h"
typedef short boolean;
struct node{

	struct bloom *bf;
	struct node *next;
	//int size;
};
typedef struct node*list;
struct bloom* getFirst(list l);
void newList(list*l);
list insertList(list l,struct bloom *x);
list DeleteList(list l,struct bloom *x);
boolean FullList(list l);
int ConfrontaList(struct bloom *a,struct bloom *b);
void VisualizzaElementoLista(struct bloom *x);
void VisitList(list l);
boolean EmptyList(list l);
int GetSize(list l);
list addAll(list l,list new);
struct bloom* getElement(list l,int index);

