#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _PUBLIC_H
#define _PUBLIC_H

int my_max(const int x1, const int x2);
int my_min(const int x1, const int x2);
int my_abs(const int x);
long my_labs(const long x);
int my_ctoi(const char ch);
unsigned long my_pow(const unsigned long x, const unsigned long y);
long my_ulrandnum(const long low, const long high);

#endif

