#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"

void add_letters(int * freq_table, char * string){
  int currentCharCount = 0;
  int i = 0;
  int j = 0;
  /*for each letter of alphabet, go through string
  and count number of times it occurs*/
  for (i = 0; i < 26; i ++){
    j = 0;
      while (j < strlen(string)){
          if ( ( string[j] == ('a' + i) ) || (string[j] == ('A' + i))){
            currentCharCount++;
          }
          j++;
      }
      /*after checked entire string, store currentCharCount into
       corresponding array position*/
       freq_table[i] = freq_table[i] + currentCharCount;
       currentCharCount = 0;
  }

}
