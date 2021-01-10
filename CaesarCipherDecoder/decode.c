#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"


double ENGLISH_FREQ[26] = {0.08167, 0.01492, 0.02782,
                           0.04253, 0.12702, 0.02228,
                           0.02015, 0.06094, 0.06966,
                           0.00153, 0.00772, 0.04025,
                           0.02406, 0.06749, 0.07707,
                           0.01929, 0.00095, 0.05987,
                           0.06327, 0.09056, 0.02758,
                           0.00978, 0.02360, 0.00150,
                           0.01974, 0.00074};


int main (int argc, char *argv[]){
  #define MAXCHAR 100
  #define ALPHABET 26

  FILE *fpIn;
  FILE *fpOut;
  FILE *fpTemp;
  char currentString[MAXCHAR];
  int i,j = 0;
  int numLetters = 0;
  int numChars = 0;
  /*flag finder variables*/
  int fileInFound = 0;
  int fileOutFound = 0;
  int nFlagFound = 0;
  int sFlagFound = 0;
  int SFlagFound = 0;
  int tFlagFound = 0;
  int xFlagFound = 0;

  int maxLength = 0;
  int encodeNum = 0;
  int argCounter = 1; /* b/c will always have exectuable */
  int decodeNum = 0;
  char currentChar;
  int tempFileMade = 0;

  /******************************************************************************/
  /*                    HANDLE COMMAND LINE ARGUMENTS                           */
  /******************************************************************************/

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

  /********************************look for -O flag********************************/

  i = 0;
  for (i = 0; i < argc; i ++){
    if (strncmp(cmdLine[i], "-O", 2) == 0){
        /*if match is found, check if flag is on its own or if seperate arguments*/
        /*also check flag not last argument without filename given*/
        if ((strcmp(cmdLine[i], "-O") == 0) && (i != argc)){
          /*if flag on own, get filename from next argument, otherwise, seperate from flag*/
          fileOutFound = i + 1;
          argCounter = argCounter + 2;
        }
        else {
          j = 0;
          for (j = 0; j < strlen(cmdLine[i])- 2; j++){
            cmdLine[i][j] = cmdLine[i][j+2];
          }
          cmdLine[i][j] = '\0';
          fileOutFound = i;
          argCounter = argCounter + 1;
        }
    }
  }

/****************look for other flags on command line*************************/
i = 0;
for (i = 0; i < argc; i++){
  /*look at each argument to look for flags (argument will begin with a -)*/
  if (strncmp(cmdLine[i], "-", 1) == 0){
    /*look through argument to see if 'n' flag present*********************/
    j = 0;
    for (j = 0; j < strlen(cmdLine[i]); j++ ){
      if (cmdLine[i][j] == 'n'){
        nFlagFound = 1;
      }
    }

    /*look through argument to see if 's' flag present'*********************/
    j = 0;
    for (j = 0; j < strlen(cmdLine[i]); j++ ){
      if (cmdLine[i][j] == 's'){
        sFlagFound = 1;
      }
    }

    /*look through argument to see if 'S' flag present'**********************/
    j = 0;
    for (j = 0; j < strlen(cmdLine[i]); j++ ){
      if (cmdLine[i][j] == 'S'){
        SFlagFound = 1;
      }
    }

    /*look through argument to see if 't' flag present'*********************/
    j = 0;
    for (j = 0; j < strlen(cmdLine[i]); j++ ){
      if (cmdLine[i][j] == 't'){
        tFlagFound = 1;
      }
    }

    /*look through argument to see if 'x' flag present'*********************/
    j = 0;
    for (j = 0; j < strlen(cmdLine[i]); j++ ){
      if (cmdLine[i][j] == 'x'){
        xFlagFound = 1;
      }
    }
  }
}

/******************************************************************************/
/*                               HANDLE -F FLAG                               */
/******************************************************************************/

  /***********make table to be filled with letter frequencies**************/
  int *text_freq = create_freq_table();

  /******************************Read from stdin****************************/
  if (fileInFound == 0){
    /* copy from stdin into frequency table */
    while (( fgets(currentString, MAXCHAR, stdin) != NULL)){
      numLetters = numLetters + letter_count(currentString);
      add_letters(text_freq, currentString);
      numChars = numChars + strlen(currentString);

      /*copy into temp file as reading in to save for later*/
        fpTemp = fopen("tempFile.txt", "a" );
        for (i = 0; i < strlen(currentString); i ++){
          fputc(currentString[i], fpTemp);
        }
        tempFileMade = 1;
        fclose(fpTemp);
    }
  }

  /****************************Read from file********************************/
  else if (fileInFound != 0){
    fpIn = fopen(cmdLine[fileInFound], "r");
    /*check fileIn is not NULL*/
    if (fpIn == NULL){
      printf("Error: Cannot open file in\n");
      return(-2);
    }
    /*copy each character from fileIn to frequency table*/
    while ((fgets(currentString, MAXCHAR, fpIn)) != NULL){
      add_letters(text_freq, currentString);
      numLetters = numLetters + letter_count(currentString);
      numChars = numChars + strlen(currentString);
    }
  fclose(fpIn);
  }

/******************************************************************************/
/*                          DETERMINE SHIFT USED                              */
/******************************************************************************/

  encodeNum = decode_shift(text_freq);
  decodeNum = 26 - encodeNum;

/******************************************************************************/
/*                 PRINT TO STDOUT DEPENDING ON FLAGS PRESENT                 */
/******************************************************************************/

/****************************deal with 's' flag if present ********************/
  if (sFlagFound == 1){
    printf("The shift value used to decode the message is shift = %d\n\n", decodeNum);
  }

/****************************deal with 'S' flag if present ********************/
  if (SFlagFound == 1){
    printf("The shift value used to encode the message is shift = %d\n\n", encodeNum);
  }

/**************************deal with 'x' flg if present************************/
if (xFlagFound == 1){
  /*print chi table for each shift value tested*/
  printf("Chi Squared Value Table\n");
  i = 0;
  for (i = 0; i < ALPHABET; i++){
      printf("%f when shift is %d\n",chi_sq(text_freq, i),i);
  }
  printf("\n");
}

/************************deal with 't' flag if present*************************/
if (tFlagFound == 1){
  printf("Number of Letters in text: %d\n", numLetters);
  printf("Number of Characters in text: %d\n", numChars-1);
  /*ASSUMPTION:
  last character counted is terminating character, so subtract from total value*/

  /*print table*/
  printf("Letter  Frequency\n");
  i = 0;
  for (i = 0; i < ALPHABET; i++){
      printf("%c/%c\t%d\n", ('A'+i),('a'+i),text_freq[i]);
  }
  printf("\n");
}

/******************************************************************************/
/*                          DEAL WITH OUTPUT                              */
/******************************************************************************/

/*********************both file in and file out listed************************/
if (fileInFound != 0 && fileOutFound != 0){
  fpOut = fopen(cmdLine[fileOutFound], "w");
  fpIn = fopen(cmdLine[fileInFound], "r");
  if (fpIn == NULL){
    printf("Error: Cannot open file in\n");
    return(-2);
    fclose (fpOut);
  }
  /*read char from fileIn, convert by guessed shift,
   put changed char into fileOut*/
   while ((currentChar = fgetc(fpIn)) != EOF){
     currentChar = convertChar(currentChar, (encodeNum * -1));
     fputc(currentChar, fpOut);
   }
   fclose(fpIn);
   fclose(fpOut);
}


/************************ file in found, but no file out **********************/
/**********************************(print to stdout)***************************/
else if (fileInFound != 0 && fileOutFound == 0){
  fpIn = fopen(cmdLine[fileInFound], "r");
  /*read char from tempFile, convert by guessed shift,
   put changed char into fileOut*/

   /*only print to stdout if 'n' flag not present*/
   if (nFlagFound == 0){
     printf("Bestshift is %d ENCODE NUM IS %d  decode NUM IS %d\n\n", decode_shift(text_freq) ,encodeNum, decodeNum);
     while ((currentChar = fgetc(fpIn)) != EOF){
       currentChar = convertChar(currentChar, (encodeNum * -1));
       fputc(currentChar, stdout);
     }
   }
}

/****************** file out found, but no file in found **********************/
  /****************** (read from tempfile made earlier) **********************/
else if (fileInFound == 0 && fileOutFound != 0){
  fpOut = fopen(cmdLine[fileOutFound], "w");
  fpTemp = fopen("tempFile.txt", "r");
  if (fpTemp == NULL){
    printf("Error: Cannot open file temp\n");
    return(-2);
    fclose (fpOut);
  }
  /*read char from fileIn, convert by guessed shift,
   put changed char into fileOut*/
   while ((currentChar = fgetc(fpTemp)) != EOF){
     currentChar = convertChar(currentChar, (encodeNum * -1));
     fputc(currentChar, fpOut);
   }
   fclose(fpTemp);
   fclose(fpOut);
}

/******************** no file out found, no file in intFound ******************/
/************ (print to stdout, read from tempfile made earlier) **************/
 else if (fileInFound == 0 && fileOutFound == 0){
   fpTemp = fopen("tempFile.txt", "r");
   if (fpTemp == NULL){
     printf("Error: Cannot open file temp\n");
     return(-2);
   }
   /*read char from fileIn, convert by guessed shift,
    put changed char into fileOut*/

    /*only print to stdout if 'n' flag not present*/
    if (nFlagFound == 0){
      while ((currentChar = fgetc(fpTemp)) != EOF){
        currentChar = convertChar(currentChar, (encodeNum * -1));
        fputc(currentChar, stdout);
      }
    }
    fclose(fpTemp);
 }

/***************** remove temp file if it was made ****************************/
if (tempFileMade == 1){
  tempFileMade = remove("tempFile.txt");
}

/*************************** free the malloc's ********************************/

for (i = 0; i < 26; i ++){
  free(&text_freq[i]);
}

  return 0;
}
