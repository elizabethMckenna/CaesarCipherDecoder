/*function declarations*/
int letter_count (char* string);
int *create_freq_table();
void add_letters(int * freq_table, char * string);
int offset(char charIn);
char convertChar (char currentChar, int shift);
double chi_sq(int * freq_table, int shift);
int decode_shift(int * freq_table);
void free_freq_table(int *text_freq);

/*structure declarations*/
struct tempElement {
  char shortString[24];
  double doubleValues[24];
  char longString[144];
  int intValues[12];
};
typedef struct tempElement RecordTemp;

struct element {
  struct tempElement data;
  struct element *next;
};
typedef struct element Record;
