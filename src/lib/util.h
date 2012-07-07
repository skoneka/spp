#ifndef  util_INC
#define  util_INC
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "define.h"

void setVerbose (bool b);

void fprintf_v (FILE * out, const char *format, ...);

/* Funkcja kopiująca pliki. 
 * Zwraca 0 lub wartość != 0 dla niepowodzenia */
int util_copy_file (FILE * in, FILE * out);

/* Funkcja usuwająca znak nowej lini. 
 * Zwraca wskaźnik na wynikowy łańcuch znaków */
char *util_strip_nl (char *s);

#endif /* ----- #ifndef util_INC  ----- */
