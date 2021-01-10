#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"

int offset(char charIn){
  int shiftNum;
  /*if capital letter in*/
  if ( (charIn >= 'A') && (charIn <= 'Z') ){
    shiftNum = charIn - 'A';
  }

  /*if lower case letter in*/
  else if ( (charIn >= 'a') && (charIn <= 'z') ){
    shiftNum = charIn - 'a';
  }
  /*if character in is not a letter*/
  else {
    printf("Error: offset requires parameter to be letter between a/z or A/Z.\n");
    return -1;
  }

  return shiftNum;
}
