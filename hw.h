#ifndef HW_H
#define HW_H
#include <string.h>
#include <ctype.h>
#define MAX_STR 50
#define SIZE 50
#define TIME 8
#define MAX_YEARS 2018
#define MIN_YEARS 1500
#define HOUR_SECS 3600
#define MIN_SECS 60
#define ADD_ZERO 10
#define FILE_NAME "struct.bin"
/*----------------------------------------
Author:                  Gabriele Buivydaite
Date created:            2018-11-26
Purpose:                 to store and edit data about songs

Parameters:
MAX_str    -  size of an array of name
SIZE       -  size of an array of structs
TIME       -  size of an array of duration
MAX_years  -  current year
MIN_years  -  defined oldest possible year of song release
j          -  index of array elements
l          -  lenght of strings


*/
typedef struct song{
char name[MAX_STR + 1];        //to do dynamic arrays
char title[MAX_STR + 1];
char duration[TIME + 1];
int date;
int num_list;
}Song;

int to_file(Song s[], int j);
void from_file(Song * s, int *j, int *mem_num);
#endif
