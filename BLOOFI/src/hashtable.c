#include "hashtable.h"

int hashCode(int key) {

   return key % SIZE;
}

struct BFINode *searchHash(struct DataItem** hashArray,int key){
   //get the hash
   int hashIndex = hashCode(key);
	//int hashIndex=1;
   //printf("Hash index:%d\n",hashIndex);
   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
	   //printf("ORDER ELEMENTO HASH:%d\n",hashArray[hashIndex]->data->order);
	   //printf("KEY:%d\n",key);
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]->data;


      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

void insert(struct DataItem** hashArray,int key,struct BFINode* data) {
	//printf("ORDER NELLA INSERT:%d\n",data->order);
   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;
   item->key = key;

   //get the hash
   int hashIndex = hashCode(key);
   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }
  // printf("Sto inserendo all indice:%d\n",hashIndex);
   hashArray[hashIndex] = item;

}

void delete(struct DataItem** hashArray,int key) {
  // int key = item->key;
   //get the hash
   int hashIndex = hashCode(key);
   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
      if(hashArray[hashIndex]->key == key) {
        // struct DataItem* temp = hashArray[hashIndex];
         //assign a dummy item at deleted position
         hashArray[hashIndex] = NULL;
         //return temp;
      }

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   //return NULL;
}
void display(struct DataItem** hashArray){
   int i = 0;

   for(i = 0; i<SIZE; i++) {

      if(hashArray[i] != NULL)
         printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data->order);
      else
         printf(" ~~ ");
   }

   printf("\n");
}
