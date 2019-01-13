#include <IP_entry.h>

IP_entry * createNewIP_entry(const char * IP_sender, long entry) {
    
    IP_entry * el = (IP_entry *)malloc(sizeof(IP_entry));
    
    strcpy(el->IP_sender, IP_sender);

    el->entry = entry;
}