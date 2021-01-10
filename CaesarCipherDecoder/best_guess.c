#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"

/*looks at chi_sq value for each letter of the alphabet,
and keeps track of what has been the smallest value of chi_sq
and returns the value of the shift as the "best guess"
* if smallest is still greater than 60, then assume that text isnt english*/

int best_guess(int * freq_table){
  #define ALPHABET 26
  #define MAXERROR 0.5
  int best_shift = 0;
  double smallest_chi;
  int i = 0;

  /*initialize smallest chi to chi of shift 0*/
  smallest_chi = chi_sq(freq_table, shift);

  /*for each shift (0 - 25), determine chi_sq and compare result to the
  current smallest_chi.  If new smallest chi is found, update information*/

  for (i = 0; i < ALPHABET; i++){
    /*if new smallest chi found*/
    if (chi_sq(freq_table, i) <= smallest_chi){
      best_shift = i;
      smallest_chi = chi_sq(freq_table,i);
    }
  }
  /*make sure the smallest chi is within acceptable range*/
  if (smallest_chi <= MAXERROR){
    return best_shift;
  }
  else {
    return 0;
  }

}
