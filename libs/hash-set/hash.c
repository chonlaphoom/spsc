#include <stdbool.h>
#include <stdlib.h>

#define MAX_KEY 1000000
#define EMPTY -1

/*
 * key is in the range of [0, 10^6].
 * At most 10^4 calls will be made to add, remove, and contains.
 */

typedef struct {
  int keys[MAX_KEY];
} MyHashSet;

MyHashSet *hashSetCreate() { return (MyHashSet *)malloc(sizeof(MyHashSet)); }
void hashSetAdd(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= MAX_KEY)
    return;
  obj->keys[key] = 1;
};
void hashSetRemove(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= MAX_KEY)
    return;
  obj->keys[key] = EMPTY;
}
bool hashSetContains(MyHashSet *obj, int key) {
  if (obj == NULL || key < 0 || key >= MAX_KEY)
    return false;
  return obj->keys[key] != EMPTY && obj->keys[key] > 0 &&
         obj->keys[key] <= 1000000;
};
void hashSetFree(MyHashSet *obj) {
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
