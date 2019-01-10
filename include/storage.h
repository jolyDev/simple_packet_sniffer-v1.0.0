#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <IP_entry.h>

int size;

struct IP_entry* * hashArray;
struct IP_entry* dummyItem;
struct IP_entry* item;

struct IP_entry * get_IP_entry(char *);
void add_IP_entry(struct IP_entry * );
void log_IP_call_history(void);
void loadStat();