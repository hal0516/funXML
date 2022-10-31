#include "_public.h"

int my_max(const int x1, const int x2)
{
  return x1 >= x2 ? x1 : x2;
}

int my_min(const int x1, const int x2)
{
  return x1 <= x2 ? x1 : x2;
}

int my_abs(const int x)
{
  return x >= 0 ? x : -x;
}

long my_labs(const long x)
{
  return x >= 0 ? x : -x;
}

int my_ctoi(const char ch)
{
  switch(ch)
  {
    case '0' : return 0;
    case '1' : return 1;
    case '2' : return 2;
    case '3' : return 3;
    case '4' : return 4;
    case '5' : return 5;
    case '6' : return 6;
    case '7' : return 7;
    case '8' : return 8;
    case '9' : return 9;
    default : return -1;
  }
}

unsigned long my_pow(const unsigned long x, const unsigned long y)
{
	if(y == 0) return 1L;
  unsigned long temp = 1L;
  unsigned long ii = y;
  while(ii--)
		temp *= x;
	return temp;
}

long my_ulrandnum(const long low, const long high)
{
	if(low > high) return -1;
  srand(time(0) );
  return low + (rand() % (high - low + 1) );
}
