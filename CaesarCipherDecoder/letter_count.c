#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"

int letter_count (char* string){
    int charCount = 0;
    int i = 0;

    while (string[i] != '\0'){
      /*count the character as a letter if ascii value is between a/z or A/Z
      otherwise, character is not counted in letter count because not a letter*/
      if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z')){
        charCount++;
      }
      i ++;
    }
    return charCount;
}
/*
int main (int argc, char *argv[]){
  letter_count("aeoz AeoZ!\n");
  return (1);
}
*/
