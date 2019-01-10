#pragma once

#include<stdio.h>	//For standard things
#include<stdlib.h>	//malloc
#include<unistd.h>	//memset

#include<string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <stdbool.h>

//own headers
#include <printPacketInfo.h>
#include <storage.h>
#include <IP_entry.h>

void collect(unsigned char*);