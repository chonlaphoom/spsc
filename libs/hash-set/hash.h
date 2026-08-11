#include <stdbool.h>

#define MAX_KEY 1000000
#define EMPTY -1

typedef struct {
  int keys[MAX_KEY];
} MyHashSet;

extern MyHashSet *hashSetCreate();

extern void hashSetAdd(MyHashSet *obj, int key);
extern void hashSetRemove(MyHashSet *obj, int key);
extern bool hashSetContains(MyHashSet *obj, int key);
extern void hashSetFree(MyHashSet *obj);

/**
 * example usage:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 * myHashSetRemove(obj, key);
 * bool param_3 = myHashSetContains(obj, key);
 * myHashSetFree(obj);
 */
