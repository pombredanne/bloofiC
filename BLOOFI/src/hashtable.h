#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BFINode.h"

#define SIZE 20

struct DataItem {
   struct BFINode *data;
   int key;
};

//struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key);

struct BFINode *searchHash(struct DataItem** hashArray,int key);

void insert(struct DataItem** hashArray,int key,struct BFINode* data);

void delete(struct DataItem** hashArray,int key);

void display(struct DataItem** hashArray);

//int main() {
  // dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
   //dummyItem->data = -1;
   //dummyItem->key = -1;
   //struct BFINode *b1;
   //struct BFINode *b2;
   //insert(1, b1);
   //insert(2, b2);
   //insert(42, 80);
   //insert(4, 25);
   //insert(12, 44);
   //insert(14, 32);
   //insert(17, 11);
   //insert(13, 78);
   //insert(37, 97);

   //display();
   //item = search(37);

   //if(item != NULL) {
     // printf("Element found: %d\n", item->data);
   //} else {
     // printf("Element not found\n");
   //}

   //delete(item);
   //item = search(37);

   //if(item != NULL) {
     // printf("Element found: %d\n", item->data);
  // } else {
    //  printf("Element not found\n");
  // }
//}
