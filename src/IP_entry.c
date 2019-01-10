#include <IP_entry.h>

struct IP_entry * createNewIP_entry(char * IP_sender, long entry) {
    
    struct IP_entry * el = (struct IP_entry *)malloc(sizeof(struct IP_entry));
    
    strcpy(el->IP_sender, IP_sender);

    el->entry = entry;
}