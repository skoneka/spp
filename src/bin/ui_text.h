#ifndef  ui_text_INC
#define  ui_text_INC
#include <stdlib.h>
#include <stdio.h>


/* Funkcja kontrolująca działanie nakładki tekstowej. */
int ui_run (int argc, char **argv);

/* Wczytaj argumenty lini poleceń */
int ui_setup_arguments (int argc, char **argv);

/* Wypisz wszystkie dostępne opcje */
void ui_show_options (FILE *);

/* Pokaż opis programu */
void ui_show_description (FILE *);

/* Pokaż krótka pomoc */
void ui_show_help (FILE *);
#endif /* ----- #ifndef ui_text_INC  ----- */
