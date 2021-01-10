#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Author Elizabeth McKenna
* Function: char convertChar (character, integer)
* Purpose:  Function accepts parameters of a character and an integer.
            The character is the character before it has been tranformed.
            The integer is a value between -25 and 25, and represents the
            number of characters shifted that the user wants the alphabet
            to be shifted by
            The function returns the charcater that has been shifted */

char convertChar (char currentChar, int shift){
  /*for lowercase*/
  if (currentChar >= 'a' && currentChar <= 'z'){
    /*if finish alphabet, loop back to letter "a"*/
    if (currentChar > ('z' - shift)){
      currentChar = currentChar - 26;
    }
    else if (currentChar < ('a' - shift)){
      currentChar = currentChar + 26;
    }
    currentChar = currentChar + shift;
  }
  /*for uppercase*/
  else if ((currentChar >= 'A' && currentChar <= 'Z')){
    /*if finish alphabet, loop back to letter "A"*/
    if (currentChar > ('Z' - shift)){
      currentChar = currentChar - 26;
    }
    else if (currentChar < 'A' - shift){
      currentChar = currentChar + 26;
    }
    /*perform shift*/
    currentChar = currentChar + shift;
  }
  return (currentChar);
}
