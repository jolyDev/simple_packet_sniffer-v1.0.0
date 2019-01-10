#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <progbase.h>
#include <progbase/console.h>
#include <ctype.h>
#include <stdbool.h>

#define BIG_BUFFER_LENGTH 10000
#define BUFFER_LENGTH 200
#define LINKLEN 100
#define INFLEN 30
#define EPSILON 0.1
#define PERCENT 50
#define SLEEP 125

void menu(bool * procced, int (*f)(bool));