typedef short boolean;

struct nodeList{

	void *bf;
	struct nodeList *next;
	//int size;
};

typedef struct nodeList*list;
void newList(list*l);
list insertElement(list l,void *x);
boolean isFullList(list l);
boolean isEmptyList(list l);
int getSize(list l);
void* getElement(list l,int index);
int compareElement(void *a,void *b);
list addAll(list l,list new);
list insertElementByIndex(list l,int index,void *newChild);
list deleteElement(list l,void *x);
list deleteElementByIndex(list l,int index);
list deleteElementByIndexNode(list l,int index);
int indexOfElement(list l,void *bfn);
list removeLastHalf(list l,int from);
