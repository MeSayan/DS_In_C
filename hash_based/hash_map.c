#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define  SIZE 10

struct Node {
    int key;
    char * value;
    struct Node * next;
};

struct hash_map {
    struct Node * h[SIZE];
};

// hash - function
int hash(int x) {
    return x % SIZE;
}


void initialise(struct hash_map * hm) {
    for (int i =0; i < SIZE; ++i) {
        hm->h[i] = NULL;
    }
}


// helps to visualize the map
void print_hashmap(struct hash_map * hm) {
    for (int i = 0; i < SIZE; ++i) {
        printf("Items for hash key %d : [", i);
        struct Node * p = hm->h[i];
        while (p != NULL) {
            printf("(%d -> %s), ", p->key, p->value);
            p = p->next; 
        }
        printf("] \n");
    }
}

// if key already exists, updates value
// if key doesn't exists, adds it to map
void put(struct hash_map * hm, int key, char * value) {
    int hash_key = hash(key);
    struct Node * p = hm->h[hash_key];
    if(p == NULL) {
       hm->h[hash_key] = (struct Node *) malloc(sizeof(struct Node));
       hm->h[hash_key]->key = key;
       hm->h[hash_key]->value = value;
       hm->h[hash_key]->next = NULL;     
    } else {
        // update old value if key already exists (if key exists at begining of list)
        if (p->key == key) {
            p->value = value;
            return;
        }

        // key doesnot exist at begining of list
        while (p->next != NULL) {
            // update old value if key already exists
            if (p->key == key) {
                p->value = value;
                return;
            }
            p = p->next;
        }

        // Key was not present
        p->next = (struct Node *) malloc(sizeof(struct Node));
        p->next->key = key;
        p->next->value = value;
        p->next->next = NULL;
    }
}

// test whether the key is present in the map
bool in(struct hash_map * hm, int key) {
    int hash_key = hash(key);
    struct Node * p = hm->h[hash_key];
    if( p == NULL ) {
       return false;     
    } else {
        while (p != NULL) {
            if (p->key == key) {
                return true;
            }
            p = p->next;
        }
        return false;
    }
}

// Removes key from map - if key doesn't exist returns "N/A"
char * rm(struct hash_map * hm, int key) {
    int hash_key = hash(key);
    struct Node * p = hm->h[hash_key];
    if (p == NULL)
        return "N/A";
    else {
        if( p->key == key) {
            hm->h[hash_key] = p->next;
            return p->value;
        }

        struct Node * prev = p; 
        for (struct Node * q = p; q != NULL; q = q->next) {
            if (q->key == key) {
                prev->next = q->next;
                return q->value;
            }
            prev = q;
        }
        return "N/A";
    }
}

int main() {
    struct hash_map hm;
    initialise(&hm);
    printf("Adding (100 -> abc), (15 -> def), (200 -> ghi) \n");
    put(&hm, 100, "abc");
    put(&hm, 15,  "def");
    put(&hm, 200, "ghi");
    print_hashmap(&hm);
    printf("%d in map ? %d \n", 200, in(&hm, 200));
    printf("Value for removed entry (%d -> %s) \n", 200, rm(&hm, 200));
    printf("Updating value of key %d \n", 100);
    put(&hm, 100, "ABC");
    print_hashmap(&hm);
    printf("%d in map ? %d \n", 200, in(&hm, 200));
    printf("Value for removed entry (%d -> %s) \n", 100, rm(&hm, 100));
    printf("%d in map ? %d \n", 100, in(&hm, 100));
    print_hashmap(&hm);
    printf("Value in map for key - %d -> %s \n", 25, rm(&hm, 25));
    return 0;
}