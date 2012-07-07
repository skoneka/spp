#ifndef  spp_INC
#define  spp_INC
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "define.h"
#include "util.h"
#include "db_io.h"
/* Niekompletna tablica kodów błędów:
 *
 * -1 - złe/niewystarczające argumenty
 *  0 - nie wykryto błędów
 *  1 - nie otrzymano struktury sppArgs
 *  2 - wymgana nazwa pliku jest nieznana
 *  3 - nie udało się otworzyć pliku bazy danych
 *
 */

/* Struktura sppArgs zawiera wszystkie 
 * parametry potrzebne modułowi spp */
struct sppArgs
{
    int mode; /* tryb działania */

    char type; /* typ rekordu na którym operujemy */
    char *data; /* nazwa bazy danych */
    char *log; /* nazwa pliku logu */
    char *out; /* plik wyjścia standardowego */
    char *build; /* nazwa tworzonej bazy danych */

    int id; /* pole rekordu: numer identyfikacyjny rekordu */
    char *name; /* pole rekordu: nazwa */
    char *degree; /* pole rekordu: stopień naukowy */
    char *room; /* pole rekordu: pokój */
    char *date; /* pole rekordu: termin zajęć */
    char *topic; /* pole rekordu: przedmioty */
    char *topic_type; /* pole rekordu: typ przedmiotu */
    int hours; /* pole rekordu: liczba godzin */
    int index; /* pole rekordu: numer indeksu */
};

/* Funkcja przygotowująca moduł spp do działania, 
 * jako argument pobiera struckturę sppArgs.
 * Kody błędów powyżyej. */
int spp_setup (struct sppArgs *);

/* Funkcja kończąca działanie modułu spp.
 * Zamyka pliki i uwalnia pamięć
 * Kody błędów powyżyej. */
void spp_finish ();

/* Wywołanie funkcji spp_run powoduje wykonanie
 * działań zaprogramowanych w strukturze sppArgs
 * Kody błędów powyżyej. */
int spp_run ();

FILE * spp_get_log();
#endif /* ----- #ifndef spp_INC  ----- */
