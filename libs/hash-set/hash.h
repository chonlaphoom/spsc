#include <stdbool.h>

typedef struct {

} MyHashSet;

MyHashSet *hashSetCreate();

void hashSetAdd(MyHashSet *obj, int key);
void hashSetRemove(MyHashSet *obj, int key);
bool hashSetContains(MyHashSet *obj, int key);
void hashSetFree(MyHashSet *obj);

/**
 * example usage:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 * myHashSetRemove(obj, key);
 * bool param_3 = myHashSetContains(obj, key);
 * myHashSetFree(obj);
 */
