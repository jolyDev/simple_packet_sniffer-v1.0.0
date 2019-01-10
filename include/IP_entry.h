#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//const int ip_length = 10;
// int protocol_len = 4;

struct IP_entry {
    char IP_sender[20];
    long entry;
};

struct IP_entry * createNewIP_entry(char * , long);