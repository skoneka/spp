#ifndef _DB_IO_H
#define _DB_IO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "db_types.h"
#include "util.h"
#include "define.h"

/* Funkcje wczytujące z plików (parametr FILE * in) zbiory rekordów.
 * Wynik zapisywany jest w tablicach struktur.
 *  Parametr max to maksymalna ilosc rekordów wczytana jednorazowo.
 * Funkcje zwracają liczbę wczytanych rekordów.
 */
int db_read_records_students (FILE * in, st_rekord_student records[], int max, bool * overflow);

int db_read_records_lecturers(FILE * in, st_rekord_lecturer records[], int max, bool * overflow);

int db_read_records_topics (FILE * in, st_rekord_topic records[], int max, bool * overflow);

/* Funkcje zapisujące w plikach (FILE * out) rekordy przechowywane
 * w tablicach struktur podawanych jako parametr funkcji.
 * int n - liczba rekordow w tabeli
 */

void db_write_records_students (FILE * out, st_rekord_student records[], int n);

void db_write_records_lecturers(FILE * out, st_rekord_lecturer records[], int n);

void db_write_records_topics (FILE * out, st_rekord_topic records[], int n);


/* Generuje niewykorzystany ID dla rekordu */
int dbGetNewID (FILE * in);

/* Usuwa rekord o podanym ID, wynik zapisuje w out */
int dbRemoveID(FILE * in, FILE * out, int rmid);

int db_remove_topic_id_from_stud(FILE * in, FILE * out, int rmid);

int db_remove_topic_id_from_lecturer(FILE * in, FILE * out, int rmid);

#endif
