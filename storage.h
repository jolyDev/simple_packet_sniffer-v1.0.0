#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <IP_entry.h>

typedef struct _storage storage;

IP_entry* * hashArray;
IP_entry* dummyItem;
IP_entry* item;


storage * loadStat();

storage * new_storage();

void log_IP_call_history(storage * );

void addToStorage(storage*, IP_entry * );

IP_entry * getFromStorage(storage*, const char * );




