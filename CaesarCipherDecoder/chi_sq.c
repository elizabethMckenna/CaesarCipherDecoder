#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "A3lib.h"

double chi_sq(int * freq_table, int shift){
  #define ALPHABET 26
  double ENGLISH_FREQ[26] = {0.08167, 0.01492, 0.02782,
                             0.04253, 0.12702, 0.02228,
                             0.02015, 0.06094, 0.06966,
                             0.00153, 0.00772, 0.04025,
                             0.02406, 0.06749, 0.07707,
                             0.01929, 0.00095, 0.05987,
                             0.06327, 0.09056, 0.02758,
                             0.00978, 0.02360, 0.00150,
                             0.01974, 0.00074};
  int n = 0;
  int i = 0;
  char c;
  int expected;
  double chi_sq;
  double chi_next;

  /*calculate number of letters using freq_table*/
  for (i = 0; i < ALPHABET; i ++){
    n = n + freq_table[i];
  }
  /*perform chi_sq calculation for next letter of alphabet and add to total chi value*/
  for (i = 0; i < ALPHABET; i ++){
    /*reset chi_sq value for next summation*/
    chi_next = 0;
    c = 'a' + i;
    expected = freq_table[offset(convertChar(c,shift))];
    chi_next = ((((n* ENGLISH_FREQ[offset(c)]) - expected) * ((n * ENGLISH_FREQ[offset(c)]) - expected)));
    chi_next = chi_next/ (n * n * ENGLISH_FREQ[offset(c)]);
    chi_sq = chi_sq + chi_next;
  }
return chi_sq;
}
