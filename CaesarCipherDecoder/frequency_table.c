#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"

int main (int argc, char *argv[]){
  #define MAXCHAR 100
  #define ALPHABET 26

  FILE *fpIn;
  char currentString[MAXCHAR];
  int i,j = 0;
  int numLetters = 0;
  int numChars = 0;
  int fileInFound = 0;
  int maxLength = 0;
  int argCounter = 1; /* b/c will always have exectuable */

  /*************Seperate command line arguments into 2d array*****************/

  /*find longest string on command line*/
  for (i = 0; i < argc; i++){
    if (strlen(argv[i]) > maxLength){
      maxLength = strlen(argv[i]);
    }
  }
  /*make array for command line arguments and move from argv to array*/
  char cmdLine[argc][maxLength + 1];
  i = 0;
  for (i = 0; i < argc; i++){
    strcpy(cmdLine[i], argv[i]);
  }

  /***************************look for -F flag*******************************/
  for (i = 0; i < argc; i ++){
    if (strncmp(cmdLine[i], "-F", 2) == 0){
        /*if match is found, check if flag is on its own or if seperate arguments*/
        /*also check flag not last argument without filename given*/
        if ((strcmp(cmdLine[i], "-F") == 0) && (i != argc)){
          /*if flag on own, get filename from next argument, otherwise, seperate from flag*/
          fileInFound = i + 1 ;
          argCounter = argCounter + 2;
          break;
        }
        else {
          j = 0;
          for (j = 0; j < strlen(cmdLine[i])- 2; j++){
            cmdLine[i][j] = cmdLine[i][j+2];
          }
          cmdLine[i][j] = '\0';
          fileInFound = i ;
          argCounter = argCounter + 1;
          break;
        }
     }
  }

  /*make table to be filled with letter frequencies*/
  int *table = create_freq_table();

  /*************************read from stdin************************/
  if (fileInFound == 0){
    /*copy each character from stdin to stdout*/
    while (( fgets(currentString, MAXCHAR, stdin) != NULL)){
      numLetters = numLetters + letter_count(currentString);
      add_letters(table, currentString);
      numChars = numChars + strlen(currentString);
    }
  }

  /**************************read from file**************************/
  else if (fileInFound != 0){
    fpIn = fopen(cmdLine[fileInFound], "r");
    /*check fileIn is not NULL*/
    if (fpIn == NULL){
      printf("Error: Cannot open file in\n");
      return(-2);
    }
    /*copy each character from fileIn to stdout*/
    while ((fgets(currentString, MAXCHAR, fpIn)) != NULL){
      add_letters(table, currentString);
      numLetters = numLetters + letter_count(currentString);
      numChars = numChars + strlen(currentString);
    }
    fclose(fpIn);
  }

  /*****************Print information to stdout*******************/
  printf("Number of Letters in text: %d\n", numLetters);
  printf("Number of Characters in text: %d\n", numChars-1);
  /*assumption:
  last character counted is terminating character, so subtract from total*/

  /*print table*/
  printf("Letter  Frequency\n");
  i = 0;
  for (i = 0; i < ALPHABET; i++){
      printf("%c/%c\t%d\n", ('A'+i),('a'+i),table[i]);
  }

  free(table);

  return 0;
}
