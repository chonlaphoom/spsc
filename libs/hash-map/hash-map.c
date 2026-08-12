#include "hash-map.h"
#include <stdio.h>
#include <stdlib.h>

int hash(int key) { return key % CAP; }

MyHashMap *hashMapCreate() {
  MyHashMap *map = (MyHashMap *)calloc(1, sizeof(MyHashMap));
  if (map == NULL) {
    return NULL;
  }
  for (int i = 0; i < CAP; i++) {
    map->bucket[i] = NULL;
  }
  return map;
}

void hashMapPut(MyHashMap *obj, int key, int value) {
  if (obj == NULL || key < 0 || key >= CAP)
    return;
  struct Node *current = obj->bucket[hash(key)];
  if (current == NULL) {
    // first node at hash
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    obj->bucket[hash(key)] = newNode;
    return;
  }
  while (current != NULL) {
    if (current->key == key) {
      // update value
      current->value = value;
      return;
    }
    if (current->next == NULL) {
      struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
      newNode->key = key;
      newNode->value = value;
      newNode->next = NULL;
      current->next = newNode;
      return;
    }
    current = current->next;
  }
}

int hashMapGet(MyHashMap *obj, int key) {
  if (obj == NULL || key < 0 || key >= CAP)
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
  if (obj == NULL || key < 0 || key >= CAP)
    return;
  struct Node *current = obj->bucket[hash(key)];
  if (current == NULL)
    return;

  struct Node *prev = NULL;
  do {
    if (current->key == key) {
      if (prev == NULL) {
        // remove head node
        obj->bucket[hash(key)] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  } while (current != NULL);
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
