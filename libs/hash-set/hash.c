#include "hash.h"
#include <stdbool.h>
#include <stdlib.h>

/*
 * key is in the range of [0, 10^6].
 * At most 10^4 calls will be made to add, remove, and contains.
 */
static int hash(int key) { return key % CAP; }

MyHashSet *hashSetCreate(void) {
  MyHashSet *set = (MyHashSet *)calloc(1, sizeof(MyHashSet));
  return set;
}

void hashSetAdd(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0)
    return;
  int idx = hash(key);
  struct Node *current = obj->bucket[idx];
  while (current != NULL) {
    if (current->key == key) {
      return;
    }
    current = current->next;
  }
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL)
    return;
  newNode->key = key;
  newNode->next = obj->bucket[idx];
  obj->bucket[idx] = newNode;
}

void hashSetRemove(MyHashSet *obj, int key) {
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

bool hashSetContains(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0)
    return false;
  struct Node *current = obj->bucket[hash(key)];
  while (current != NULL) {
    if (current->key == key) {
      return true;
    }
    current = current->next;
  }
  return false;
}

void hashSetFree(MyHashSet *obj) {
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

/**
 * example usage:
 * MyHashSet* obj = hashSetCreate();
 * hashSetAdd(obj, key);
 * hashSetRemove(obj, key);
 * bool param_3 = hashSetContains(obj, key);
 * hashSetFree(obj);
 */
