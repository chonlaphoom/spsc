
#define CAP 1047293

// use linked list
struct Node {
  int key;
  int value;
  struct Node *next;
};

typedef struct HashMap {
  struct Node *bucket[CAP];
} MyHashMap;

extern MyHashMap *hashMapCreate(void);
extern void hashMapPut(MyHashMap *obj, int key, int value);
extern int hashMapGet(MyHashMap *obj, int key);
extern void hashMapRemove(MyHashMap *obj, int key);
extern void hashMapFree(MyHashMap *obj);
