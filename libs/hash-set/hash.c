#include "hash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * key is in the range of [0, 10^6].
 * At most 10^4 calls will be made to add, remove, and contains.
 */
extern MyHashSet *hashSetCreate() {
  MyHashSet *set = (MyHashSet *)calloc(1, sizeof(MyHashSet));
  if (set == NULL)
    return NULL;
  for (int i = 0; i < CAP; i++) {
    *(set->bucket + i) = EMPTY;
  }
  return set;
}
static int hash(int key) { return key % CAP; }
extern void hashSetAdd(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= CAP)
    return;
  struct Node *current = obj->bucket[hash(key)];

  do {
    if (current != EMPTY && current->key == key) {
      // already exist
      return;
    }

    if (current == EMPTY) {
      struct Node *newNode = (struct Node *)calloc(1, sizeof(struct Node));
      if (newNode == NULL)
        return;
      newNode->key = key;
      newNode->next = NULL;
      obj->bucket[hash(key)] = newNode;
      return;
    }

    current = current->next;
  } while (current != EMPTY);
};
extern void hashSetRemove(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= CAP)
    return;
  struct Node *current = obj->bucket[hash(key)];
  if (current == EMPTY)
    return;
  struct Node *prev = EMPTY;
  do {
    if (current->key == key) {
      if (prev == EMPTY) {
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
  } while (current != EMPTY);
}
extern bool hashSetContains(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= CAP)
    return false;

  struct Node *current = obj->bucket[hash(key)];
  while (current != EMPTY) {
    if (current->key == key) {
      return true;
    }
    current = current->next;
  }

  return false;
};

static void freeNode(struct Node *node) {
  if (node == EMPTY) {
    return;
  }
  if (node->next != EMPTY) {
    freeNode(node->next);
  }
  free(node);
}

extern void hashSetFree(MyHashSet *obj) {
  if (obj == EMPTY) {
    return;
  }
  for (int i = 0; i < CAP; i++) {
    if (obj->bucket[i] == EMPTY) {
      continue;
    }
    freeNode(obj->bucket[i]->next);
    free(obj->bucket[i]);
  }
};

/**
 * example usage:
 * MyHashSet* obj = hashSetCreate();
 * hashSetAdd(obj, key);
 * hashSetRemove(obj, key);
 * bool param_3 = hashSetContains(obj, key);
 * hashSetFree(obj);
 */
