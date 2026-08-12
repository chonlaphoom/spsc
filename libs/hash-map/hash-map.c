#include "hash-map.h"
#include <stdio.h>
#include <stdlib.h>

static int hash(int key) { return key % CAP; }

MyHashMap *hashMapCreate(void) {
  return (MyHashMap *)calloc(1, sizeof(MyHashMap));
}

void hashMapPut(MyHashMap *obj, int key, int value) {
  if (obj == NULL || key < 0)
    return;
  int idx = hash(key);
  struct Node *current = obj->bucket[idx];
  while (current != NULL) {
    if (current->key == key) {
      current->value = value;
      return;
    }
    current = current->next;
  }
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL)
    return;
  newNode->key = key;
  newNode->value = value;
  newNode->next = obj->bucket[idx];
  obj->bucket[idx] = newNode;
}

int hashMapGet(MyHashMap *obj, int key) {
  if (obj == NULL || key < 0)
    return -1;
  struct Node *current = obj->bucket[hash(key)];
  while (current != NULL) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }
  return -1;
}

void hashMapRemove(MyHashMap *obj, int key) {
  if (obj == NULL || key < 0)
    return;
  int idx = hash(key);
  struct Node *current = obj->bucket[idx];
  if (current == NULL)
    return;
  struct Node *prev = NULL;
  while (current != NULL) {
    if (current->key == key) {
      if (prev == NULL) {
        obj->bucket[idx] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}

void hashMapFree(MyHashMap *obj) {
  if (obj == NULL)
    return;
  for (int i = 0; i < CAP; i++) {
    struct Node *current = obj->bucket[i];
    while (current != NULL) {
      struct Node *temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(obj);
}

int main(void) {
  MyHashMap *map = hashMapCreate();
  hashMapPut(map, 1, 10);
  hashMapPut(map, 2, 20);
  hashMapPut(map, 3, 30);
  printf("Value for key 1: %d\n",
         hashMapGet(map, 1)); // Output: Value for key 1: 10
  printf("Value for key 2: %d\n",
         hashMapGet(map, 2)); // Output: Value for key 2: 20
  printf("Value for key 3: %d\n",
         hashMapGet(map, 3)); // Output: Value for key 3: 30
  hashMapRemove(map, 2);
  printf("Value for key 2 after removal: %d\n",
         hashMapGet(map, 2)); // Output: Value for key 2 after removal: -1
  hashMapFree(map);
  return 0;
}
