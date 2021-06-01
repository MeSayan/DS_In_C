#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HS_SIZE 10


struct Node {
    int value;
    struct Node * next;
};

struct hash_set {
    struct Node * h[HS_SIZE];
};

int hash(int x) {
    return x % HS_SIZE;
}

void initialise(struct hash_set * hs) {
    for (int i =0; i < HS_SIZE; ++i) {
        hs->h[i] = NULL;
    }
}

void print_hashset(struct hash_set * hs) {
    for (int i = 0; i < HS_SIZE; ++i) {
        printf("Hash key %d : ", i);
        struct Node * p = hs->h[i];
        while (p != NULL) {
            printf("%d ", p->value);
            p = p->next;
        }
        printf("\n");
    }
}

void put(struct hash_set * hs, int x) {
    int hash_key = hash(x);
    struct Node * p = hs->h[hash_key];
    if(p == NULL) {
       hs->h[hash_key] = (struct Node *) malloc(sizeof(struct Node));
       hs->h[hash_key]->value = x;
       hs->h[hash_key]->next = NULL;     
    } else {
        while (p->next != NULL)
            p = p->next;
        p->next = (struct Node *) malloc(sizeof(struct Node));
        p->next->value = x;
        p->next->next = NULL;
    }
}

bool in(struct hash_set * hs, int x) {
    int hash_key = hash(x);
    struct Node * p = hs->h[hash_key];
    if( p == NULL ) {
       return false;     
    } else {
        while (p != NULL) {
            if (p->value == x) {
                return true;
            }
            p = p->next;
        }
        return false;
    }
}

bool rm(struct hash_set * hs, int x) {
    int hash_key = hash(x);
    struct Node * p = hs->h[hash_key];
    if (p == NULL)
        return false;
    else {
        if( p->value == x) {
            hs->h[hash_key] = p->next;
            return true;
        }

        struct Node * prev = p; 
        for (struct Node * q = p; q != NULL; q = q->next) {
            if (q->value == x) {
                prev->next = q->next;
                return true;
            }
            prev = q;
        }
        return false;
    }
}

int main() {
    struct hash_set hs;
    initialise(&hs);
    printf("Adding 100, 15, 200 \n");
    put(&hs, 100);
    put(&hs, 15);
    put(&hs, 200);
    print_hashset(&hs);
    printf("%d in set ? %d \n", 200, in(&hs, 200));
    rm(&hs, 200);
    printf("%d in set ? %d \n", 200, in(&hs, 200));
    rm(&hs, 100);
    printf("%d in set ? %d \n", 100, in(&hs, 100));
    print_hashset(&hs);
    printf("Can I remove %d from the set ? %d \n", 25, rm(&hs, 25));
    return 0;
}