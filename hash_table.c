#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct {
    unsigned int size;
    Entry **buckets; // linked list
} HashTable;

void* verify_malloc_result(void *p) {
    if (p == NULL) {
        fprintf(stderr, "Failed to allocate memory.");
        exit(1);
    }

    return p;
};

Entry* create_entry (char *key, char *value) {
    Entry *entry = malloc(sizeof(Entry));

    entry->key = malloc(strlen(key) + 1); 
    verify_malloc_result(entry->key);

    entry->value = malloc(strlen(value) + 1); 
    verify_malloc_result(entry->value);

    strcpy(entry->key, key);
    strcpy(entry->value, value);

    return entry;
}

/* hash function for strings: djb2 */
unsigned int hash(char *str, int size) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % size;
}

HashTable* create(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    verify_malloc_result(ht);
    
    ht->size = size;
    
    ht->buckets = calloc(size, sizeof(Entry*));
    verify_malloc_result(ht->buckets);
    
    return ht;
};


void insert(HashTable *ht, char *key, char *value) {
    Entry *new_node = create_entry(key, value);
    unsigned index_new_node = hash(new_node->key, ht->size);

    Entry *node = ht->buckets[index_new_node];

    if (node == NULL) {
        ht->buckets[index_new_node] = new_node;
        printf("The bucket at index %u didn't have any entries. First entry was created with the key '%s'.\n", index_new_node, new_node->key);
        return;
    }

    // Collision 
    while (node->next) {
        node = node->next;
    }

    node->next = new_node;
    new_node->next = NULL;

    printf("COLLISION AT BUCKET %u: A new node with key '%s' was created after node of key '%s'.\n", index_new_node, new_node->key, node->key);
}

char* search(HashTable *ht, char *key) {
    unsigned int index_to_look = hash(key, ht->size);
    Entry *node = ht->buckets[index_to_look];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            printf("Entry with key %s was found!\n", key);
            return node->value;
        }

        node = node->next;

    }
    printf("No entry was found with key %s!\n", key);
    return NULL;
}

void delete(HashTable *ht, char *key) {

    unsigned int index_to_look = hash(key, ht->size);

    Entry *node = ht->buckets[index_to_look];
    Entry *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (!prev) { // beginning
                ht->buckets[index_to_look] = node->next;
            } else prev->next = node->next; // end || middle

            free(node->key);
            free(node->value);
            free(node);
            printf("\n\n[i]Node with key %s was deleted!\n", key);
            return;
        } else {
            prev = node;
            node = node->next;
        };
    }

    printf("No entry was found with key %s!\n", key);
} 

void destroy(HashTable *ht) {
    if (ht == NULL) return;

    for (unsigned int i = 0; i < ht->size; i++) {
        Entry *node = ht->buckets[i];
        while (node) {
            Entry *temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }

    free(ht->buckets);
    free(ht);

    printf("\n\nThe hash table and its contents were destroyed successfully!");
}

size_t get_entry_count(HashTable *ht) {
    size_t count = 0;
    for (size_t i = 0; i < ht->size; i++) {
        Entry *node = ht->buckets[i];
        while (node) {
            count++;
            node = node->next;
        }
    }
    return count;
}

void print_hash_table(HashTable *ht) {
    size_t size = ht->size;

    for (int i = 0; i < size; i++) {
        Entry *node = ht->buckets[i];
        if (node) {
            printf("\n[%d]:", i);
            while (node) {
                printf(" %s", node->key);
                node = node->next;
                if (node) {
                    printf(" → ");
                }
            }
        }
        
        
    }
}


int main(int argc, char *argv[]) {
    HashTable *ht = create(10);

    /* INSERT OPERATION */
    insert(ht, "Georgia", "Yellow in Green");
    
    insert(ht, "Fiona Apple", "Valentine");

    insert(ht, "Tyle Hyde", "Nancy Tries to Take the Night");

    insert(ht, "May Kershaw", "For the Cold Country"); 
    
    insert(ht, "Horsegirl", "Phonetics on and on");
    
    insert(ht, "Electrelane (UK)", "Gone Under Sea");

    // /* PRINTING */
    printf("\n\nBefore deletion:\n");

    printf("\n === HASH TABLE === \n");
    size_t entries = get_entry_count(ht);
    printf("Size: %u | Entries: %zu\n", ht->size, entries);
    print_hash_table(ht);

    // /* DELETE OPERATION */
    delete(ht, "Horsegirl");

    /* PRINTING */
    printf("\nAfter deletion:\n");
    printf("\n === HASH TABLE === \n");
    entries = get_entry_count(ht);
    printf("Size: %u | Entries: %zu\n", ht->size, entries);
    print_hash_table(ht);

    /* DESTROY */
    destroy(ht);
    return 0;
}
