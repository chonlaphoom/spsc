#include <stdbool.h>

// load factor = size / capacity
#define CAP 1333357
#define EMPTY NULL

struct Node {
  int key;
  struct Node *next;
};

typedef struct {
  struct Node *bucket[CAP];
} MyHashSet;

extern MyHashSet *hashSetCreate(void);
extern void hashSetAdd(MyHashSet *obj, int key);
extern void hashSetRemove(MyHashSet *obj, int key);
extern bool hashSetContains(MyHashSet *obj, int key);
extern void hashSetFree(MyHashSet *obj);
