#include "hash.h"
#include <stdbool.h>
#include <stdlib.h>

/*
 * key is in the range of [0, 10^6].
 * At most 10^4 calls will be made to add, remove, and contains.
 */

extern MyHashSet *hashSetCreate() {
  return (MyHashSet *)malloc(sizeof(MyHashSet));
}
extern void hashSetAdd(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= MAX_KEY)
    return;
  obj->keys[key] = 1;
};
extern void hashSetRemove(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= MAX_KEY)
    return;
  obj->keys[key] = EMPTY;
}
extern bool hashSetContains(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= MAX_KEY)
    return false;
  return obj->keys[key] != EMPTY && obj->keys[key] > 0 &&
         obj->keys[key] <= 1000000;
};
extern void hashSetFree(MyHashSet *obj) {
  if (obj != NULL) {
    free(obj);
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
