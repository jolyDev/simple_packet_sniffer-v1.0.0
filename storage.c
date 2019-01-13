#include <storage.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct _storage {
    int size;
    int filling;
    float loadFactor;
    IP_entry ** buckets;
};

storage * new_storage() {
    storage * self = malloc(sizeof(storage));

    self->size = 128;
    self->filling = 0;
    self->loadFactor= 0.75;
    self->buckets = (IP_entry **)calloc(self->size, sizeof(IP_entry *));

    return self;
}

unsigned int hash(const char * str) {
    unsigned int hash = 5381;

    for (const char* c = str; *c != '\0'; c++)
        hash = ((hash << 5) + hash) + (unsigned char)*c;

    return hash;
}

void rehash(storage * self) {
    IP_entry ** bigger_buckets = malloc(sizeof(IP_entry) * (self->size *= 2));

    for(int i = 0; i < self->size / 2; i++)
        // adding element to new table
        if (self->buckets[i] != NULL) {
            int h = hash(self->buckets[i]->IP_sender) % self->size;
            int index = h;
        
            for( ; bigger_buckets + index != NULL ; ++index)
                index %= self->size;

            bigger_buckets[index] = self->buckets[i];
        }

    free(self->buckets);
    self->buckets = bigger_buckets;
}

void addToStorage(storage* self, IP_entry * el) {

    if(self == NULL || self->buckets == NULL) 
        self = new_storage();

    int code = hash(el->IP_sender) % self->size;


    for(;self->buckets + code != NULL ; ++code)
        code %= self->size; 
        
    self->buckets[code] = createNewIP_entry( el->IP_sender, 0);

    self->filling++;
    if (self->filling * self->loadFactor > self->size)
        rehash(self);
}


static void Storage_free(storage* self) { // @TODO
    free(self->buckets);
    free(self);
}

IP_entry * getFromStorage(storage* self, const char * ip) {

    unsigned int h = hash(ip);
    unsigned int index = h % self->size;

    if (self == NULL || self->buckets == NULL || self->buckets[index] == NULL)  return NULL;

    for(;self->buckets[index];) {
        if (hash(self->buckets[index]->IP_sender) % self->size == index && hash(self->buckets[index]->IP_sender) == h)
            return self->buckets[index];

        ++index;
        index %= self->size;
    }

    return NULL;
}

void log_IP_call_history(storage * self) {
    FILE * fp = fopen("log.txt", "w");
    
    if(fp == NULL) {
        puts("WARNING, can`t log!!");
        return;
    }

    for (int i = 0; i < self->size; i++)
        if (self->buckets[i] != NULL) 
            fprintf(fp, "[%s | %lu]",self->buckets[i]->IP_sender, self->buckets[i]->entry);
         else printf(".");
    
    fclose(fp);
}
    
int copy_str_till_char(char * str, char * result, char c) {
    int j = 0;
    for(; str[j] != c; j++)
        result[j] = str[j];
    result[j] = '\0';

    return j;
}

storage * loadStat() {
    
    FILE * f = fopen("log.txt", "r");

    int size_of_buff = 1000;
    char buffer[size_of_buff];
    buffer[fread(buffer,sizeof(char), size_of_buff, f)] = '\0';
    
    char IP_holder[30];
    char entry_holder[20];
    storage * self = new_storage(); 

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i++] == '[')
            i += copy_str_till_char(buffer + i, IP_holder, ' ');

        i += copy_str_till_char(buffer + i, entry_holder, ']');

        addToStorage(self, (createNewIP_entry(IP_holder, atol(entry_holder + 3))));
    }

    log_IP_call_history(self);

    return self;
}