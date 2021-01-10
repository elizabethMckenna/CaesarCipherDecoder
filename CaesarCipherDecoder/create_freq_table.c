#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"

int *create_freq_table(){
  /*make table and allocate memory for each position*/
  int *table = malloc(26 * sizeof(int));
  int i = 0;
  /**/
  for (i = 0; i < 26; i++){
    table[i] = 0;
  }

  return table;
}
/*
int main (int argc, char *argv[]){
  create_freq_table();
  return (1);
}
*/
