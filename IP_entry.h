#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//const int ip_length = 10;
// int protocol_len = 4;

struct IP_entry {
    const char IP_sender[20];
    long entry;
};

typedef struct IP_entry IP_entry;
IP_entry * createNewIP_entry(const char * , long);