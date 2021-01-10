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
  FILE *fpName;
  char currentString[MAXCHAR];
  int i,j = 0;
  int numLetters = 0;
  int numChars = 0;
  /*flag finder variables*/
  int fileInFound = 0;
  int fileOutFound = 0;
  int fileNameFound = 0;
  int rFlagFound = 0;

  int maxLength = 0;
  int encodeNum = 0;
  int argCounter = 1; /* b/c will always have exectuable */
  int decodeNum = 0;
  RecordTemp tempRec;
  int recCount = 0;


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

  /********************************look for -D flag********************************/

  i = 0;
  for (i = 0; i < argc; i ++){
    if (strncmp(cmdLine[i], "-D", 2) == 0){
        /*if match is found, check if flag is on its own or if seperate arguments*/
        /*also check flag not last argument without filename given*/
        if ((strcmp(cmdLine[i], "-D") == 0) && (i != argc)){
          /*if flag on own, get filename from next argument, otherwise, seperate from flag*/
          fileNameFound = i + 1;
          argCounter = argCounter + 2;
        }
        else {
          j = 0;
          for (j = 0; j < strlen(cmdLine[i])- 2; j++){
            cmdLine[i][j] = cmdLine[i][j+2];
          }
          cmdLine[i][j] = '\0';
          fileNameFound = i;
          argCounter = argCounter + 1;
        }
    }
  }

  /************************* look for -r flag ********************************/
  i = 0;
  for (i = 0; i < argc; i++){
    /*look at each argument to look for flags (argument will begin with a -)*/
    if (strncmp(cmdLine[i], "-", 1) == 0){
      /*look through argument to see if 'n' flag present*********************/
      j = 0;
      for (j = 0; j < strlen(cmdLine[i]); j++ ){
        if (cmdLine[i][j] == 'r'){
          rFlagFound = 1;
        }
      }
    }
  }

    /******************************************************************************/
    /*                               HANDLE -D FLAG                               */
    /******************************************************************************/

      /***********make table to be filled with letter frequencies**************/
      int *text_freq = create_freq_table();

      /******************************Read from stdin****************************/
      if (fileNameFound == 0){
        /* no file name given print error message to stdout */
        encodeNum = 0;
        decodeNum = 0;
      }
      /****************************Read from file********************************/
      else if (fileNameFound != 0){
        fpName = fopen(cmdLine[fileNameFound], "r");
        /*check fileIn is not NULL*/
        if (fpName == NULL){
          printf("Error: Cannot open file in\n");
          return(-2);
        }
        /*copy each character from fileIn to frequency table*/
        while ((fgets(currentString, MAXCHAR, fpName)) != NULL){
          add_letters(text_freq, currentString);
          numLetters = numLetters + letter_count(currentString);
          numChars = numChars + strlen(currentString);
        }
      fclose(fpName);
      }

  /****************************************************************************/
  /*                DETERMINE SHIFT USED IN EXTRA TEXT FILE                   */
  /****************************************************************************/
  if (fileNameFound != 0){
    encodeNum = decode_shift(text_freq);
    decodeNum = 26 - encodeNum;
  }

  /******************************************************************************/
  /*                               HANDLE -F FLAG                               */
  /******************************************************************************/
    /******************************Read from stdin****************************/
    if (fileInFound == 0){
      /* no file name given print error message to stdout */
      printf("Error: No valid input file");
      return (-2);
    }

    /****************************Read from file********************************/
    else if (fileInFound != 0){
      fpIn = fopen(cmdLine[fileInFound], "rb");
      /*check fileIn is not NULL*/
      if (fpIn == NULL){
        printf("Error: Cannot open file in\n");

        return(-2);
      }
      if (rFlagFound == 1){
        fseek(fpIn, sizeof(RecordTemp) * -1 , SEEK_END);
      }
while (fread(&tempRec, sizeof(RecordTemp),1, fpIn)){
      if (rFlagFound == 1){
        recCount ++;
        fseek(fpIn, sizeof(RecordTemp) * -1 *(recCount+1), SEEK_END);
    }
else {

      fseek(fpIn, 0, SEEK_CUR + (recCount * sizeof(RecordTemp)));
        recCount ++;

}

/*FOR EACH TEMP RECORD READ IN, SHIFT DATA BY DECODE, AND COPY TO OUTPUT FILE.*/
for (i = 0; i < strlen(tempRec.shortString); i ++){
  tempRec.shortString[i] = convertChar(tempRec.shortString[i], decodeNum);
}
for (i = 0; i < strlen(tempRec.longString); i++){
  tempRec.longString[i] = convertChar(tempRec.longString[i], decodeNum);
}


/*records copied to file in forwards order: append to end of binary file*/

  fpOut = fopen(cmdLine[fileOutFound], "ab");
  if (fpOut == NULL){
    printf("Error: Cannot open file out\n");
    return(-2);

  }
  fwrite(&tempRec, sizeof(RecordTemp), 1, fpOut);
if (ftell(fpIn) == 0){
   break;
}
      }

      /*manually get first record becasue not working*/
      if (rFlagFound != 0){
      recCount++;
      fseek(fpIn, 0, SEEK_SET);
      fread(&tempRec, sizeof(RecordTemp),1, fpIn);

      /*FOR EACH TEMP RECORD READ IN, SHIFT DATA BY DECODE, AND COPY TO OUTPUT FILE.*/
      for (i = 0; i < strlen(tempRec.shortString); i ++){
        tempRec.shortString[i] = convertChar(tempRec.shortString[i], decodeNum);
      }
      for (i = 0; i < strlen(tempRec.longString); i++){
        tempRec.longString[i] = convertChar(tempRec.longString[i], decodeNum);
      }
      fwrite(&tempRec, sizeof(RecordTemp), 1, fpOut);

      }

printf("RECORDS: %d\n", recCount);

    fclose(fpOut);
    fclose(fpIn);
    }
    for (i = 0; i < 26; i ++){
      free(&text_freq[i]);
    }
    free (text_freq);

  return (0);
}
