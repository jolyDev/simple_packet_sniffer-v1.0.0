#include <storage.h>

int hashCode(char * ip) {
    if (ip == NULL) return 0;
    int hash = 0;
    for (int i = 0; ip[i] != '\0'; i++ )
        hash += ip[i] * i * i ;//+ ip2[i] * i;
    return hash;
}

struct IP_entry * get_IP_entry(char * ip) {

    if(hashArray == NULL)
        return NULL;
    
    int code = hashCode(ip);
    int hashIndex = code % size;

    for(;hashArray[hashIndex];) {
        if (hashCode(hashArray[hashIndex]->IP_sender) % size == hashIndex && hashCode(hashArray[hashIndex]->IP_sender) == code)
            return hashArray[hashIndex];

        ++hashIndex;
        hashIndex %= size;
    }

    return NULL;
}

void add_IP_entry(struct IP_entry * el) {

    if (hashArray == NULL) {
        hashArray = (struct IP_entry **)malloc(sizeof(struct IP_entry *) * 10);
        size = 10;
    }

    int code = hashCode(el->IP_sender) % size;
    int hashIndex = code;

    for(;hashArray[hashIndex] != NULL ; ++hashIndex)
        hashIndex %= size;
    hashArray[hashIndex] = el;
}

void rehash() {
    struct IP_entry ** biggerHashArray = (struct IP_entry **)malloc(sizeof(struct IP_entry *) *(size *= 2));

    for(int i = 0; i < size; i++)
        // adding element to new table
        if (hashArray[i] != NULL) {
            int code = hashCode(hashArray[i]->IP_sender) % size;
            int hashIndex = code;
        
            for(;biggerHashArray[hashIndex] != NULL ; ++hashIndex)
                hashIndex %= size;
            biggerHashArray[hashIndex] = hashArray[i];
        }

    free(hashArray);
    hashArray = biggerHashArray;
}

void log_IP_call_history() {
    FILE * fp = fopen("log.txt", "w");
    
    if(fp == NULL) {
        puts("WARNING, can`t log!!");
        return;
    }

    for (int i = 0; i < size; i++)
        if (hashArray[i] != NULL) 
            fprintf(fp, "[%s | %lu]",hashArray[i]->IP_sender, hashArray[i]->entry);
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

void loadStat() {
    
    FILE * f = fopen("log.txt", "r");

    int size_of_buff = 1000;
    char buffer[size_of_buff];
    buffer[fread(buffer,sizeof(char), size_of_buff, f)] = '\0';
    
    char IP_holder[30];
    char entry_holder[20];

    /*deserialization unit*/
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i++] == '[')
            i += copy_str_till_char(buffer + i, IP_holder, ' ');

        i += copy_str_till_char(buffer + i, entry_holder, ']');

        add_IP_entry(createNewIP_entry(IP_holder, atol(entry_holder + 3)));
    }
    log_IP_call_history();
}

