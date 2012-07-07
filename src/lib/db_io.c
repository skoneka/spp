#include "db_io.h"

/* Dzialanie funkcji char * strtok( char * str, char * delim );
 * Funkcja dzieli ciag znakow (char * str) na kawalki
 * rozdzielone znakiem (lub ciagiem znakow) char * delim.
 * Przy pierwszym wywolaniu funkcji nalezy podac wskaznik
 * do ciagu znakow, ktory ma byc podzielony. Przy kazdym
 * nastepnym wywolaniu jako parametr char * str nalezy podac
 * wartosc NULL. jest to informacja dla funkcji strtok,
 * ze ma ona kontynuowac dzielenie ostatniego ciagu znakow.
 *
 * Nalezy pamietac:
 * 1) W przypadku bledu lub nieodnalezienia rozdzielnika
 *    funkcja zwraca NULL.
 * 2) Funkcja bezpowrotnie niszczy ciag znakow podany
 *    jako parametr char *str. 
 */

/*
 * Makrodyrektywy:
 * __FILE__ : nazwa kompilowanego pliku.
 * __LINE__ : numer linii programu.
 */





int
db_read_records_topics (FILE * in, st_rekord_topic records[], int max, bool * overflow)
{
    char line[LINE_LEN];
    char *s;
    int i = 0;
    int linia = 1;
    *overflow = FALSE;
    while ((fgets (line, LINE_LEN, in) != NULL)) {
        if (feof (in))
            break;
        else if (ferror (in))
            break;
        if (i >= max) {
            *overflow = TRUE;
            break;
        }
        s = strtok (line, "|"); /*pierwsze wywolanie strtok z paremetrem line */
        if (s != NULL) {
            records[i].id = atoi (s);

            s = strtok (NULL, "|");
            if (s != NULL)
                strncpy (records[i].name, s, MAX_NAME);
            else {
                fprintf (stderr, "%s:%d ! E: Error in line: %d.Ignoring record.\n", __FILE__, __LINE__, 
                         linia);
                continue;
            }

            s = strtok (NULL, "|");     /* pobranie z aktualnego wiersza nastepnej kolumny */
            if (s != NULL)
                strncpy (records[i].topic_type, s, MAX_TOPIC_TYPE);
            else {
                fprintf (stderr, "%s:%d ! E: Error in line: %d.Ignorying record.\n", __FILE__, __LINE__, 
                         linia);
                continue;
            }

            s = strtok (NULL, "|");

            records[i].hours = atoi (s);

            s = strtok (NULL, "|");

            if (s != NULL)
                strncpy (records[i].date, s, MAX_DATE);
            else {
                fprintf (stderr, "%s:%d ! E: Error in line: %d.Ignorying record.\n", __FILE__, __LINE__, 
                         linia);
                continue;
            }

            /* W porzadku, wiec zwiekszam licznik rekordow. */
            i++;
            if (i >= max) {
                *overflow = TRUE;
                break;
            }
        }
        else {
            fprintf (stderr, "%s:%d ! E : Error in line %d. Ignorying record.\n", __FILE__, __LINE__,  linia);
        }

        linia++;
    };
    /* Zwracam liczbe rekordow. */
    return i;
}
int
db_read_records_lecturers(FILE * in, st_rekord_lecturer records[], int max, bool * overflow)
{
    char line[LINE_LEN];
    char *s;
    int i = 0;
    int linia = 1;
    *overflow = FALSE;
    while ((fgets (line, LINE_LEN, in) != NULL)) {
        if (feof (in))
            break;
        else if (ferror (in))
            break;
        if (i >= max) {
            *overflow = TRUE;
            break;
        }
        s = strtok (line, "|"); /*pierwsze wywolanie strtok z paremetrem line */
        if (s != NULL) {
            records[i].id = atoi (s);

            s = strtok (NULL, "|");
            if (s != NULL)
                strncpy (records[i].name, s, MAX_NAME);
            else {
                fprintf (stderr, "%s:%d ! E: Error in line: %d.Ignoring record.\n", __FILE__, __LINE__ , linia);
                continue;
            }
            
            s = strtok (NULL, "|");
            if (s != NULL)
                strncpy (records[i].degree, s, MAX_DEGREE);
            else {
                fprintf (stderr, "%s:%d ! E: Erro in line: %d.Ignoring record.\n", __FILE__, __LINE__ , linia);
                continue;
            }

            s = strtok (NULL, "|");
            if (s != NULL)
                strncpy (records[i].room, s, MAX_ROOM);
            else {
                fprintf (stderr, "%s:%d ! E: Erro in line: %d.Ignoring record.\n", __FILE__, __LINE__ , linia);
                continue;
            }

            s = strtok (NULL, "|");     /* pobranie z aktualnego wiersza nastepnej kolumny */
            if (s != NULL)
                strncpy (records[i].topic, s, MAX_TOPIC);
            else {
                fprintf (stderr, "%s:%d ! E: Error in line: %d.Ignoring record.\n", __FILE__, __LINE__ , linia);
                continue;
            }

            /* W porzadku, wiec zwiekszam licznik rekordow. */
            i++;
            if (i >= max) {
                *overflow = TRUE;
                break;
            }
        }
        else {
            fprintf (stderr, "%s:%d !  E: Error in line: %d.Ignoring record.\n", __FILE__, __LINE__,  linia);
        }
        linia++;
    };
    /* Zwracam liczbe rekordow. */
    return i;
}
int
db_read_records_students (FILE * in, st_rekord_student records[], int max, bool * overflow)
{
    char line[LINE_LEN];
    char *s;
    int i = 0;
    int linia = 1;
    *overflow = FALSE;
    while ((fgets (line, LINE_LEN, in) != NULL)) {
        if (feof (in))
            break;
        else if (ferror (in))
            break;
        if (i >= max) {
            *overflow = TRUE;
            break;
        }
        s = strtok (line, "|"); /*pierwsze wywolanie strtok z paremetrem line */
        if (s != NULL) {
            records[i].id = atoi (s);

            s = strtok (NULL, "|");
            if (s != NULL)
                strncpy (records[i].name, s, MAX_NAME);
            else {
                fprintf (stderr, "%s:%d ! E: Erro in line: %d.Ignoring record.\n", __FILE__, __LINE__ , linia);
                continue;
            }

            s = strtok (NULL, "|");

            records[i].index = atoi (s);

            s = strtok (NULL, "|");     /* pobranie z aktualnego wiersza nastepnej kolumny */
            if (s != NULL)
                strncpy (records[i].topic, s, MAX_TOPIC);
            else {
                fprintf (stderr, "%s:%d ! E: Error in line: %d.Ignorying record.\n", __FILE__, __LINE__ , linia);
                continue;
            }

            /* W porzadku, wiec zwiekszam licznik rekordow. */
            i++;
            if (i >= max) {
                *overflow = TRUE;
                break;
            }
        }
        else {
            fprintf (stderr, "%s:%d ! E: Error in line: %d.Ignorying record\n", __FILE__, __LINE__,  linia);
        }

        linia++;
    };
    /* Zwracam liczbe rekordow. */
    return i;
}

void
db_write_records_lecturers(FILE * out, st_rekord_lecturer records[], int n)
{
    int i;
    char buf[LINE_LEN];
    int s_len;
    for (i = 0; i < n; i++) {
        if (records[i].id != -1) {
            util_strip_nl (records[i].name);
            util_strip_nl (records[i].degree);
            util_strip_nl (records[i].room);
            util_strip_nl (records[i].topic);
            snprintf (buf, sizeof buf, "%d|%s|%s|%s|%s\n",
                      records[i].id,
                      records[i].name,
                      records[i].degree,
                      records[i].room,
                      records[i].topic);
            s_len = strlen (buf);

            fwrite (buf, 1, s_len * sizeof *buf, out);

        }
    }
}
void
db_write_records_students (FILE * out, st_rekord_student records[], int n)
{
    int i;
    char buf[LINE_LEN];
    int s_len;
    for (i = 0; i < n; i++) {
        if (records[i].id != -1) {
            util_strip_nl (records[i].name);
            util_strip_nl (records[i].topic);
            snprintf (buf, sizeof buf, "%d|%s|%d|%s\n",
                      records[i].id,
                      records[i].name, records[i].index,
                      records[i].topic);
            s_len = strlen (buf);

            fwrite (buf, 1, s_len * sizeof *buf, out);

        }
    }
}

void
db_write_records_topics (FILE * out, st_rekord_topic records[], int n)
{
    int i;
    char buf[LINE_LEN];
    int s_len;
    for (i = 0; i < n; i++) {
        if (records[i].id != -1) {
            util_strip_nl (records[i].name);
            util_strip_nl (records[i].topic_type);
            util_strip_nl (records[i].date);
            snprintf (buf, sizeof buf, "%d|%s|%s|%d|%s\n",
                      records[i].id,
                      records[i].name,
                      records[i].topic_type,
                      records[i].hours,
                      records[i].date);
            s_len = strlen (buf);

            fwrite (buf, 1, s_len * sizeof *buf, out);

        }
    }
}



int
dbRemoveID(FILE * in, FILE * out, int rmid)
{
    char line[LINE_LEN];
    char line_org[LINE_LEN];
    char *s;
    while ((fgets (line, LINE_LEN, in) != NULL)) {
        if (feof (in))
            break;
        else if (ferror (in))
            break;
        strncpy( line_org, line, LINE_LEN);
        s = strtok (line, "|"); /*pierwsze wywolanie strtok z paremetrem line */
        if (s != NULL) {
            int id = atoi (s);
            if (rmid != id) {
                fwrite(&line_org, strlen(line_org), 1, out);
                if (ferror(out))
                    return 1;
            }
        }
    }
    return 0;
}

int
db_remove_topic_id_from_stud(FILE * in, FILE * out, int rmid)
{
    st_rekord_student records_students[MAX_RECORDS];
    bool overflow;
    char *s;
    char *topic = malloc(MAX_TOPIC * sizeof(topic));
    do {
        int records_n = db_read_records_students (in, records_students, MAX_RECORDS, &overflow);
        int i;
        for (i=0; i<records_n; i++) {
            s = strtok(records_students[i].topic, ",");
            memset(topic, '\0', MAX_TOPIC);
            while (1) {
                if (!s)
                    break;
                int sub_id = atoi(s);
                if (sub_id != rmid) {
                    strcat(topic, s);
                    strcat(topic, ",");
                }
                s = strtok(NULL, ",");
            }
            strncpy(records_students[i].topic, topic, MAX_TOPIC);
            db_write_records_students (out, &records_students[i], 1);
        }
    } while (overflow);
    free(topic);
    return 0;
}

int
db_remove_topic_id_from_lecturer(FILE * in, FILE * out, int rmid)
{
    st_rekord_lecturer records_lecturers[MAX_RECORDS];
    bool overflow;
    char *s;
    char *topic = malloc(MAX_TOPIC * sizeof(topic));
    do {
        int records_n = db_read_records_lecturers (in, records_lecturers, MAX_RECORDS, &overflow);
        int i;
        for (i=0; i<records_n; i++) {
            s = strtok(records_lecturers[i].topic, ",");
            memset(topic, '\0', MAX_TOPIC);
            while (1) {
                if (!s)
                    break;
                int sub_id = atoi(s);
                if (sub_id != rmid) {
                    strcat(topic, s);
                    strcat(topic, ",");
                }
                s = strtok(NULL, ",");
            }
            strncpy(records_lecturers[i].topic, topic, MAX_TOPIC);
            db_write_records_lecturers (out, &records_lecturers[i], 1);
        }
    } while (overflow);
    free(topic);
    return 0;
}

int
dbGetNewID (FILE * in)
{
    int maxid = 0;
    char line[LINE_LEN];
    char *s;
    while ((fgets (line, LINE_LEN, in) != NULL)) {
        if (feof (in))
            break;
        else if (ferror (in))
            break;
        s = strtok (line, "|"); /*pierwsze wywolanie strtok z paremetrem line */
        if (s != NULL) {
            int id = atoi (s);
            if (id>maxid) maxid = id;
        }
    }
    return maxid+1;
}
